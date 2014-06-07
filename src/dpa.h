#ifndef DPA_H_
#define DPA_H_

#define NDEBUG 1

#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dac/dac.h>
#include <dac/Exception.h>
#include <dac/Map.h>
#include <dlex2/DFA.h>

// Global exception
Exception *error;
// Lexcical definition
DFA *dfa;


#endif // dpa.h
