#include <tdsl_list.h>

tdsl_list_t* tdsl_lnew()
{
  tdsl_list_t* bud = calloc(1, sizeof(tdsl_list_t));
  if (bud == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  bud->to[0] = bud->to[1] = bud;
  return bud;
err_0:
  return NULL;
}

void tdsl_lfree(tdsl_list_t* self)
{
  tdsl_lclear(self);
  free(self);
}

int tdsl_lappend(tdsl_list_t* self, void* elem)
{
  tdsl_list_t* bud = tdsl_lnew();
  if (bud == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  bud->data = elem;
  bud->to[0] = self;
  bud->to[1] = self->to[1];
  self->to[1]->to[0] = bud;
  self->to[1] = bud;
  return 0;
err_0:
  return -1;
}

void tdsl_lremove(tdsl_list_t* self)
{
  self->to[0]->to[1] = self->to[1];
  self->to[1]->to[0] = self->to[0];
  free(self);
}

void tdsl_lclear(tdsl_list_t* self)
{
  while (self->to[1] != self)
    tdsl_lremove(self->to[1]);
}

tdsl_list_t* tdsl_lprobe(tdsl_list_t* self, tdsl_probe_i probe)
{
  for (tdsl_list_t* p = self->to[1]; p != self; p = p->to[1])
    if (probe(p->data) != 0)
      return p;
  return NULL;
}

int tdsl_lmap(tdsl_list_t* self, tdsl_map_i map)
{
  for (tdsl_list_t* p = self->to[1]; p != self; p = p->to[1])
    if (map(p->data) == -1)
      TDSL_GOTO(err_0, TDSL_EMAP);
  return 0;
err_0:
  return 1;
}
