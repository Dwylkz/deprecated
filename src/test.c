#include <tdsl_comm.h>
#include <tdsl_utils.h>
#include <tdsl_array.h>
#include <tdsl_bytes.h>
#include <tdsl_list.h>
#include <tdsl_hash.h>
#include <tdsl_tree.h>

int nstr = 1e1;
int nstrs = 1e1;
char** strs;

int show_str(void* str)
{
  printf(" %s", (char*)str);
  return 0;
}

char* str_key;

int probe(void* str)
{
  return strcmp((char*)str, str_key) == 0;
}

void start()
{
  strs = calloc(nstrs, sizeof(char*));
  for (int i = 0; i < nstrs; i++)
    strs[i] = tdsl_random_str('a', 'z', nstr);
  str_key = strs[nstrs-1];
  // tdsl_map(strs, strs + nstrs, show_str);
  // puts("");
}

void end()
{
  tdsl_map(strs, strs + nstrs, tdsl_free);
  free(strs);
}

void ttree()
{
  tdsl_tree_t* t = tdsl_tnew(tdsl_str_compare);
  for (int i = 0; i < nstrs; i++)
    tdsl_tsearch(t, strs[i]);
  for (int i = 0; i < nstrs/2; i++)
    tdsl_tremove(t, strs[i]);
  tdsl_tclear(t);
  for (int i = 0; i < nstrs/2; i++)
    tdsl_tsearch(t, strs[i]);
  // for (int i = 0; i < nstrs/2; i++)
  //   printf("found=%p\n", tdsl_tfind(t, strs[i]));
  // for (int i = 0; i < t->size; i++)
  //   printf(" %s", (char*)tdsl_tselect(t, i));
  // puts("");
  // tdsl_tmap(t, show_str);
  // printf("\nsize=%d\n", t->size);
  tdsl_tfree(t);
}

void thash()
{
  tdsl_hash_t* h = tdsl_hnew(tdsl_str_hash, tdsl_str_compare);
  for (int i = 0; i < nstrs; i++)
    tdsl_hsearch(h, strs[i]);
  for (int i = 0; i < nstrs/2; i++)
    tdsl_hremove(h, strs[i]);
  for (int i = 0; i < nstrs/2; i++)
    if (tdsl_hfind(h, strs[i]))
      printf("shit!\n");
  tdsl_hclear(h);
  for (int i = nstrs/2; i < nstrs; i++)
    tdsl_hsearch(h, strs[i]);
  // tdsl_hmap(h, show_str);
  // puts("");
  tdsl_hfree(h);
}

void tlist()
{
  tdsl_list_t* l = tdsl_lnew();
  for (int i = 0; i < nstrs; i++)
    tdsl_lappend(l->to[0], strs[i]);
  tdsl_list_t* found = tdsl_lprobe(l, probe);
  printf("found: %s\n", (char*)found->data);
  tdsl_lremove(found);
  tdsl_lclear(l);
  tdsl_lmap(l, show_str);
  puts("");
  tdsl_lfree(l);
}

int tbmap(void* data)
{
  char* c = data;
  *c = toupper(*c);
  return 0;
}

int tbprobe(void* data)
{
  char* c = data;
  return isgraph(*c);
}

void tbytes()
{
  tdsl_bytes_t* b = tdsl_bnew();
  tdsl_bappend(b, "     head: ");
  tdsl_bclear(b);
  for (int i = 0; i < nstrs; i++)
    tdsl_bappend(b, strs[i]);
  tdsl_bmap(b, tbmap);
  // printf("%s\n", b->data);
  // printf("first graph: %c\n", *tdsl_bprobe(b, tbprobe));
  tdsl_bfree(b);
}

int taprobe(void* key)
{
  return strcmp(key, strs[nstrs/2]) == 0;
}

void tarray()
{
  tdsl_array_t* a = tdsl_anew();
  for (int i = 0; i < nstrs; i++)
    tdsl_aappend(a, strs[i]);
  // tdsl_amap(a, show_str);
  printf("\n%d\n", tdsl_aprobe(a, taprobe)-a->data);
  tdsl_afree(a);
}

void tutils()
{
  char* mem = tdsl_loadfile("test.c");
  tdsl_dumpfile(mem, "dump.c");
  free(mem);

  char* str = "\'\\x30";
  char* buf = tdsl_escs2raws(str);
  char* buf1 = tdsl_raws2escs(buf);
  puts(buf);
  puts(buf1);
  free(buf);
  free(buf1);
}

int main()
{
  start();
  tutils();
  // tarray();
  // tbytes();
  // tlist();
  // thash();
  // ttree();
  end();
  printf("%fs\n", tdsl_clock());
  return 0;
err_0:
  return -1;
}
