# Spell Checker in C — Data Structures & Performance Analysis

A spell-checking application developed in **C** as part of an Algorithms and Programming project at **Grenoble INP – Phelma (2024)**.

Developed by a team of three engineering students, the project explores how different data structures affect search efficiency, memory consumption, and execution time.

## Project Overview

The application reads two input files:

- A dictionary containing valid words.
- A text file to analyze.

It identifies and displays words that are not present in the dictionary.

Beyond implementing a functional spell checker, the main objective was to **design, implement, benchmark, and compare different data structures** to determine their efficiency for large datasets.

## Data Structures & Algorithms

The project implements several approaches to dictionary storage and word lookup:

| Data Structure | Main Characteristics |
|---|---|
| Dynamic Array | Sequential search and amortized constant-time insertion |
| Sorted Dynamic Array | Binary search for faster word lookup |
| Hash Table | Hash-based indexing with collision handling |
| Patricia Tree | Prefix-based word storage |
| Compressed Tree | Memory optimization through shared suffixes |
| Trie | Character-by-character word storage |

Additional implementations include:

- **Heap Sort:** Generic sorting using `void*`, function pointers, and pointer arithmetic.
- **Linked Lists:** Singly linked and circular list implementations.
- **Generic Data Structures:** Reusable implementations using pointers and C macros.

## Performance Analysis

We benchmarked the different data structures to evaluate their behavior as dictionary size increased.

The analysis focused on:

- Dictionary construction time.
- Word insertion time.
- Search efficiency and algorithmic complexity.
- Memory consumption.
- Performance trade-offs between different implementations.

Tests covered datasets ranging from **100 to 300,000 elements**.

### Key Findings

- Hash tables provide efficient average-case lookup when appropriately sized.
- Patricia trees and tries offer prefix-based storage and lookup.
- Implementation choices significantly affect memory consumption, even when theoretical time complexities are similar.
- Compressed structures introduce additional memory-management challenges, particularly when multiple pointers reference shared nodes.

The project highlighted the importance of considering both **theoretical complexity and experimental performance** when selecting data structures.

## Technologies

- **Language:** C
- **Build System:** Make / Makefile
- **Debugging:** GDB
- **Memory Safety:** Valgrind, AddressSanitizer, UndefinedBehaviorSanitizer
- **Version Control:** Git
- **Testing:** Automated tests, assertions, and regression checks

## Building and Running

### Prerequisites

- GCC or a compatible C compiler
- Make
- A Unix/Linux development environment

### Build the Project

```bash
make
```

### Run the Spell Checker

The project includes a Makefile target for running the spell checker on a sample literary text:

```bash
make testTempsPerdu
```

### Run Tests

Compile the test suite:

```bash
make tests
```

Run automated tests with memory and undefined-behavior checks:

```bash
make tests@check
```

Run tests using GDB:

```bash
make tests@debug
```

Clean generated files:

```bash
make clean
```

## Testing & Memory Safety

The project includes automated tests covering both valid and invalid inputs.

Testing practices include:

- Assertions to validate expected behavior.
- Error handling and invalid-argument testing.
- Memory leak detection.
- Undefined-behavior detection.
- Regression testing across multiple data structures.

The final implementation passed the project's test suite, with no memory leaks detected during Valgrind testing.

## My Contributions

My main contributions included:

- Implementing data structures and sorting algorithms in C.
- Working on generic algorithms and memory management.
- Participating in performance analysis and benchmarking.
- Contributing to technical documentation and the final report.
- Collaborating through Git branches and code integration.

## Challenges & Lessons Learned

One significant challenge was adapting an existing singly linked list implementation into a circular linked list.

Because several components depended on the original structure, this change required modifying multiple functions and associated tests.

This experience highlighted the importance of:

- Defining clear interfaces before implementation.
- Designing reusable and maintainable data structures.
- Anticipating dependencies between software components.
- Validating changes through automated testing.

The project also demonstrated how experimental benchmarking can reveal performance differences that are not immediately apparent from asymptotic complexity alone.

## Academic Context

**Institution:** Grenoble INP – Phelma  
**Course:** Algorithms and Programming  
**Date:** December 2024  
**Team:** 3 engineering students

**Contributors:**
- Clément Yahia-Amar
- Noé Prevel
- Mathis Hurstel

---

*Academic project developed for educational purposes.*
