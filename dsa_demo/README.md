# Data Structures Demo

This is a standalone C11 terminal program for a college Data Structures and Algorithms practical demonstration. It does not use CMake, external libraries, or any code from the parent project.

It demonstrates:

- An array-based stack (push, pop, peek, display, empty/full checks) and LIFO behavior.
- An array-based circular queue (enqueue, dequeue, display, empty/full checks) and FIFO behavior.
- Linear search with each sequential comparison shown.
- Iterative binary search with range changes shown and ascending-order validation.
- Bubble, selection, insertion, merge, and quick sort, with useful intermediate states.

## Compile

From the repository root:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic dsa_demo/dsa_demo.c -o dsa_demo/dsa_demo
```

## Run

```sh
./dsa_demo/dsa_demo
```

## Suggested presentation demonstrations

1. **Stack / LIFO:** Push `10`, `20`, and `30`; then pop once. Explain that `30`, the last value pushed, is the first value removed. Push until the capacity of five is reached to show overflow.
2. **Circular queue / FIFO:** Enqueue `10`, `20`, `30`, `40`; dequeue twice; then enqueue `50`, `60`. The displayed array slots show the rear wrapping around and reusing the freed positions.
3. **Linear search:** Use `[7, 3, 9, 2, 5]` and search for `2`, so each element checked before index 3 is visible.
4. **Binary search:** Use the sorted array `[2, 4, 6, 8, 10, 12, 14]` and search for `12`. First try an unsorted array if you want to demonstrate why validation is necessary.
5. **Sorting:** Use `[5, -2, 5, 1, 0]` to show duplicates and negative values. Run more than one algorithm from the sorting submenu; each starts with the same original array.
