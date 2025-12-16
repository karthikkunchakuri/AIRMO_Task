# AIRMO Airplane Test Campaign – Environmental Data Acquisition System

## Overview
This repository contains the complete firmware, hardware documentation, and supporting tools for the **AIRMO airplane test campaign environmental measurement setup**. The system is designed to record precise environmental and positional data during flight tests prior to satellite deployment.

The solution complies with the task constraints:
- Only **commercially available modules** are used (no custom PCB)
- Powered via **USB from laptop**
- Data recorded and transmitted to **laptop mass storage**
- Focus on **robust, timestamped environmental data acquisition**

---

## System Objectives

During the airplane test campaign, the system records:
- Temperature, pressure, and humidity
- 3‑axis acceleration
- 3‑axis magnetic field
- GPS position (latitude, longitude, altitude)
- Accurate UTC time

This data is required for **sensor calibration, environmental correlation, and validation of AIRMO measurement results**.

---

## System Architecture

### Control Unit
- **STM32 Nucleo development board** (e.g. NUCLEO‑F767ZI)
- Real‑time deterministic execution
- Interfaces: I2C, SPI, UART, USB CDC

### Sensors & Modules
| Module | Purpose | Interface |
|------|--------|-----------|
| BME280 | Temperature / Pressure / Humidity | I2C |
| ICM‑20948 | Acceleration & Magnetic Field | I2C or SPI |
| u‑blox NEO‑M8N | GPS position & UTC time | UART + PPS |
| DS3231 | Backup real‑time clock | I2C |
| microSD (optional) | Local backup logging | SPI |

---

## Data Flow

1. Sensors are periodically sampled by the STM32
2. Measurements are timestamped using RTC and GNSS time
3. Data is formatted into records (CSV or binary frames)
4. Records are streamed to the laptop via **USB CDC (virtual COM port)**
5. Optionally, data is written to a local microSD card for redundancy

---

## Repository Structure

```
airmo-test-setup/
├─ README.md                # This file
├─ firmware/
│  ├─ CubeIDE/              # STM32CubeIDE project files
│  ├─ src/                  # Application source code
│  ├─ drivers/              # Sensor drivers
│  │  ├─ bme280.c/.h
│  │  ├─ icm20948.c/.h
│  │  └─ neo_m8n.c/.h
│  └─ middleware/           # USB CDC, FATFS, etc.
├─ hardware/
│  ├─ diagrams/             # Block diagrams (PNG, Mermaid)
│  ├─ wiring/               # Pin mapping tables
│  └─ BOM.csv               # Bill of Materials
├─ tools/
│  └─ laptop_logger/        # PC-side data capture script
└─ tests/
   └─ sample_logs/          # Example recorded data
```

---

## Firmware Description

### Features
- STM32 HAL‑based firmware
- Periodic sensor polling
- High‑rate IMU acquisition
- GNSS NMEA parsing
- Accurate timestamping
- USB CDC streaming
- Optional SD card logging

### Build Environment
- **STM32CubeIDE** (recommended)
- STM32 HAL drivers
- USB Device (CDC class)

### Build & Flash
1. Open the project in **STM32CubeIDE**
2. Connect the Nucleo board via USB
3. Build the project
4. Flash using ST‑LINK

---

## Laptop Data Capture

The STM32 enumerates as a **USB virtual COM port**.

Typical workflow:
1. Connect STM32 to laptop
2. Identify COM port (`/dev/ttyACM*` or `COMx`)
3. Run the logger script in `tools/laptop_logger/`
4. Data is saved directly to laptop storage

Example (Linux):
```bash
python3 logger.py /dev/ttyACM0
```

---

## Timing & Synchronization

- Primary time source: **GNSS UTC**
- Backup time source: **DS3231 RTC**
- Optional PPS signal used for precise alignment
- All records include absolute timestamps

---

## Power Supply

- System powered from **USB 5V** (laptop)
- On‑board regulators supply 3.3V to sensors
- No external power supply required

---

## Risks & Mitigations

| Risk | Mitigation |
|----|-----------|
| GNSS signal loss | External antenna + RTC fallback |
| USB disconnect | Optional SD card backup |
| EMI / vibration | Shielded cables, robust connectors |

---

## Future Improvements

- Ethernet streaming (STM32 + LwIP)
- Binary data protocol with CRC
- FreeRTOS task separation
- Automatic sensor calibration
- Health monitoring & watchdog

---

## License & NDA

⚠️ **Confidential**  
This repository and its contents are covered by a **Non‑Disclosure Agreement (NDA)**. Distribution or reuse without authorization is prohibited.

---

## Contact

For questions related to the AIRMO test setup or firmware, please contact the responsible AIRMO project engineer.


