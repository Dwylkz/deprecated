#ifndef DAC_V2_TYPE_H_
# define DAC_V2_TYPE_H_

typedef void* (*DacCopy)(void*);
typedef void (*DacFree)(void*);
typedef int (*DacVs)(void*, void*);
typedef uint32_t (*DacHash)(void*);
typedef char* (*DacPush)(void*);
typedef char* (*DacPull)(const char*, void*);

typedef struct DacType {
  DacCopy Copy;
  DacFree Free;
  DacVs Vs;
  DacHash Hash;
  DacPush Push;
  DacPull Pull;
} DacType;

#endif
