#include <tdsl_utils.h>

int tdsl_free(void* self)
{
  free(self);
  return 0;
}

int tdsl_random_int(int lower, int upper)
{
  static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
  static int is_init = 1;
  pthread_mutex_lock(&lock);
  if (is_init == 1) {
    is_init = 0;
    srand((unsigned)time(0));
  }
  int ret = rand()%(upper-lower)+lower;
  pthread_mutex_unlock(&lock);
  return ret;
}

char* tdsl_random_str(int lower, int upper, int size)
{
  char* ret = calloc(size + 2, sizeof(char));
  if (ret == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  for (int i = 0; i < size; i++)
    ret[i] = tdsl_random_int(lower, upper);
  return ret;
err_0:
  return NULL;
}

int tdsl_map(void* lower, void* upper, tdsl_map_i map)
{
  void** start = lower;
  void** end = upper;
  while (start < end)
    if (map(*start++) == -1)
      TDSL_GOTO(err_0, TDSL_EMAP);
  return 0;
err_0:
  return -1;
}

void* tdsl_recduce(void* lower, void* upper,
                   void* init, tdsl_binary_i binary)
{
  void** start = lower;
  void** end = upper;
  while (start < end)
    init = binary(init, *start++);
  return init;
}

int tdsl_int_compare(void* lhs, void* rhs)
{
  int lval = *(int*)lhs;
  int rval = *(int*)rhs;
  if (lhs == rhs) return 0;
  return lhs < rhs? -1: 1;
}

uint32_t tdsl_int_hash(void* self)
{
  return *(uint32_t*)self;
}

int tdsl_str_compare(void* lhs, void*rhs)
{
  return strcmp((char*)lhs, (char*)rhs);
}

uint32_t tdsl_str_hash(void* self)
{
  uint32_t code = 0;
  for (char* i = self; *i != '\0'; i++)
    code = code*3+*i;
  return code;
}

char* tdsl_loadfile(const char* name)
{
  FILE* file = fopen(name, "r");
  if (file == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  if (fseek(file, 0, SEEK_END) == -1)
    TDSL_GOTO(err_1, TDSL_ESYS);

  int size = ftell(file);
  if (size == -1)
    TDSL_GOTO(err_1, TDSL_ESYS);

  rewind(file);
  char* mem= calloc(1, (size+2)*sizeof(char));
  if (mem == NULL)
    TDSL_GOTO(err_1, TDSL_ESYS);

  if (fread(mem, sizeof(char), size, file) != size)
    TDSL_GOTO(err_2, TDSL_ESYS);

  fclose(file);
  return mem;
err_2:
  free(mem);
err_1:
  fclose(file);
err_0:
  return NULL;
}

int tdsl_dumpfile(const char* mem, const char* name)
{
  FILE* file = fopen(name, "w");
  if (file == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  int size = strlen(mem);
  if (fwrite(mem, sizeof(char), size, file) != size)
    TDSL_GOTO(err_1, TDSL_ESYS);

  fclose(file);
  return 0;
err_1:
  fclose(file);
err_0:
  return -1;
}

double tdsl_clock(void)
{
  return 1.0*clock()/CLOCKS_PER_SEC;
}

static char raws[] = "\'\"\\\a\b\f\n\r\t\v";
static char escs[] = "\'\"\\abfnrtv";

char* tdsl_raws2escs(const char* str)
{
  char* buf;
  size_t size;
  FILE* file = open_memstream(&buf, &size);
  if (file == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  for (char* i = (char*)str; *i != '\0'; i++) {
    char* found = strchr(raws, *i);
    if (found == NULL) {
      if (fprintf(file, "%c", *i) < 0)
        TDSL_GOTO(err_1, TDSL_ESYS);
      continue;
    }

    if (fprintf(file, "\\%c", escs[found-raws]) < 0)
      TDSL_GOTO(err_1, TDSL_ESYS);
  }

  fclose(file);
  return buf;
err_1:
  fclose(file);
  free(buf);
err_0:
  return NULL;
}

char* tdsl_escs2raws(const char* str)
{
  char* buf;
  size_t size;
  FILE* file = open_memstream(&buf, &size);
  if (file == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  for (char* i = (char*)str; *i != '\0'; i++)
    if (*i == '\\') {
      if (*++i == '\0')
        TDSL_GOTO(err_1, "missing escape charactor");

      char* found = strchr(escs, *i);
      if (found == NULL && *i != 'x')
        TDSL_GOTO(err_1, "unknown escape charactor %c", *i);

      if (found != NULL) {
        if (fprintf(file, "%c", raws[found-escs]) < 0)
          TDSL_GOTO(err_1, TDSL_ESYS);
        continue;
      }

      if (*++i == '\0' || *++i == '\0')
        TDSL_GOTO(err_1, "hex form error, expected '\\xHH'");

      char h = (*(i-1)-'0')*16+*i-'0';
      if (fprintf(file, "%c", h) < 0)
        TDSL_GOTO(err_1, TDSL_ESYS);
    }
    else if (fprintf(file, "%c", *i) < 0)
      TDSL_GOTO(err_1, TDSL_ESYS);

  fclose(file);
  return buf;
err_1:
  fclose(file);
  free(buf);
err_0:
  return NULL;
  return NULL;
}
