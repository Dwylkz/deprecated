#include <tdsl_array.h>

tdsl_array_t* tdsl_anew()
{
  tdsl_array_t* bud = calloc(1, sizeof(tdsl_array_t));
  if (bud == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);
  return bud;
err_0:
  return NULL;
}

void tdsl_afree(tdsl_array_t* self)
{
  free(self->data);
  free(self);
}

int tdsl_aappend(tdsl_array_t* self, void* elem)
{
  if (self->size == self->volume) {
    int volume = self->volume > 0? self->volume*2: 1;
    void* data = realloc(self->data, volume*sizeof(void*));
    if (data == NULL)
      TDSL_GOTO(err_0, TDSL_ESYS);

    self->data = data;
    self->volume = volume;
  }
  self->data[self->size++] = elem;
  return 0;
err_0:
  return -1;
}

void tdsl_aclear(tdsl_array_t* self)
{
  free(self->data);
  self->data = NULL;
  self->size = self->volume = 0;
}

void** tdsl_aprobe(tdsl_array_t* self, tdsl_probe_i probe)
{
  for (int i = 0; i < self->size; i++)
    if (probe(self->data[i]) != 0)
      return self->data+i;
  return NULL;
}

int tdsl_amap(tdsl_array_t* self, tdsl_map_i map)
{
  for (int i = 0; i < self->size; i++)
    if (map(self->data[i]) == -1)
      TDSL_GOTO(err_0, TDSL_ESYS);
  return 0;
err_0:
  return -1;
}
