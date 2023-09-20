# cop4600-assignment2-memory-page-replacement-simulator

## Introduction

This repository contains a memory page replacement simulator that evaluates the performance of different page replacement algorithms using real memory traces from applications. The simulator is designed to help you understand the costs of page replacement algorithms and observe their effects on system performance.

## Project Overview

In this project, you will find:

- C++ code implementing the memory simulator.
- Memory traces from real applications (bzip.trace and sixpack.trace).
- Different page replacement algorithm implementations: FIFO and LRU.
- A makefile for easy compilation.
- Detailed instructions on how to run the simulator.

## Getting Started

To run the memory simulator, follow these steps:

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/your-username/Memory-Page-Replacement-Simulator.git
   ```

2. Navigate to the project directory:

   ```bash
   cd Memory-Page-Replacement-Simulator
   ```

3. Compile the simulator:

   ```bash
   g++ -o memsim memsim.cpp policies.hpp lru.cpp fifo.cpp dataStructures.hpp dataStructures.cpp -std=c++11
   ```

4. Run the simulator with the desired memory trace, number of frames, and policy:

   ```bash
   ./memsim tracefile nFrames policy [percentage] quiet/debug
   ```

   - `tracefile`: Name of the memory trace file (e.g., sixpack.trace or bzip.trace).
   - `nFrames`: Number of memory frames.
   - `policy`: Page replacement policy (e.g., fifo or lru).
   - `[percentage]` (only for the "vms" policy): Percentage of total program memory to be used in the secondary buffer.
   - `quiet/debug`: Choose "quiet" for silent mode or "debug" for debug mode.

## Project Structure

The project is organized as follows:

- `memsim.cpp`: Main interface of the simulator.
- `dataStructures.hpp` and `dataStructures.cpp`: Data structures used by the simulator.
- `policies.hpp`: Declarations of page replacement policies.
- `fifo.cpp` and `lru.cpp`: Implementations of FIFO and LRU page replacement policies.
- `bzip.trace` and `sixpack.trace`: Memory traces from real applications.
- `makefile`: Makefile for easy compilation.

Feel free to use this README template as a starting point for your repository documentation. Good luck with your project!
