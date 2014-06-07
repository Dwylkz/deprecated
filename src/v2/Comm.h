#ifndef DAC_V2_COMM_H_
# define DAC_V2_COMM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <pthread.h>

#include <Error.h>
#include <Type.h>

#define DacFree(old, bud) (free(*(old)), *(old) = (bud))

#define DacMax(lhs, rhs) ((lhs) > (rhs)? (lhs): (rhs))
#define DacMin(lhs, rhs) ((lhs) < (rhs)? (lhs): (rhs))

// Memory Utils
void* DacRealloc(void* old, int size);

void DacRangeFree(void* lower, void* upper, DacFree dac_free); // Random Utils
int DacRandomInt(int lower, int upper);

int* DacRandomInts(int lower, int upper, int length);

char* DacRandomString(int lower, int upper, int length);

char** DacRandomStrings(int lower, int upper, int length, int size);

// String Utils
char* DacReplace(const char* str,
                 const char* pat,
                 const char* sub,
                 const int do_all);

char* DacReplaceFree(char* str,
                     const char* pat,
                     const char* sub,
                     const int do_all);

char* DacVFormat(const char* format, va_list ap);

char* DacFormat(const char* format, ...);

char* DacEsc2Raw(const char* esc);

char* DacEsc2RawFree(char* esc);

char* DacRaw2Esc(const char* raw);

char* DacRaw2EscFree(char* raw);

char* DacFirstGraph(const char* str);

void DacPutsAndFree(char* str);

// Bit Utils

inline int DacSetBit(int self, int vane, int bit) {return (self&~(1<<vane))|(bit<<vane);};
inline int DacGetBit(int self, int vane) {return self>>vane&1;};

#endif
