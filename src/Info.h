#ifndef INFO_H
#define INFO_H

#include "Basic.i"
 
struct Info {
  dif_char* name_;
  dif_size size_,
         offset_;
  BasicI Basic_;
};
typedef struct Info Info;
typedef const struct Info *LockedPtrInfo;

#endif
