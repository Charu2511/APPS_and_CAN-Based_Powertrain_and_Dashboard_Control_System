# APPS_and_CAN-Based_Powertrain_and_Dashboard_Control_System

## Project Overview

This project presents the design and development of a microcontroller-based **Accelerator Pedal Position Sensor (APPS) and CAN-based Powertrain and Dashboard Control System**.

The system is designed to acquire and process accelerator pedal position data in real time, implement safety monitoring mechanisms, and communicate pedal information to a secondary microcontroller through a Controller Area Network (CAN) bus.

The system also integrates dashboard LED control to provide visual feedback on the operating status of the accelerator pedal and associated safety conditions.

Custom-designed PCBs were developed to integrate the APPS interface, safety monitoring, CAN communication, and dashboard control into a compact embedded hardware system.

## Key Features

- **Real-Time APPS Monitoring:** Microcontroller-based acquisition and processing of accelerator pedal position sensor signals.
- **Safety Monitoring:** Continuous sensor monitoring and pedal plausibility checks to identify abnormal operating conditions.
- **Fault Detection:** Threshold-based fault detection mechanisms for identifying invalid sensor readings and potential system failures.
- **CAN Bus Communication:** Transmission of accelerator pedal position data to a secondary microcontroller through CAN communication.
- **Powertrain Integration:** Interface with a secondary controller responsible for communicating with the motor controller.
- **Dashboard LED Control:** LED-based dashboard indication for displaying system status and relevant operating conditions.
- **Custom PCB Design:** Dedicated PCB development integrating sensor interfacing, safety logic, CAN communication, and dashboard control.

## System Architecture

The system consists of two primary microcontroller-based control units.

### 1. APPS and Safety Monitoring Unit

The primary controller is responsible for:

- Acquiring accelerator pedal position sensor signals.
- Processing real-time pedal position data.
- Continuously monitoring sensor readings.
- Performing pedal plausibility checks.
- Detecting sensor faults using predefined thresholds.
- Controlling dashboard LEDs based on system conditions.
- Transmitting processed accelerator pedal data through the CAN bus.

### 2. Powertrain Interface Unit

The secondary controller receives accelerator pedal information from the primary controller through the CAN bus.

Its role is to interface the received data with the motor controller as part of the vehicle's powertrain control system.

### System Data Flow

```text
Accelerator Pedal Position Sensor
              |
              v
    Primary Microcontroller
              |
       +------+------+
       |             |
       v             v
  Safety Logic   Dashboard LED
       |          Control
       |
       v
    CAN Bus
       |
       v
Secondary Microcontroller
       |
       v
   Motor Controller
```

## Safety Implementation

Safety monitoring is an important component of this project. The APPS controller incorporates several mechanisms to identify abnormal sensor behavior and improve the reliability of pedal position monitoring.

Implemented safety features include:

- Continuous monitoring of accelerator pedal sensor signals.
- Pedal plausibility checking to identify inconsistent sensor readings.
- Threshold-based fault detection.
- Monitoring of abnormal operating conditions.
- Dashboard LED indication for relevant system conditions.

These mechanisms are intended to detect potential sensor-related faults before accelerator pedal information is passed to the downstream powertrain interface.

## CAN Bus Communication

CAN communication is used to establish data exchange between the primary APPS controller and the secondary powertrain interface controller.

The communication system enables:

- Transmission of processed accelerator pedal position data.
- Communication between distributed microcontroller units.
- Integration with the motor controller interface.
- A structured communication link between the APPS and powertrain subsystems.

## Hardware Development

Custom PCBs were designed and implemented to integrate the different functional blocks of the system.

The hardware development includes:

- APPS sensor interfacing circuitry.
- Microcontroller-based signal acquisition and processing.
- Safety monitoring circuitry and logic.
- CAN communication interface.
- Dashboard LED control circuitry.
- PCB layout and hardware integration.

## Technologies and Tools

The project involves the following engineering domains:

- Embedded Systems Development
- Microcontroller Programming
- Accelerator Pedal Position Sensing
- CAN Bus Communication
- Automotive Powertrain Electronics
- Embedded Safety Monitoring
- PCB Design and Development
- Hardware and Software Integration

**Note:** Specific microcontroller models, programming languages, development environments, and PCB design tools can be added here based on the actual hardware and software used.

## Repository Structure

The repository can be organized as follows:

```text
APPS-CAN-Powertrain-Dashboard/
│
├── README.md
│
├── Firmware/
│   ├── APPS_Controller/
│   │   └── Source_Code/
│   │
│   └── Powertrain_Controller/
│       └── Source_Code/
│
├── Hardware/
│   ├── APPS_PCB/
│   ├── CAN_Interface/
│   └── Dashboard_PCB/
│
├── Documentation/
│   ├── Project_Report.pdf
│   ├── System_Architecture/
│   └── Circuit_Diagrams/
│
├── Images/
│   ├── PCB_Design/
│   ├── Hardware_Prototype/
│   └── System_Diagram/
│
└── LICENSE
```

*The directory structure is a suggested organization for the project. Adjust it according to the files included in the repository.*

## Project Objectives

The primary objectives of this project are:

1. Develop a microcontroller-based APPS system for real-time accelerator pedal data acquisition and processing.
2. Implement sensor monitoring and plausibility-checking mechanisms for fault detection.
3. Establish CAN-based communication between distributed microcontroller units.
4. Integrate accelerator pedal information with the motor controller interface.
5. Develop dashboard LED control for visual system indication.
6. Design and implement custom PCBs for hardware integration.

## Applications

The developed system demonstrates embedded control and communication concepts relevant to:

- Electric Vehicle (EV) Powertrain Systems.
- Automotive Embedded Electronics.
- Accelerator Pedal Monitoring Systems.
- CAN-Based Distributed Control Systems.
- Automotive Dashboard and Driver Interface Systems.
- Embedded Safety Monitoring Applications.

## Future Improvements

Potential future development areas include:

- Implementation of additional diagnostic and fault-reporting features.
- Enhanced CAN message validation and communication monitoring.
- Integration of additional dashboard indicators.
- Extended hardware testing and system validation.
- Further development of powertrain safety and control interfaces.

## Author

Developed as a Electrical Team member of EV FSAE team "Team Crack Platoon".

## License

This project is intended for educational and engineering reference purposes. Licensing and reuse permissions should be specified according to the author's requirements.
