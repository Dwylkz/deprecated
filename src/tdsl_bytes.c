#include <tdsl_bytes.h>

tdsl_bytes_t* tdsl_bnew()
{
  tdsl_bytes_t* bud = calloc(1, sizeof(tdsl_bytes_t));
  if (bud == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);
  return bud;
err_0:
  return NULL;
}

void tdsl_bfree(tdsl_bytes_t* self)
{
  free(self->data);
  free(self);
}

int tdsl_bappend(tdsl_bytes_t* self, const char* elem)
{
  int nelem = strlen(elem);
  if (self->size+nelem >= self->volume) {
    int volume = self->volume > 0? self->volume: 1;
    while (volume < self->size+nelem)
      volume <<= 1;
    char* data = realloc(self->data, (volume+2)*sizeof(char));
    if (data == NULL)
      TDSL_GOTO(err_0, TDSL_ESYS);

    self->data = data;
    self->volume = volume;
  }
  for (int i = 0; i < nelem; i++)
    self->data[self->size++] = elem[i];
  self->data[self->size] = '\0';
  return 0;
err_0:
  return -1;
}

void tdsl_bclear(tdsl_bytes_t* self)
{
  free(self->data);
  self->data = NULL;
  self->size = self->volume = 0;
}

char* tdsl_bprobe(tdsl_bytes_t* self, tdsl_probe_i probe)
{
  for (int i = 0; i < self->size; i++)
    if (probe(self->data+i) != 0)
      return self->data+i;
  return NULL;
}

int tdsl_bmap(tdsl_bytes_t* self, tdsl_map_i map)
{
  for (int i = 0; i < self->size; i++)
    if (map(self->data+i) == -1)
      TDSL_GOTO(err_0, TDSL_EMAP);
  return 0;
err_0:
  return -1;
}
