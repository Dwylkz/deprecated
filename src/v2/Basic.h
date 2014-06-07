#ifndef DAC_V2_BASIC_H_
# define DAC_V2_BASIC_H_

#include <Comm.h>

// DacString
void* DacStringCopy(void* self);
void DacStringFree(void* self);
int DacStringVs(void* self, void* that);
uint32_t DacStringHash(void* self);
char* DacStringPush(void* self);
char* DacStringPull(const char* flow, void* self);
extern DacType* DacStringType;

// DacInt
void* DacIntCopy(void* self);
void DacIntFree(void* self);
int DacIntVs(void* self, void* that);
uint32_t DacIntHash(void* self);
char* DacIntPush(void* self);
char* DacIntPull(const char* flow, void* self);
extern DacType* DacIntType;

int* DacIntFromString(const char* str);

// DacAddress
void* DacAddressCopy(void* self);
void DacAddressFree(void* self);
int DacAddressVs(void* self, void* that);
uint32_t DacAddressHash(void* self);
char* DacAddressPush(void* self);
char* DacAddressPull(const char* flow, void* self);
extern DacType* DacAddressType;

void* DacAddressFromString(const char* str);

#endif
