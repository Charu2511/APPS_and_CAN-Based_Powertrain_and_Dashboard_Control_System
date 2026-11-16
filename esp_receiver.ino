#include <SPI.h>
#include <mcp2515.h>

#define MCP_CS   5    // CS pin on ESP32
#define MCP_INT 21    // INT from MCP2515 → ESP32 IO21

MCP2515 mcp(MCP_CS);
volatile bool msgReady = false;

void IRAM_ATTR onMCPInterrupt() {
  msgReady = true;
}

void setup() {
  Serial.begin(115200);
  SPI.begin(18, 19, 23);  // SCK, MISO, MOSI

  mcp.reset();
  mcp.setBitrate(CAN_500KBPS, MCP_8MHZ);  // ← corrected here as well
  mcp.setNormalMode();

  pinMode(MCP_INT, INPUT);
  attachInterrupt(digitalPinToInterrupt(MCP_INT), onMCPInterrupt, FALLING);

  Serial.println("MCP2515 Receiver Ready");
}

void loop() {
  if (!msgReady) return;
  msgReady = false;

  struct can_frame frame;
  if (mcp.readMessage(&frame) == MCP2515::ERROR_OK) {
    Serial.print("Rx ID: 0x");
    Serial.print(frame.can_id, HEX);
    Serial.print("  Data:");
    for (uint8_t i = 0; i < frame.can_dlc; i++) {
      Serial.print(" ");
      Serial.print(frame.data[i], HEX);
    }
    Serial.println();
  }
}
