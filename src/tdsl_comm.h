#ifndef TDSL_COMM_H_
# define TDSL_COMM_H_

#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TDSL_INFO(msg, ...) \
    do {\
      fprintf(stderr, "%s:%s:%d: ", __FILE__, __func__, __LINE__);\
      fprintf(stderr, msg,##__VA_ARGS__);\
      fputs(".\n", stderr);\
    } while (0)

#define TDSL_GOTO(tag, msg, ...) \
    do {TDSL_INFO(msg,##__VA_ARGS__); goto tag;} while (0)

#define TDSL_ESYS "%s", strerror(errno)
#define TDSL_EMAP "map failed"
#define TDSL_EREDUCE "reduce failed"

typedef int (*tdsl_compare_i)(void*, void*);

typedef uint32_t (*tdsl_hash_i)(void*);

typedef int (*tdsl_map_i)(void*);

typedef int (*tdsl_probe_i)(void*);

typedef void* (*tdsl_binary_i)(void*, void*);

#endif
