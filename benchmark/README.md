# Zephyr RTOS Benchmark Suite

A multi-threaded benchmarking application developed using **Zephyr RTOS** to evaluate the execution performance of different embedded workloads including CPU computation, communication interfaces, sensor acquisition, timing accuracy, and storage operations.

The project demonstrates Zephyr kernel concepts such as:

- Threads
- Semaphores
- Interrupt-driven execution
- DeviceTree-based peripheral configuration
- I2C communication
- UART communication
- SPI SD Card filesystem access
- Hardware timer capture
- Cycle-based performance measurement


## Overview

This benchmark application runs multiple independent tasks concurrently on an STM32F411RE platform.

Each workload is implemented as an individual Zephyr thread and measured using the Zephyr cycle counter API:

```c
k_cycle_get_64()
```

The measured CPU cycles are converted into execution time using:

```c
k_cyc_to_us_floor64()
```

This provides a low-level view of task execution performance.


## System Architecture

```
                 +----------------------+
                 |      Zephyr RTOS     |
                 +----------+-----------+
                            |
          +-----------------+----------------+
          |                 |                |
          v                 v                v

   Matrix Thread       PPS Thread       MPU6050 Thread
   CPU Benchmark       Timing Test      Sensor Read

          |                 |                |
          |                 |                |
          v                 v                v

    UART Thread                         SD Card Thread
 Communication Test                  Data Logging Test

```


## Benchmark Modules


### 1. Matrix Computation Benchmark

File:

```
src/matrix15.c
```

Measures floating-point matrix multiplication performance.

Operation:

```
C = A × B
```

Features:

- 15x15 matrix multiplication
- Cycle measurement
- Minimum execution time
- Maximum execution time
- Average execution cycles


Example output:

```
Matrix Operation:

Iteration : 20
Cycles    : 175000
Time      : 1822 us
Min time  : 174500
Max time  : 176300
Average   : 175400
```


---

## 2. PPS Timing Benchmark

Files:

```
src/pps.c
src/timer2.c
```

Measures external pulse timing accuracy using STM32 hardware timer input capture.

Features:

- Hardware timer capture
- Interrupt-based synchronization
- Period measurement
- Jitter calculation


Measured parameters:

```
Capture Value
Pulse Period
Timing Jitter
```


---

## 3. MPU6050 I2C Benchmark

Files:

```
src/mpu6050.c
```

Measures I2C communication performance with MPU6050 IMU sensor.

Features:

- Interrupt driven sensor acquisition
- I2C burst read
- Cycle measurement
- Semaphore synchronization


Data flow:

```
MPU6050 INT
      |
      v
GPIO Interrupt
      |
      v
Semaphore Give
      |
      v
MPU Thread
      |
      v
I2C Read
```


---

## 4. UART Benchmark

File:

```
src/uart_benchmark.c
```

Measures UART transmission overhead.

Test:

```
100 bytes transmission
```

Measured:

- CPU cycles
- Transmission time


---

## 5. SD Card Logging Benchmark

File:

```
src/sdcard.c
```

Demonstrates filesystem integration with Zephyr.

Features:

- SPI SD Card interface
- FAT filesystem support
- Binary sensor data logging


Data flow:

```
MPU6050
   |
   v
IMU Buffer
   |
Semaphore
   |
   v
SD Thread
   |
   v
imu.bin
```


---

# Thread Configuration

| Thread | Priority | Purpose |
|--------|----------|---------|
| Matrix Thread | 5 | CPU benchmark |
| PPS Thread | 4 | Timing measurement |
| MPU Thread | 3 | Sensor acquisition |
| UART Thread | 6 | Communication benchmark |
| SD Thread | 7 | Storage logging |


---

# Synchronization Mechanisms

The project uses Zephyr kernel synchronization primitives.


## Semaphores


### PPS Semaphore

```c
K_SEM_DEFINE(pps_sem,0,1);
```

Used for:

```
Timer ISR
    |
    v
PPS Thread
```


### MPU Semaphore

```c
K_SEM_DEFINE(mpu_sem,0,1);
```

Used for:

```
MPU6050 Interrupt
        |
        v
 MPU6050 Thread
```


### SD Semaphore

```c
K_SEM_DEFINE(sd_sem,0,1);
```

Used for:

```
Sensor Data
     |
     v
SD Card Thread
```


---

# Hardware Platform

## Tested Board

```
STM32 NUCLEO-F411RE
```

## Peripherals Used

| Peripheral | Function |
|------------|----------|
| I2C1 | MPU6050 Sensor |
| USART6 | UART Benchmark |
| SPI3 | SD Card |
| TIM2 | PPS Input Capture |
| GPIO Interrupt | MPU6050 Data Ready |


---

# Project Structure

```
benchmark/

├── CMakeLists.txt
├── prj.conf

├── include
│   ├── matrix15.h
│   ├── mpu6050.h
│   ├── pps.h
│   ├── sdcard.h
│   ├── timer2.h
│   └── uart_benchmark.h

└── src
    ├── main.c
    ├── matrix15.c
    ├── mpu6050.c
    ├── pps.c
    ├── sdcard.c
    ├── timer2.c
    └── uart_benchmark.c
```


---

# Build Instructions


## Setup Zephyr Environment

```bash
west init ~/zephyrproject
cd ~/zephyrproject

west update
```


Activate environment:

```bash
source .venv/bin/activate
```


## Build Application

From the benchmark directory:

```bash
west build -b nucleo_f411re
```


## Flash Board

```bash
west flash
```


## Monitor Output

```bash
west espressif monitor
```

or using UART terminal:

```
115200 baud
8N1
```


---

# Configuration

The application uses:

```
Zephyr Version:
4.4.1

Board:
STM32 NUCLEO-F411RE

SDK:
Zephyr SDK 0.17.x
```


---

# Future Improvements

- Add configurable matrix sizes
- Add CPU load measurement
- Add context switching benchmark
- Add mutex and message queue benchmarks
- Add power consumption measurements
- Add automated benchmark report generation


---

# Author

**Rohith A**

Embedded Systems | Zephyr RTOS | STM32 Development

