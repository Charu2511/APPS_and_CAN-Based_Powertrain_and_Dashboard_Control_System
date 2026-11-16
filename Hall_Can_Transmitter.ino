#include <SPI.h>
#include <mcp2515.h>

// ── Hardware pins ─────────────────────────────────
const int MCP_CS_PIN    = 10;  // Uno D10 → MCP2515 CS
const int hallPin1      = A0;  // Sensor 1
const int hallPin2      = A1;  // Sensor 2
const int analogOutPin  = 5;   // PWM output (debug)

// ── Sensor calibration ─────────────────────────────
// Sensor 1
const float V1_min      = 1.52493;
const float V1_max      = 4.85;
// Sensor 2
const float V2_min      = 1.49071;
const float V2_max      = 4.85;

const float PWM_MAX     = 210.0;    // Max PWM duty (0–255)
const float DEVIATION_LIMIT = 10;   // allowable % difference between sensors

// ── Fault handling ─────────────────────────────────
const unsigned long IMPLAUSIBLE_MS = 100;
static unsigned long deviationStartTime = 0;
static bool implausible = false;
static bool outOfRange  = false;
static bool systemFault = false;

// ── CAN controller ─────────────────────────────────
MCP2515 mcp(MCP_CS_PIN);//entering the pin 10 to mcp function 

void setup() {
  pinMode(analogOutPin, OUTPUT);
  Serial.begin(115200);
  while (!Serial);

  SPI.begin();//starting SPI communication
  mcp.reset();//mcp needs to be resetted
  mcp.setBitrate(CAN_500KBPS, MCP_8MHZ);//tells the library that can bus speed is 500KBPS and the MCP module using has 8MHZ oscillator
  mcp.setNormalMode();//2 modes, normal(data send receive) and configuration(setting change).

  Serial.println("Dual Pedal Sensor System + CAN Ready\n");
}

void loop() {
  // --- Read sensors ---
  int rawValue1 = analogRead(hallPin1);
  int rawValue2 = analogRead(hallPin2);

  float voltage1 = rawValue1 * (5.0 / 1023.0);
  float voltage2 = rawValue2 * (5.0 / 1023.0);

  // --- Normalize ---
  float norm1 = (voltage1 - V1_min) / (V1_max - V1_min);
  float norm2 = (voltage2 - V2_min) / (V2_max - V2_min);
  norm1 = constrain(norm1, 0.0, 1.0);
  norm2 = constrain(norm2, 0.0, 1.0);

  int pwmInt1 = round(norm1 * PWM_MAX);
  int pwmInt2 = round(norm2 * PWM_MAX);

  float pedalPercent1 = norm1 * 100.0;
  float pedalPercent2 = norm2 * 100.0;

  // --- Range checks ---
  bool inRange1 = (voltage1 >= V1_min) && (voltage1 <= V1_max);
  bool inRange2 = (voltage2 >= V2_min) && (voltage2 <= V2_max);
  outOfRange = (!inRange1 || !inRange2);

  // --- Implausibility detection ---
  implausible = false;
  if (inRange1 && inRange2) {
    float diffPercent = abs(pedalPercent1 - pedalPercent2);
    if (diffPercent > DEVIATION_LIMIT) {
      if (deviationStartTime == 0) deviationStartTime = millis();
      else if (millis() - deviationStartTime >= IMPLAUSIBLE_MS) implausible = true;
    } else {
      deviationStartTime = 0;
    }
  } else {
    deviationStartTime = 0;
  }

  // --- Fault condition check ---
  bool newSystemFault = (outOfRange || implausible);
  if (newSystemFault && !systemFault) {
    if (outOfRange) Serial.println("SYSTEM FAULT: Sensor out-of-range detected -> Forcing 0% pedal.");
    else if (implausible) Serial.println("SYSTEM FAULT: Implausibility detected between sensors -> Forcing 0% pedal.");
  }
  systemFault = newSystemFault;

  // --- Final PWM output ---
  int pwmOut = 0;
  float pedalPercent = 0.0;
  if (!systemFault) {
    pwmOut = round((pwmInt1 + pwmInt2) / 2.0);
    pedalPercent = (pwmOut / PWM_MAX) * 100.0;
  } else {
    pwmOut = 0;
    pedalPercent = 0.0;
  }
  analogWrite(analogOutPin, pwmOut);

  // --- Serial debug print ---
  Serial.print("Sensor1: ");
  Serial.print(voltage1, 3);
  Serial.print("V -> ");
  Serial.print(pedalPercent1, 1);
  Serial.print("% | PWM=");
  Serial.print(pwmInt1);
  if (!inRange1) Serial.print(" [OUT OF RANGE]");

  Serial.print("\t\t");

  Serial.print("Sensor2: ");
  Serial.print(voltage2, 3);
  Serial.print("V -> ");
  Serial.print(pedalPercent2, 1);
  Serial.print("% | PWM=");
  Serial.print(pwmInt2);
  if (!inRange2) Serial.print(" [OUT OF RANGE]");

  Serial.print("\t\t");

  Serial.print("OUT_PWM=");
  Serial.print(pwmOut);
  Serial.print("  Pedal=");
  Serial.print(pedalPercent, 1);
  Serial.print("%");

  if (outOfRange) Serial.print("  [FAULT: OUT OF RANGE]");
  else if (implausible) Serial.print("  [FAULT: IMPLAUSIBLE]");

  Serial.println();

  //Can Start
  // Scale % into 0–100 integer (1 byte)
  uint8_t pctByte = (uint8_t) pedalPercent; //value to 8 bit conversion

  // Send CAN message
  struct can_frame frame;
  frame.can_id  = 0x123; //message id
  frame.can_dlc = 1; //1 byte length
  frame.data[0] = pctByte; 

  if (mcp.sendMessage(&frame) == MCP2515::ERROR_OK) {//&frame is a pointer to the structure, and it sends the CAN frame by the status code (sendmessage()), and MCP2515 sends code like ERROR_OK or ERROR_FAIL
    Serial.print("Sent Pedal % = ");
    Serial.println(pctByte);
  } else {
    Serial.println("CAN Send Error");
  }

  delay(1000);
}
