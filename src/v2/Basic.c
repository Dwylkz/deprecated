#include "Basic.h"

static const int kIntPushSize = 21;

// DacString
void* DacStringCopy(void* self)
{
  char* bud = strdup(self);
  DacCheck(bud == NULL, NULL);
  return bud;
}

void DacStringFree(void* self)
{
  free(self);
}

int DacStringVs(void* self, void* that)
{
  return strcmp(self, that);
}

uint32_t DacStringHash(void* self)
{
  char* old = self;
  uint32_t ret = 0;
  for ( ; *old; old++)
    ret = ret * 131 + *old;
  return ret;
}

char* DacStringPush(void* self)
{
  char* esc = DacRaw2Esc(self);
  DacCheck(esc == NULL, NULL);
  return DacFormat("\"%*s\"", esc);
}

static char* FirstQuote(const char* str)
{
  char* ret = (char*)str;
  while ((ret = strchr(ret, '\"')) != NULL) {
    int backslash_cnt = 0;
    for (char* i = ret-1; i >= str && *i == '\\'; i--)
      backslash_cnt++;
    if (backslash_cnt % 2 == 0) return ret;
    ret++;
  }
  return NULL;
}

char* DacStringPull(const char* flow, void* self)
{
  char* head = DacFirstGraph(flow);
  if (head == NULL || *head != '"')
    return DacErr(NULL, "missing open '\"'");
  char* tail;
  if (*(head + 1) == '\0' || (tail = FirstQuote(head + 1)) == NULL)
    return DacErr(NULL, "missing close '\"'");
  if (head + 1 >= tail)
    return DacErr(NULL, "empty escaped string.");
  char* bud = calloc(strlen(flow) + 2, sizeof(char));
  DacCheck(bud == NULL, NULL);
  strncpy(bud, head + 1 , tail - (head + 1));
  *(bud + (tail - (head + 1))) = '\0';
  bud = DacRealloc(bud, (strlen(bud) + 2) * sizeof(char));
  DacCheck(bud == NULL, NULL);
  bud = DacEsc2RawFree(bud);
  DacCheck(bud == NULL, NULL);
  *(char**)self = bud;
  return tail + 1;
}

static DacType __DacStringType = {
  DacStringCopy,
  DacStringFree,
  DacStringVs,
  DacStringHash,
  DacStringPush,
  DacStringPull
};
DacType* DacStringType = &__DacStringType;

// DacInt
void* DacIntCopy(void* self)
{
  int* bud = malloc(sizeof(int));
  DacCheck(bud == NULL, NULL);
  *bud = *(int*)self;
  return bud;
}

void DacIntFree(void* self)
{
  free(self);
}

int DacIntVs(void* self, void* that)
{
  int lhs = *(int*)self;
  int rhs = *(int*)that;
  if (lhs < rhs) return -1;
  if (lhs == rhs) return 0;
  return 1;
}

uint32_t DacIntHash(void* self)
{
  return *(uint32_t*)self;
}

char* DacIntPush(void* self)
{
  return DacFormat("d%d", *(int*)self);
}

char* DacIntPull(const char* flow, void* self)
{
  char* ret = DacFirstGraph(flow);
  if (ret == NULL || *ret != 'd')
    return DacErr(NULL, "missing predict 'd'");
  int* bud = malloc(sizeof(int));
  DacCheck(bud == NULL, NULL);
  DacCheckAndFree(sscanf(ret + 1, "%d", bud) != 1, bud, NULL);
  *(int**)self = bud;
  return ret + snprintf(NULL, 0, "d%d", *bud);
}

int* DacIntFromString(const char* str)
{
  int* bud = malloc(sizeof(int));
  DacCheck(bud == NULL, NULL);
  DacCheckAndFree(sscanf(str, "%d", bud) != 1, bud, NULL);
  return bud;
}

static DacType __DacIntType = {
  DacIntCopy,
  DacIntFree,
  DacIntVs,
  DacIntHash,
  DacIntPush,
  DacIntPull
};
DacType* DacIntType = &__DacIntType;

// DacAddress
void* DacAddressCopy(void* self)
{
  return self;
}

void DacAddressFree(void* self)
{
}

int DacAddressVs(void* self, void* that)
{
  if (self < that) return -1;
  if (self == that) return 0;
  return 1;
}

uint32_t DacAddressHash(void* self)
{
  return (uint32_t)self;
}

char* DacAddressPush(void* self)
{
  return DacFormat("p%p", self);
}

char* DacAddressPull(const char* flow, void* self)
{
  char* ret = DacFirstGraph(flow);
  if (ret == NULL || *ret != 'p')
    return DacErr(NULL, "missing predict 'p'");
  DacCheck(sscanf(ret + 1, "%p", (void**)self) != 1, NULL);
  return ret + snprintf(NULL, 0, "p%p", *(void**)self);
}

static DacType __DacAddressType = {
  DacAddressCopy,
  DacAddressFree,
  DacAddressVs,
  DacAddressHash,
  DacAddressPush,
  DacAddressPull
};
DacType* DacAddressType = &__DacAddressType;

void* DacAddressFromString(const char* str)
{
  void* bud;
  DacCheck(sscanf(str, "%p", &bud) != 1, NULL);
  return bud;
}
