# Memory Management Simulator — Design Document

## 1. Overview
This project simulates OS-level memory management in user space, including
dynamic allocation, cache hierarchies, and virtual memory with paging.

## 2. Physical Memory Model
- Contiguous byte-addressable memory
- Explicit block headers
- Linked-list representation
- Coalescing on free

## 3. Allocation Strategies
- First Fit
- Best Fit
- Worst Fit
- Block splitting and merging
- Comparison via fragmentation metrics

## 4. Buddy Allocation System
- Power-of-two memory requirement
- Size rounding to nearest power of two
- Free lists per block size
- XOR-based buddy computation
- Internal fragmentation tracking

## 5. Cache Simulation
- Multilevel cache (L1/L2)
- Configurable size, block size, associativity
- Replacement policies: FIFO, LRU, LFU
- Hit/miss tracking per level

## 6. Virtual Memory
- Paging-based virtual memory
- Page tables with valid bit and metadata
- Replacement policies: FIFO, LRU
- Page fault handling
- Page hit/fault statistics

## 7. Integration Order
Virtual Address → Page Table → Physical Address → Cache → Memory

## 8. Metrics & Statistics
- Internal fragmentation
- External fragmentation
- Allocation success/failure
- Memory utilization
- Cache hits/misses
- Page hits/faults

## 9. Limitations
- Single-process simulation
- Symbolic disk latency
- Buddy allocator tracked independently from contiguous memory stats
