# CPU Process Scheduling Simulator

This is a C++ program that simulates various process scheduling algorithms. It includes implementations of the following algorithms:

1. **First Come First Serve (FCFS)**
2. **Shortest Job First (SJF)**
3. **Shortest Remaining Time (SRT)**
4. **Round Robin (RR)**
5. **Priority Scheduling (Preemptive)**

The program allows the user to choose between these scheduling types and provides details of the execution of each process, such as start time, end time, and the order of execution.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Installation](#installation)
- [How to Use](#how-to-use)
- [Scheduling Algorithms Explained](#scheduling-algorithms-explained)
  - [First Come First Serve (FCFS)](#first-come-first-serve-fcfs)
  - [Shortest Job First (SJF)](#shortest-job-first-sjf)
  - [Shortest Remaining Time (SRT)](#shortest-remaining-time-srt)
  - [Round Robin (RR)](#round-robin-rr)
  - [Priority Scheduling](#priority-scheduling)
- [Example](#example)

## Features

- Simulates 5 process scheduling algorithms.
- Displays process execution order, start times, and end times.
- Supports both non-preemptive and preemptive algorithms.
- Provides detailed information for each process.

## Getting Started

### Installation

To install and run the project locally, follow these steps:

#### Step 1: Clone the Repository

Clone this GitHub repository to your local machine using the following command:

```bash
git clone https://github.com/Aarav-Shah-175/CPU_Scheduling.git
```

#### Step 2: Navigate to the Project Directory

Change into the project directory:

```bash
cd CPU_Scheduling
```

#### Step 3: Compile the Program

Use the following command to compile the C++ program:

```bash
g++ -o Scheduling Scheduling.cpp
```

This will generate an executable file called `Scheduling`.

Alternatively, if you have `make` installed, you can use the provided `Makefile`:

```bash
make
```

#### Step 4: Run the Program

After compilation, run the program using:

```bash
./Scheduling
```

## How to Use

1. After running the program, you will be prompted to choose a scheduling algorithm from the following:
    - **1** for FCFS
    - **2** for SJF
    - **3** for SRT
    - **4** for Round Robin (RR)
    - **5** for Priority Scheduling (Preemptive)

2. For each scheduling type, you will need to provide:
    - Process ID
    - Arrival Time
    - Burst Time
    - (Priority, if applicable for Priority Scheduling)

3. For Round Robin, you'll also need to enter the time quantum.

4. The program will display the process execution order, start time, and end time for each process.

## Scheduling Algorithms Explained

### First Come First Serve (FCFS)

- **FCFS** is the simplest scheduling algorithm.
- Processes are executed in the order they arrive.
- It is non-preemptive, meaning once a process starts, it will run to completion.

### Shortest Job First (SJF)

- **SJF** selects the process with the smallest burst time to execute next.
- This is a non-preemptive algorithm.
- If two processes have the same burst time, the one that arrived first is executed.

### Shortest Remaining Time (SRT)

- **SRT** is a preemptive version of SJF.
- It selects the process with the smallest remaining burst time.
- If a new process arrives with a smaller burst time than the remaining time of the current process, it will preempt the current process.

### Round Robin (RR)

- **RR** uses a time quantum, which is a fixed amount of CPU time for each process.
- Each process is executed for a quantum, then placed back in the queue if it hasn't finished.
- This is a preemptive algorithm and works well in time-sharing systems.

### Priority Scheduling

- **Priority Scheduling** selects the process with the highest priority (smallest number represents the highest priority).
- It is preemptive, so if a new process with a higher priority arrives, it will preempt the current running process.

## Example

### Sample Input for FCFS
```
Number of Processes: 3
Process Details:
PID    Arrival Time    Burst Time
1      0               4
2      1               3
3      2               2
```

### Sample Output
```
------FCFS Scheduling------

Process Execution Order:

Process ID    Start Time    End Time
------------------------------------
1             0             4
2             4             7
3             7             9
```

------------------------------
