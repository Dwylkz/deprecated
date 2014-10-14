##Tiny data structure library
A tiny, thread safe data structure library.

### tdsl_comm.h
```c
#define TDSL_INFO(msg, ...)

#define TDSL_GOTO(tag, msg, ...)

#define TDSL_ESYS
#define TDSL_EMAP
#define TDSL_EREDUCE

typedef int (*tdsl_compare_i)(void*, void*);

typedef uint32_t (*tdsl_hash_i)(void*);

typedef int (*tdsl_map_i)(void*);

typedef int (*tdsl_probe_i)(void*);

typedef void* (*tdsl_binary_i)(void*, void*);
```

### tdsl_utils.h
```c
int tdsl_free(void* self);

int tdsl_random_int(int lower, int upper);

char* tdsl_random_str(int lower, int upper, int size);

int tdsl_map(void* lower, void* upper, tdsl_map_i map);

void* tdsl_recduce(void* lower, void* upper,
                   void* init, tdsl_binary_i binary);

int tdsl_int_compare(void* lhs, void* rhs);

uint32_t tdsl_int_hash(void* self);

int tdsl_str_compare(void* lhs, void*rhs);

uint32_t tdsl_str_hash(void* self);

char* tdsl_loadfile(const char* name);

int tdsl_dumpfile(const char* mem, const char* name);

double tdsl_clock(void);

char* tdsl_raws2escs(const char* str);

char* tdsl_escs2raws(const char* str);

```

### tdsl_array.h
```c
tdsl_array_t* tdsl_anew();

void tdsl_afree(tdsl_array_t* self);

int tdsl_aappend(tdsl_array_t* self, void* elem);

void tdsl_aclear(tdsl_array_t* self);

void** tdsl_aprobe(tdsl_array_t* self, tdsl_probe_i probe);

int tdsl_amap(tdsl_array_t* self, tdsl_map_i map);
```
### tdsl_bytes.h
```c
tdsl_bytes_t* tdsl_bnew();

void tdsl_bfree(tdsl_bytes_t* self);

int tdsl_bappend(tdsl_bytes_t* self, const char* elem);

void tdsl_bclear(tdsl_bytes_t* self);

char* tdsl_bprobe(tdsl_bytes_t* self, tdsl_probe_i probe);

int tdsl_bmap(tdsl_bytes_t* self, tdsl_map_i map);
```

### tdsl_list.h
```c
tdsl_list_t* tdsl_lnew();

void tdsl_lfree(tdsl_list_t* self);

int tdsl_lappend(tdsl_list_t* self, void* elem);

void tdsl_lremove(tdsl_list_t* self);

void tdsl_lclear(tdsl_list_t* self);

tdsl_list_t* tdsl_lprobe(tdsl_list_t* self, tdsl_probe_i probe);

int tdsl_lmap(tdsl_list_t* self, tdsl_map_i map);
```

### tdsl_hash.h
```c
tdsl_hash_t* tdsl_hnew(tdsl_hash_i hash, tdsl_compare_i compare);

void tdsl_hfree(tdsl_hash_t* self);

void* tdsl_hsearch(tdsl_hash_t* self, void* elem);

void* tdsl_hfind(tdsl_hash_t* self, void* elem);

void tdsl_hremove(tdsl_hash_t* self, void* elem);

void tdsl_hclear(tdsl_hash_t* self);

int tdsl_hmap(tdsl_hash_t* self, tdsl_map_i map);
```

### tdsl_tree.h
```c
tdsl_tree_t* tdsl_tnew(tdsl_compare_i compare);

void tdsl_tfree(tdsl_tree_t* self);

void tdsl_tclear(tdsl_tree_t* self);

void* tdsl_tsearch(tdsl_tree_t* self, void* key);

void* tdsl_tfind(tdsl_tree_t* self, void* key);

void* tdsl_tselect(tdsl_tree_t* self, int rank);

void tdsl_tremove(tdsl_tree_t* self, void* key);

int tdsl_tmap(tdsl_tree_t* self, tdsl_map_i map);
```
