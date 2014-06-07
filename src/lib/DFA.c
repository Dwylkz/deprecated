#include "DFA.h"

#define DFA_MAGIC 0xdfa00dfa
#define SIGMA_SHIFT 128

static int SigmaEC(int x)
{
  return x + SIGMA_SHIFT;
}

static int SigmaDC(int x)
{
  return x - SIGMA_SHIFT;
}

static int InSigma(int x)
{
  return 0 <= x && x < SIGMA_SIZE;
}

static char* Escape(int x)
{
  static char buf[10];
  buf[0] = '\\';
  buf[1] = '\0';
  buf[2] = '\0';
  if (!isspace(x)) {
    buf[0] = x;
    buf[1] = '\0';
  }
  else if (x == '\n') buf[1] = 'n';
  else if (x == '\t') buf[1] = 't';
  else if (x == ' ') buf[1] = ' ';
  else buf[1] = '?';
  return buf;
}

DFA *DFANew(Map* i_table, Tree *i_tree)
{
  int idx,
      zero = 0,
      sigma[SIGMA_SIZE],
      i;
  // Construct sigma
  memset(sigma, -1, sizeof(sigma));
  for (i = idx = 0; i < ArraySize(i_tree->map_); i++) {
    int c = SigmaEC(*(int*)ArrayGet(i_tree->map_, i));
    if (InSigma(c) && sigma[c] == -1) {
      sigma[c] = idx++;
    }
  }

  // Construct S, T, F
  Map *S = MapNew(BitSetT, IntT);
  Array *T = ArrayNew(IntT),
        *F = ArrayNew(IntT);
  List *Q = ListNew(BitSetT);

  idx = 0;
  ListPush(Q, i_tree->firstpos_, LIST_HEAD);
  MapPush(S, i_tree->firstpos_, &idx);
  idx++;
  Map *tmp_map = MapNew(IntT, IntT);
  ArrayPush(T, &tmp_map);
  ArrayPush(F, &zero);
  for ( ; ListSize(Q); ListPop(Q, LIST_TAIL)) {
    BitSet *u = ListGet(Q, LIST_TAIL);
    int ac_meta = NOTAC, u_id = *(int*)MapGet(S, u);
    tmp_map = *(void**)ArrayGet(T, u_id);
    for (i = 0; i < BitSetSize(u); i++) {
      if (BitSetGet(u, i)) {
        int c = *(int*)ArrayGet(i_tree->map_, i);
        // check if c is kChar
        if (InSigma(SigmaEC(c))) {
          c = sigma[SigmaEC(c)];
          BitSet *tmp_bitset;
          // check if c is a new kChar for state u
          if (!MapGet(tmp_map, &c)) {
            tmp_bitset = BitSetNew();
            MapPush(tmp_map, &c, &tmp_bitset);
          } else {
            tmp_bitset = *(void**)MapGet(tmp_map, &c);
          }
          BitSetUnion(tmp_bitset, *(void**)ArrayGet(i_tree->followpos_, i));
        } else {
          ac_meta = Min(ac_meta, MetaDC(c));
        } // if (InSigma(SigmaEC(c))) 
      } // if (BitSetGet(u, i)) 
    } // for (i = 0; i < BitSetSize(u); i++)
    *(int*)ArrayGet(F, u_id) = ac_meta;
#if 0
    printf("set %d has %d trans:\n", u_id, MapSize(tmp_map));
#endif
    for (i = 0; i < MapSize(tmp_map); i++) {
#if 0
      printf("(%d, %d)\n", *(int*)MapPick(tmp_map, i + 1, MAP_KEY),
          *(int*)MapPick(tmp_map, i + 1, MAP_DATA));
#endif
      void **pick = MapPick(tmp_map, i + 1, MAP_DATA);
#if 0
      printf("in  pick = %p, %d\n", pick, *pick);
#endif
      BitSet *tmp_bitset = (BitSet*)*pick;
      // check if tmp_bitset is a new state
      if (!MapGet(S, tmp_bitset)) {
#if 0
        int j;
        printf("new = {");
        for (j = 0; j < BitSetSize(tmp_bitset); j++) {
          if (BitSetGet(tmp_bitset, j)) {
            printf(" %3d", j);
          }
        }
        puts("}");
#endif
        // yes, append it into S
        MapPush(S, tmp_bitset, &idx);
#if 0
        printf("idx = %d\n", idx);
#endif
        idx++;
        Map* new_map = MapNew(IntT, IntT);
        ArrayPush(T, &new_map);
        ArrayPush(F, &zero);
        // push into queue for computing its Trans
        ListPush(Q, tmp_bitset, LIST_HEAD);
      } // if (!MapGet(S, tmp_bitset)) 
      // Correspond to T[u][kChar] = ID(tmp_bitset)
      *(int*)pick = *(int*)MapGet(S, tmp_bitset);
#if 0
      printf("out pick = %p, %d\n", pick, *pick);
#endif
      BitSetRemove(tmp_bitset);
    }
  } // for ( ; ListSize(Q); ) 
  ListRemove(Q);

#if 0
#if 0
//   TreeShow(i_tree);
  puts("sigma:");
  for (i = 0; i < SIGMA_SIZE; i++) {
    if (sigma[i] != -1) {
      printf("%4c--->%4d\n", SigmaDC(i), sigma[i]);
    }
  }
#endif
#if 0
  printf("S = %4d\n", MapSize(S));
  for (i = 0; i < MapSize(S); i++) {
    BitSet *tmp_bitset = MapPick(S, i + 1, MAP_KEY);
    int j, *id = MapPick(S, i + 1, MAP_DATA), indent = 0;
    printf("%4d = {", *id);
    for (j = 0; j < BitSetSize(tmp_bitset); j++) {
      if (BitSetGet(tmp_bitset, j)) {
        if (indent && indent % 10 == 0) {
          printf("\n%8s", " ");
        }
        indent++;
        printf(" %3d", j);
      }
    }
    puts("}");
  }
#endif
#if 1
  printf("T size = %d\n", ArraySize(T));
  for (i = 0; i < ArraySize(T); i++) {
    tmp_map = *(void**)ArrayGet(T, i);
    int j;
    printf("%4d-->", i);
    for (j = 0; j < MapSize(tmp_map); j++) {
      int *tmp_char = MapPick(tmp_map, j + 1, MAP_KEY),
          *tmp_to = MapPick(tmp_map, j + 1, MAP_DATA);
      if (j && j % 10 == 0) {
        printf("\n%7s", " ");
      }
      printf("(%d, %d)%s", *tmp_char, *tmp_to, j == MapSize(tmp_map)? "\n": ", ");
    }
    puts("");
  }
#endif
#if 1
  printf("F size = %4d\n", ArraySize(F));
  for (i = 0; i < ArraySize(F); i++) {
    printf("%4d = %4d\n", i, *(int*)ArrayGet(F, i));
  }
#endif
#endif

  // Compress T
  int not_occupy = -1;
  Array *_T[T_COL] = { 
    ArrayNew(IntT),
    ArrayNew(IntT),
    ArrayNew(IntT)
  };
  for (i = 0; i < MapSize(S); i++) {
    int j,
        id = *(int*)MapPick(S, i + 1, MAP_DATA),
        t_trans[SIGMA_SIZE];
    memset(t_trans, -1, sizeof(t_trans));
    Map *T_id = *(void**)ArrayGet(T, id);
    // T[i] -> t_trans for reducing time using
    for (j = 0; j  < MapSize(T_id); j++) {
      t_trans[*(int*)MapPick(T_id, j + 1, MAP_KEY)] = *(int*)MapPick(T_id, j + 1, MAP_DATA);
    }
#if 0
    printf("%4d-->", i);
    for (j = 0; j < SIGMA_SIZE; j++) {
      if (t_trans[j] != -1) {
        printf("(%d, %d)%s", j, t_trans[j], j == MapSize(T_id)? "\n": ", ");
      }
    }
    puts("");
#endif
    // Compressing
    int base;
    for (base = 0; ; base++) {
      int flag = 1;
      for (j = 0; j < SIGMA_SIZE; j++) {
        if (t_trans[j] != -1) {
          // Enlarge T_NEXT & T_CHECK
          if (base + j >= ArraySize(_T[T_NEXT])) {
            for ( ; ArraySize(_T[T_NEXT]) <= base + j + 1; ) {
              ArrayPush(_T[T_NEXT], &not_occupy);
              ArrayPush(_T[T_CHECK], &not_occupy);
            }
          }
          if (*(int*)ArrayGet(_T[T_CHECK], base + j) != not_occupy) {
            flag = 0;
            break;
          }
        }
      }
      if (flag) {
        for (j = 0; j < SIGMA_SIZE; j++) {
          if (t_trans[j] != -1) {
            *(int*)ArrayGet(_T[T_NEXT], base + j) = t_trans[j];
            *(int*)ArrayGet(_T[T_CHECK], base + j) = id;
          }
        }
        for ( ; ArraySize(_T[T_BASE]) <= id; ) {
          ArrayPush(_T[T_BASE], &not_occupy);
        }
        ArraySet(_T[T_BASE], id, &base);
        break;
      }
    }
  }

  DFA *new = calloc(1, sizeof(DFA));
  new->meta_to_id_ = i_table;
  new->id_to_meta_ = ArrayNew(IntT);
  for ( ; ArraySize(new->id_to_meta_) < MapSize(i_table); ) {
    ArrayPush(new->id_to_meta_, &zero);
  }
  for (i = 0; i < MapSize(i_table); i++) {
    int *id = MapPick(i_table, i + 1, MAP_DATA);
    char *meta = MapPick(i_table, i + 1, MAP_KEY);
#if 0
    printf("set %d->%s\n", *id, meta);
#endif
    ArraySet(new->id_to_meta_, *id, &meta);
  }
  memcpy(new->sigma_, sigma, sizeof(sigma));
  new->S_ = MapSize(S);
  new->s0_ = 0;
  memcpy(new->T_, _T, sizeof(Array*) * T_COL);
  new->F_ = F;

  for (i = 0; i < ArraySize(T); i++) {
    MapRemove(*(void**)ArrayGet(T, i));
  }
  ArrayRemove(T);
  MapRemove(S);

  return new;
}

void* DFARemove(void *_this)
{
  DFA *self = _this;
  ArrayRemove(self->F_);
  int i;
  for (i = 0; i < T_COL; i++) {
    ArrayRemove(self->T_[i]);
  }
  ArrayRemove(self->id_to_meta_);
  MapRemove(self->meta_to_id_);
  free(self);
  return self;
}

void DFAToFile(DFA *self, FILE *o_fp)
{
  // put magic
  int magic = DFA_MAGIC;
  fwrite(&magic, sizeof(int), 1, o_fp);

  // put meta_to_id
  int i,
          map_size = MapSize(self->meta_to_id_);
  fwrite(&map_size, sizeof(int), 1, o_fp);
  for (i = 0; i < map_size; i++) {
    char *meta = MapPick(self->meta_to_id_, i + 1, MAP_KEY);
    int meta_len = strlen(meta),
            *id = MapPick(self->meta_to_id_, i + 1, MAP_DATA);
    fwrite(&meta_len, sizeof(int), 1, o_fp);
    fwrite(meta, sizeof(char), meta_len, o_fp);
    fwrite(id, sizeof(int), 1, o_fp);
  }

  // put sigma
  fwrite(self->sigma_, SIGMA_SIZE, sizeof(int), o_fp);

  // put S, s0
  fwrite(&self->S_, sizeof(int), 1, o_fp);
  fwrite(&self->s0_, sizeof(int), 1, o_fp);

  // put T_
  for (i = 0; i < T_COL; i++) {
    int len = ArraySize(self->T_[i]),
            j;
    fwrite(&len, sizeof(int), 1, o_fp);
    for (j = 0; j < len; j++) {
      fwrite(ArrayGet(self->T_[i], j), sizeof(int), 1, o_fp);
    }
  }

  // put F_
  int len = ArraySize(self->F_);
  fwrite(&len, sizeof(int), 1, o_fp);
  for (i = 0; i < len; i++) {
    fwrite(ArrayGet(self->F_, i), sizeof(int), 1, o_fp);
  }
}

DFA *DFAFromFile(FILE *i_fp)
{
  // check magic
  int magic;
  fread(&magic, sizeof(int), 1, i_fp);
  if (magic != DFA_MAGIC) {
    perror("invalid magic");
    exit(-1);
  }
  DFA *new = calloc(1, sizeof(DFA));

  // get meta_to_id and id_to_meta
  new->meta_to_id_ = MapNew(StringT, IntT);
  new->id_to_meta_ = ArrayNew(IntT);
  int i, map_size, zero = 0;
  fread(&map_size, sizeof(int), 1, i_fp);
  for (i = 0; i < map_size; i++) {
    ArrayPush(new->id_to_meta_, &zero);
  }
  for (i = 0; i < map_size; i++) {
    char *meta;
    int meta_len, id;
    fread(&meta_len, sizeof(int), 1, i_fp);
    meta = calloc(meta_len + 1, sizeof(char));
    fread(meta, sizeof(char), meta_len, i_fp);
    fread(&id, sizeof(int), 1, i_fp);
    MapPush(new->meta_to_id_, meta, &id);
    free(meta);
    meta = MapPick(new->meta_to_id_, i + 1, MAP_KEY);
#if 0
    printf("ArraySize = %d\n", ArraySize(new->id_to_meta_));
    printf("\tget (%20s, %4d)\n", meta, id);
#endif
    ArraySet(new->id_to_meta_, id, &meta);
  }

  // get sigma
  fread(new->sigma_, SIGMA_SIZE, sizeof(int), i_fp);

  // get S, s0
  fread(&new->S_, sizeof(int), 1, i_fp);
  fread(&new->s0_, sizeof(int), 1, i_fp);

  // get T_
  for (i = 0; i < T_COL; i++) {
    new->T_[i] = ArrayNew(IntT);
    int len, j;
    fread(&len, sizeof(int), 1, i_fp);
    for (j = 0; j < len; j++) {
      int data;
      fread(&data, sizeof(int), 1, i_fp);
      ArrayPush(new->T_[i], &data);
    }
  }

  // get F_
  new->F_ = ArrayNew(IntT);
  int len = ArraySize(new->F_);
  fread(&len, sizeof(int), 1, i_fp);
  for (i = 0; i < len; i++) {
    int data;
    fread(&data, sizeof(int), 1, i_fp);
    ArrayPush(new->F_, &data);
  }

  return new;
}

void DFAInit(DFA *self)
{
  self->current_s_ = self->s0_;
  self->current_len_ = 0;
  self->last_ac_ = NOTAC;
  self->last_ac_len_ = 0;
}

int DFAMove(DFA *self, int i_char)
{
  int base = *(int*)ArrayGet(self->T_[T_BASE], self->current_s_);
  if (InSigma(SigmaEC(i_char)) && self->sigma_[SigmaEC(i_char)] != -1) {
    int id = base + self->sigma_[SigmaEC(i_char)];
    if (id < ArraySize(self->T_[T_CHECK])
          && *(int*)ArrayGet(self->T_[T_CHECK], id) == self->current_s_) {
      self->current_s_ = *(int*)ArrayGet(self->T_[T_NEXT], id);
      self->current_len_++;
      if (*(int*)ArrayGet(self->F_, self->current_s_) != NOTAC) {
        self->last_ac_ = *(int*)ArrayGet(self->F_, self->current_s_);
        self->last_ac_len_ = self->current_len_;
      }
      return 1;
    } else {
      return 0;
    }
  }
  return -1;
}

int DFAGetCurrentS(DFA *self)
{
  return self->current_s_;
}

int DFAGetCurrentLen(DFA *self)
{
  return self->current_len_;
}

int DFAGetLastAc(DFA *self)
{
  return self->last_ac_;
}

int DFAGetLastAcLen(DFA *self)
{
  return self->last_ac_len_;
}

char* DFAGetMetaName(DFA *self, int i_id)
{
  return *(void**)ArrayGet(self->id_to_meta_, i_id);
}

int DFAGetMetaID(DFA *self, char *i_meta)
{
  return *(int*)MapGet(self->meta_to_id_, i_meta);
}

void DFAShow(DFA *self)
{
  puts("---------------------------DFA---------------------------");
  int i;
  puts("sigma map:");
  for (i = 0; i < SIGMA_SIZE; i++) {
    if (self->sigma_[i] != -1) {
      printf("%4s->%4d\n", Escape(SigmaDC(i)), self->sigma_[i]);
    }
  }
  puts("");
  printf("has %d states\n", self->S_);
  printf("%d as initial states\n", self->s0_);
  puts("DFA transimition table:\n");
  printf("%8s%8s%8s%8s\n", "ROW", "BASE", "NEXT", "CHECK");
  for (i = 0; i < ArraySize(self->T_[T_NEXT]); i++) {
    printf("%8d", i);
    if (i < ArraySize(self->T_[T_BASE])) {
      printf("%8d", *(int*)ArrayGet(self->T_[T_BASE], i));
    } else {
      printf("%8s", "");
    }
    printf("%8d%8d\n", *(int*)ArrayGet(self->T_[T_NEXT], i), *(int*)ArrayGet(self->T_[T_CHECK], i));
  }
  printf("ID and Meta\n");
  printf("%8s %30s\n", "ID", "META");
  Array* id_to_meta = self->id_to_meta_;
  for (i = 0; i < ArraySize(id_to_meta); i++) {
    printf("%8d %30s\n", i, *(char**)ArrayGet(id_to_meta, i));
  }
}

void DFAExportBijection(DFA* self, FILE *o_fp)
{
#define __file_head "#ifndef DLEX2_HEADER_\n" \
  "#define DLEX2_HEADER_\n\n" \
  "// This file is generate by Dlex2\n"
#define __mti_head "enum token_id { // Meta to id\n"
#define __mti_tail "};\n"
#define __itm "#define token_name(n) token_name_##n\n"
#define __file_end "\n#endif // DLEX2_HEADER_"
  int i;
  Array *x = self->id_to_meta_;
  fputs(__file_head, o_fp);
  fputs(__mti_head, o_fp);
  for (i = 0; i < ArraySize(x); i++) {
    fprintf(o_fp, "  %s%c\n", DFAGetMetaName(self, i), i < ArraySize(x) - 1? ',': ' ');
  }
  fputs(__mti_tail, o_fp);

  fputs(__itm, o_fp);
  for (i = 0; i < ArraySize(x); i++) {
    fprintf(o_fp, "#define token_name_%d \"%s\"\n", i, DFAGetMetaName(self, i));
  }
  fputs(__file_end, o_fp);
#undef __file_head
#undef __mti_head
#undef __mti_tail
#undef __itm_head
#undef __itm_tail
#undef __file_end
}

void DFAPushMeta(DFA *self, char *i_meta)
{
  int id = ArraySize(self->id_to_meta_);
  MapPush(self->meta_to_id_, i_meta, &id);
  id = MapRank(self->meta_to_id_, i_meta);
  i_meta = MapPick(self->meta_to_id_, id, MAP_KEY);
  ArrayPush(self->id_to_meta_, &i_meta);
}
