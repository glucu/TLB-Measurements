# TLB-Measurements
The program measures the size and cost of accessing a TLB.

## Constraints
The `tlb.c` program is not portable. It runs on a 64-bit GNU/Linux machine. There are some caveats to keep in mind:
1. `sched_setaffinity`: In order to bind the process to a single core. Each core has its own TLB hierarchy. This is to assure the scheduler does not schedule the process to different cores and thus resets the TLB entries for that process.
2. `gcc`: In order to prevent the C compiler from applying optimization to the program. The flags I passed are: `-O0` and `-g`.
3. `Demand Zeroing`: In order to prevent the extra overhead by accessing the array for the first time. This is dealt by using `calloc` which sets the elements to zeros.

```bash
$ ./test.sh 10 10000000
$ pl plot_tlb.pl -png
$ open plot_tlb.png
```
![alt text](https://github.com/glucu/TLB-Measurements/blob/main/plot_tlb.png?raw=true)
