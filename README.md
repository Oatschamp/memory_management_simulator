# Memory Management Simulator

## Overview

This project is a **Memory Management Simulator** implemented in C++ that models
how an operating system manages memory internally. The simulator focuses on
core OS concepts such as memory allocation, fragmentation, paging-based virtual
memory, and multilevel caching.

The goal of this project is to simulate **correct operating-system behavior**
using user-space code, rather than interacting with real hardware.

---

## Objectives

The simulator is designed to:

- Understand dynamic memory allocation strategies
- Observe internal and external fragmentation
- Simulate allocation and deallocation at runtime
- Model multilevel CPU cache behavior
- Implement virtual memory using paging
- Enforce the correct memory access pipeline

---

## Key Features

### Physical Memory Simulation

- Physical memory is modeled as a **contiguous byte-addressable region**
- Memory is dynamically divided into blocks
- Each block stores:
  - Start address
  - Block size
  - Allocation status
  - Block identifier
- The current memory layout can be displayed using a dump command

---

### Dynamic Memory Allocation

The simulator supports heap-style allocation:

- `malloc <size>` allocates memory
- `free <id>` deallocates memory
- Adjacent free blocks are **automatically merged** to reduce fragmentation

---

### Allocation Strategies

The following allocation strategies are supported and can be switched at runtime:

- **First Fit** – selects the first free block large enough
- **Best Fit** – selects the smallest free block that fits
- **Worst Fit** – selects the largest available free block

These strategies allow comparison of fragmentation patterns.

---

### Fragmentation and Statistics

The simulator tracks and reports:

- Total memory
- Used memory
- Free memory
- Memory utilization
- External fragmentation (contiguous allocators)
- Internal fragmentation (buddy allocator)
- Allocation success and failure counts

Statistics are displayed using the `stats` command.

---

### Buddy Memory Allocation

A **Buddy Allocation System** is implemented as an alternative allocator.

Characteristics:

- Memory size is a power of two
- Allocation sizes are rounded up to the nearest power of two
- Free lists are maintained for each block size
- Buddy blocks are identified using XOR-based address computation
- Recursive splitting and coalescing is supported
- Internal fragmentation is explicitly tracked

This allocator reflects techniques used in real operating systems.

---

### Multilevel Cache Simulation

The simulator models a **two-level CPU cache hierarchy**:

- Level 1 (L1) cache
- Level 2 (L2) cache

Each cache level supports:

- Configurable cache size
- Configurable block size
- Configurable associativity (direct-mapped or set-associative)

---

### Cache Replacement Policies

The following cache replacement policies are implemented:

- FIFO (First-In, First-Out)
- LRU (Least Recently Used)
- LFU (Least Frequently Used)

Each cache level independently tracks hits, misses, and hit ratios.

---

### Virtual Memory Simulation

Virtual memory is simulated using paging:

- Virtual address space is divided into pages
- Physical memory is divided into frames
- A page table maps virtual pages to physical frames
- Page table entries include:
  - Valid bit
  - Frame number
  - Replacement metadata
- Page hits and page faults are tracked
- FIFO and LRU page replacement policies are supported

---

### Integrated Memory Access Pipeline

The simulator enforces the correct OS-level memory access order:

Virtual Address
→ Page Table
→ Physical Address
→ L1 Cache
→ L2 Cache
→ Main Memory (symbolic)


This integration ensures architectural correctness across all components.

---

## Project Structure
```
memory-simulator/
├── src/
│ ├── allocator/
│ ├── buddy/
│ ├── cache/
│ ├── virtual_memory/
│ └── main.cpp
├── include/
├── tests/
├── docs/
│ ├── design.md
│ └── run_instructions.txt
├── Makefile
└── README.md
```


---

## Build Instructions 
Following file contains all commands and their use.
[How to run](docs/run_instructions.txt)

## Demo Video
[video](https://drive.google.com/file/d/1vt0lxNvMO704G1xz1DDdvwCQ3Tp3Z8jY/view?usp=sharing)
