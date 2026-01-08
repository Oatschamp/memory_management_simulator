# Design Document: Memory Management Simulator

## 1. System Overview

This project implements a **user-space memory management simulator** that models
how an operating system allocates, tracks, and accesses memory. The simulator is
designed to emphasize **algorithmic correctness**, **clear abstractions**, and
**integration between memory subsystems**, rather than hardware-level accuracy.

The system includes:
- Dynamic memory allocation
- Fragmentation handling
- Buddy allocation
- Multilevel cache simulation
- Paging-based virtual memory
- Correct end-to-end memory access flow

---

## 2. Physical Memory Representation

### Memory Model

- Physical memory is simulated as a **single contiguous region of bytes**
- Addresses are **byte-addressable**
- Memory size is fixed during initialization
- Address ranges are displayed in **hexadecimal format**

### Design Assumptions

- Single-process environment
- No real hardware interaction
- No timing or latency simulation
- Memory access is symbolic and used only for correctness validation

---

## 3. Contiguous Allocation Design

### Block Structure

Physical memory is divided into blocks represented using a **doubly linked list**.
Each block stores:

- Start address
- Block size
- Free or allocated status
- Unique block ID
- Pointers to adjacent blocks

This structure allows efficient splitting and merging.

### Allocation Workflow

1. Traverse the block list based on selected strategy
2. Select a suitable free block
3. Split the block if it is larger than required
4. Mark allocated portion as used
5. Assign a block ID

### Deallocation Workflow

1. Locate block using block ID
2. Mark block as free
3. Merge adjacent free blocks (coalescing)
4. Update fragmentation statistics

---

## 4. Allocation Strategies

The simulator supports multiple allocation strategies that can be selected at runtime.

### First Fit
- Chooses the first free block that is large enough
- Fast allocation
- Can lead to early fragmentation

### Best Fit
- Chooses the smallest free block that satisfies the request
- Reduces immediate waste
- Can increase fragmentation over time

### Worst Fit
- Chooses the largest available free block
- Attempts to preserve medium-sized blocks
- Can lead to inefficient space usage

These strategies allow comparative study of fragmentation behavior.

---

## 5. Buddy Allocation System

### Overview

A **Buddy Memory Allocator** is implemented as an alternative to contiguous allocation.
It uses power-of-two block sizes and separate free lists.

### Key Properties

- Total memory size is a power of two
- Allocation sizes are rounded up to nearest power of two
- Each block has a unique buddy
- Buddy address is computed using XOR

### Allocation Process

1. Round request size to power of two
2. Locate smallest available block
3. Recursively split larger blocks if needed
4. Allocate block

### Deallocation Process

1. Identify buddy using XOR
2. Merge if buddy is free
3. Repeat recursively

### Fragmentation

- External fragmentation is minimized
- **Internal fragmentation is explicitly tracked**

---

## 6. Cache Subsystem Design

### Cache Hierarchy

The simulator models a **two-level cache hierarchy**:

- L1 Cache
- L2 Cache

Each cache level is configured with:
- Cache size
- Block size
- Associativity

### Cache Organization

- Cache is divided into **sets**
- Each set contains multiple cache lines
- Each cache line stores:
  - Valid bit
  - Tag
  - Replacement metadata

---

## 7. Cache Replacement Policies

The cache subsystem supports multiple replacement policies:

### FIFO (First-In, First-Out)
- Oldest cache line is evicted first
- Simple and predictable

### LRU (Least Recently Used)
- Evicts the least recently accessed line
- Approximates temporal locality

### LFU (Least Frequently Used)
- Evicts the least frequently accessed line
- Tracks access counts

Each cache level independently records hit and miss statistics.

---

## 8. Virtual Memory Design

### Paging Model

- Virtual memory is divided into pages
- Physical memory is divided into frames
- Page size is configurable

### Page Table

Each page table entry stores:
- Valid bit
- Physical frame number
- Replacement metadata (FIFO / LRU)

### Address Translation

Virtual address is divided into:
- Virtual page number
- Page offset

Translation produces a physical address.

---

## 9. Page Fault Handling

- If page is present → Page Hit
- If page is absent → Page Fault

On a page fault:
1. Allocate free frame if available
2. Otherwise, evict a victim page
3. Update page table
4. Load new page

Supported page replacement policies:
- FIFO
- LRU

---

## 10. Integrated Memory Access Flow

The simulator enforces the correct operating system access order:

Virtual Address
→ Page Table Translation
→ Physical Address
→ L1 Cache
→ L2 Cache
→ Main Memory (symbolic)


Key design principle:
- **Caching always operates on physical addresses**
- Virtual memory logic is independent of cache logic

---

## 11. Metrics and Statistics

The simulator tracks and reports:

- Allocation success and failure
- Used and free memory
- Memory utilization
- External fragmentation (contiguous allocators)
- Internal fragmentation (buddy allocator)
- Cache hits and misses
- Page hits and page faults

These metrics allow performance and behavior analysis.

---

## 12. Design Limitations

To keep the simulator focused and understandable:

- No Translation Lookaside Buffer (TLB)
- No dirty bits or write-back policies
- No instruction cache
- No multi-process isolation
- No real timing or latency modeling

These simplifications preserve conceptual clarity.

---

## 13. Conclusion

This simulator provides a structured and accurate model of how an operating system:

- Allocates and frees memory
- Manages fragmentation
- Implements buddy allocation
- Handles paging and page faults
- Uses multilevel caches for performance
- Integrates memory subsystems correctly

The design prioritizes correctness, modularity, and educational value.

