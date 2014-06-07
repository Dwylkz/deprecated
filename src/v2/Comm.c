#include <Comm.h>
#include <Basic.h>
#include <Bytes.h>
#include <MArray.h>

// Memory Utils
void* DacRealloc(void* old, int size)
{
  void* bud = realloc(old, size);
  DacCheckAndFree(bud == NULL, old, NULL);
  return bud;
}

void DacRangeFree(void* lower, void* upper, DacFree dac_free)
{
  void** start = lower;
  void** end = upper;
  while (start < end)
    dac_free(*start++);
  free(lower);
}

static int RangePushAux(DacBytes* bytes, void* data, DacPush dac_push)
{
  char* ret = dac_push(data);
  DacCheck(ret == NULL, NULL);
  DacCheckAndFree(DacBytesEatString(bytes, ret) != 0, ret, -1);
  return 0;
}

char* DacRangePush(void* lower, void* upper,
                   const char ogc[3],
                   DacPush dac_push)
{
  char buf[3] = {ogc[0]};
  DacBytes* ret = DacBytesNew(buf);
  DacCheck(ret == NULL, NULL);
  void** start = lower;
  void** end = upper;
  int size = end - start;
  int flag = 0;
  buf[0] = ogc[1];
  for (int i = 0; i < size; i++) {
    if (start[i] == NULL)
      continue;
    if (i > 0)
      if (DacBytesCatString(ret, buf) != 0) {
        flag++;
        break;
      }
    if (RangePushAux(ret, start[i], dac_push) != 0) {
      flag++;
      break;
    }
  }
  buf[0] = ogc[2];
  if (DacBytesCatString(ret, buf) != 0 || flag != 0) {
    DacBytesFree(ret);
    ret = NULL;
  }
  char* str = DacBytesGet(ret);
  DacBytesHalfFree(ret);
  return str;
}

static char* RangePullAux(const char* flow, DacMArray* bud)
{
  char* i;
  DacWrapper* w;
  if ((i = DacWrapperPull(flow, &w)) == NULL)
    return DacErr(NULL, "parse wrapper falied");
  if (DacMArrayPushBack(bud, w, 1) != 0)
    i = DacErr(NULL, "construct MArray failed");
  DacWrapperFree(w);
  return i;
}

char* DacRangePull(const char* flow,
                   const char ogc[3],
                   DacMArray** self)
{
  char *i = DacFirstGraph(flow);
  if (i == NULL)
    DacGoto(err_0, DAC_ERR_MISSIG_LOOKAHEAD);

  if (*i != ogc[0])
    DacGoto(err_0, DAC_ERR_MISSIG_OPEN, ogc[0]);

  DacMArray* bud = DacMArrayNew();
  if (bud == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  if ((i = DacFirstGraph(i + 1)) == NULL)
    DacGoto(err_1, DAC_ERR_MISSIG_LOOKAHEAD);

  for (;;) {
    if (*i == ogc[2])
      break;

    if ((i = RangePullAux(i, bud)) == NULL)
      DacGoto(err_1, DAC_ERR_PULL);

    if ((i = DacFirstGraph(i)) == NULL)
      DacGoto(err_1, DAC_ERR_MISSIG_LOOKAHEAD);

    if (*i == ogc[1]) {
      i++;
      continue;
    }

    if (*i != ogc[2])
      DacGoto(err_1, DAC_ERR_MISSIG_CLOSE, ogc[2]);
  }

  *self = bud;
  return i + 1;
err_1:
  DacMArrayFree(bud);
err_0:
  return NULL;
}

// Random Utils
int DacRandomInt(int lower, int upper)
{
  static int random_init = 0;
  static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&mutex);
  if (random_init == 0) {
    srand((uint32_t)time(0));
    random_init = 1;
  } 
  pthread_mutex_unlock(&mutex);
  uint32_t ret = rand() % (upper - lower) + lower;
  return ret;
}

int* DacRandomInts(int lower, int upper, int size)
{
  int* bud = calloc(size, sizeof(int));
  DacCheck(bud == NULL, NULL);
  for (int i = 0; i < size; i++)
    bud[i] = DacRandomInt(lower, upper);
  return bud;
}

char* DacRandomString(int lower, int upper, int length)
{
  char* bud = calloc(length + 2, sizeof(char));
  DacCheck(bud == NULL, NULL);
  for (int i = 0; i < length; i++)
    bud[i] = DacRandomInt(lower, upper);
  return bud;
}

char** DacRandomStrings(int lower, int upper, int length, int size)
{
  char** bud = calloc(size, sizeof(char*));
  DacCheck(bud == NULL, NULL);
  for (int i = 0; i < size; i++) {
    bud[i] = DacRandomString(lower, upper, length);
    if (bud[i] == NULL) {
      for (int j = 0; j < i; j++)
        free(bud[j]);
      return NULL;
    }
  }
  return bud;
}

// String Utils
char* DacReplace(const char* str,
                 const char* pat,
                 const char* sub,
                 const int do_all)
{
  int pat_len = strlen(pat);
  int sub_len = strlen(sub);
  int size = strlen(str);
  if (pat_len < sub_len)
    size *= (sub_len + pat_len - 1) / pat_len;
  char* ret = calloc(size + 2, sizeof(char));
  DacCheck(ret == NULL, NULL);
  char* pre = (char*)str;
  for (char* i = pre; (i = strstr(i, pat)) != NULL; ) {
    strncat(ret, pre, i - pre);
    strcat(ret, sub);
    i += strlen(pat);
    pre = i;
    if (do_all == 0) break;
  }
  strcat(ret, pre);
  return DacRealloc(ret, (size + 2) * sizeof(char));
}

char* DacReplaceFree(char* str,
                     const char* pat,
                     const char* sub,
                     const int do_all)
{
  char* ret = DacReplace(str, pat, sub, do_all);
  free(str);
  return ret;
}

char* DacVFormat(const char* format, va_list ap)
{
  char* str = DacReplace(format, "%*", "%", 1);
  DacCheck(str == NULL, NULL);
  int size = vsnprintf(NULL, 0, str, ap);
  char* ret = calloc(size + 2, sizeof(char));
  DacCheckAndFree(ret == NULL, str, NULL);
  if (vsprintf(ret, str, ap) != size) {
    free(ret);
    ret = NULL;
  }
  free(str);
  return ret;
}

char* DacFormat(const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  char* ret = DacVFormat(format, ap);
  if (ret != NULL )
    for (char* i = (char*)format; (i = strchr(i, '%')) != NULL; i++) {
      void* arg = va_arg(ap, void*);
      char pred = *(i + 1);
      if (pred != '\0' && pred == '*')
        free(arg);
    }
  va_end(ap);
  return ret;
}

static char* escs = "\"\\abefnrtv";
static char* raws = "\"\\\a\b\e\f\n\r\t\v";
static int total_char = sizeof(escs) / sizeof(char);

char* DacEsc2Raw(const char* esc)
{
  int size = strlen(esc);
  char* ret = strdup(esc);
  DacCheck(ret == NULL, NULL);
  char* i = ret;
  int flag = 0;
  for (int j = 0; j < size; j++)
    if (esc[j] == '\\') {
      if (esc[++j] == '\0') {
        DacWarn(0, "missing escape character.");
        flag++;
        break;
      }
      char* k = strchr(escs, esc[j]);
      if (k == NULL) {
        DacWarn(0, "unknown escape character %c.", esc[j]);
        flag++;
        break;
      }
      *i++ = raws[k-escs];
    }
    else {
      *i++ = esc[j];
    }
  DacCheckAndFree(flag != 0, ret, NULL);
  *i++ = '\0';
  return DacRealloc(ret, (i - ret + 1) * sizeof(char));
}

char* DacEsc2RawFree(char* esc)
{
  char* ret = DacEsc2Raw(esc);
  free(esc);
  return ret;
}

char* DacRaw2Esc(const char* raw)
{
  int size = strlen(raw);
  char* ret = calloc(size * 2 + 2, sizeof(char));
  DacCheck(ret == NULL, NULL);
  char* i = ret;
  for (int j = 0; j < size; j++) {
    char* k = strchr(raws, raw[j]);
    if (k != NULL) {
      *i++ = '\\';
      *i++ = escs[k - raws];
    }
    else {
      *i++ = raw[j];
    }
  }
  *i++ = '\0';
  return DacRealloc(ret, (i - ret + 1) * sizeof(char));
}

char* DacRaw2EscFree(char* raw)
{
  char* ret = DacEsc2Raw(raw);
  free(raw);
  return ret;
}

char* DacFirstGraph(const char* str)
{
  for (char* i = (char*)str; *i != '\0'; i++)
    if (isgraph(*i) != 0)
      return i;
  return NULL;
}

void DacPutsAndFree(char* str)
{
  if (str == NULL) {
    DacErr(-1, "empty string");
    return ;
  }
  puts(str);
  free(str);
}
