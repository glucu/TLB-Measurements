#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

volatile int* alloc_array(int num_pages, int jump) {
  volatile int *array = calloc(num_pages * jump, sizeof(int));
  if(!array) {
    perror("calloc");
    exit(EXIT_FAILURE);
  }
  return array;
}

int main(int argc, const char *argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Usage: %s <NUMPAGES> <NUMTRIALS>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	if(sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
		perror("sched_setaffinity");
		exit(EXIT_FAILURE);
	}

	const int num_pages = atoi(argv[1]);
	const int num_trials = atoi(argv[2]);
	if(num_pages <= 0 || num_trials <= 0) {
		perror("atoi");
		exit(EXIT_FAILURE);
	}

	const int page_size = (int)sysconf(_SC_PAGESIZE);
	const int jump = page_size / sizeof(int);
	volatile int *array = alloc_array(num_pages, jump);
	struct timespec begin, end;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	for(int trial = 0; trial < num_trials; ++trial) {
		for(int i = 0; i < num_pages * jump; i += jump) {
			array[i] += 1;
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);

	const double total_time_ns = (end.tv_sec - begin.tv_sec) * 1E9 + (end.tv_nsec - begin.tv_nsec);
	const double avg_time_ns = total_time_ns / (num_trials * num_pages);
	printf("Pages %4d | Time %7.2f (nanoseconds)\n", num_pages, avg_time_ns);

	free((void*)array);
	exit(EXIT_SUCCESS);
}
