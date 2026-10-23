Round-Robin Scheduling with a Circular Queue (front == rear approach)
=====================================================================

Files
-----
index.html          Interactive working model. Double-click to open in any
                    browser (Chrome, Edge, Firefox, Safari). Works offline.
circular_queue.c    C program for the same approach (SIZE = 6, capacity 5).
output.png          Screenshot of the C program output.

How to use the working model
----------------------------
1. Open index.html.
2. Click "Enqueue process" five times (queue becomes Full).
3. Click it once more to see Overflow.
4. Click "Execute and remove", then "Enqueue process" again:
   the rear pointer wraps to index 0.
5. Use "Run one slice" / "Run all" for round-robin (set the time quantum).
6. Remove until empty, then remove once more to see Underflow.

How to run the C program
------------------------
Windows (MinGW):   gcc circular_queue.c -o circular_queue.exe
                   circular_queue.exe
Linux / macOS:     gcc circular_queue.c -o circular_queue
                   ./circular_queue

Rules used
----------
Empty: front == rear
Full : (rear + 1) % SIZE == front
One slot is always kept empty, so usable capacity = SIZE - 1.
