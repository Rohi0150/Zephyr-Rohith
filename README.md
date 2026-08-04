# Zephyr RTOS Development Repository

A collection of **Zephyr RTOS applications, experiments, and embedded system projects** developed while exploring real-time operating systems, device drivers, hardware integration, and embedded software architecture.

This repository contains hands-on implementations covering:

- Zephyr Kernel concepts
- Multi-threading
- Synchronization mechanisms
- DeviceTree configuration
- Peripheral drivers
- Sensor integration
- Performance benchmarking
- STM32 based embedded applications


## About Zephyr RTOS

Zephyr is a scalable open-source Real-Time Operating System designed for resource-constrained embedded systems.

This repository focuses on understanding and implementing Zephyr concepts through practical hardware projects rather than only theoretical examples.


# Repository Overview

```
Zephyr-Rohith

│
├── benchmark/
│   │
│   ├── src/
│   │   ├── main.c
│   │   ├── matrix15.c
│   │   ├── mpu6050.c
│   │   ├── pps.c
│   │   ├── sdcard.c
│   │   ├── timer2.c
│   │   └── uart_benchmark.c
│   │
│   ├── include/
│   │   ├── matrix15.h
│   │   ├── mpu6050.h
│   │   ├── pps.h
│   │   ├── sdcard.h
│   │   ├── timer2.h
│   │   └── uart_benchmark.h
│   │
│   ├── prj.conf
│   └── CMakeLists.txt
│
└── README.md
```


# Projects


## Benchmarking Application

Location:

```
benchmark/
```

A multi-threaded Zephyr application designed to evaluate RTOS performance using different workloads.

Implemented benchmarks:

| Module | Description |
|--------|-------------|
| Matrix Benchmark | CPU computation performance |
| PPS Benchmark | Hardware timer accuracy and jitter measurement |
| MPU6050 Benchmark | I2C sensor communication performance |
| UART Benchmark | Serial communication overhead |
| SD Card Benchmark | Filesystem and storage performance |


More details:

➡️ [Benchmark Application README](benchmark/README.md)



# Zephyr Concepts Implemented


## Kernel Programming

Implemented:

- Thread creation
- Thread priorities
- Stack management
- Kernel scheduling
- Semaphores
- Interrupt synchronization


Example architecture:

```
                Zephyr Kernel

                      |
        +-------------+-------------+
        |             |             |

   Matrix Thread  MPU Thread   PPS Thread

        |             |             |

    CPU Test     Sensor Data   Timer Capture

                      |

                SD Logging Thread
```


---

# Hardware Platforms

Experiments are performed using STM32 based development boards.


## Tested Hardware

- STM32 NUCLEO-F411RE
- STM32H725ZGT6


## Peripheral Experience

| Peripheral | Usage |
|-|-|
| GPIO | Interrupts and control signals |
| UART | Communication and benchmarking |
| I2C | Sensor integration |
| SPI | External devices |
| Timers | Input capture and timing analysis |
| SD Card | Data logging |


---

# Development Environment


## Software

```
OS:
Ubuntu Linux

RTOS:
Zephyr 4.4.1

SDK:
Zephyr SDK 0.17.x

Build System:
West + CMake

Compiler:
arm-zephyr-eabi-gcc
```


---

# Learning Journey


This repository documents my progress in embedded RTOS development:

```
Bare Metal
     |
     v
STM32 Peripheral Programming
     |
     v
RTOS Fundamentals
     |
     v
Zephyr Kernel
     |
     v
DeviceTree & Drivers
     |
     v
Embedded Applications
```


---

# Future Work

Planned additions:

- Custom Zephyr board support
- DeviceTree development
- Sensor driver development
- More RTOS benchmarks
- Power optimization studies
- Open-source Zephyr contributions


---

# Author

## Rohith A

Embedded Systems Developer

Areas of Interest:

- Zephyr RTOS
- Embedded Linux
- STM32 Development
- Device Drivers
- Real-Time Systems


---

# License

This repository is intended for learning, experimentation, and open-source collaboration.
