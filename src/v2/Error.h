#ifndef DAC_V2_ERROR_H_
# define DAC_V2_ERROR_H_

#define DAC_OK "ok"
#define DAC_ERR_ALLOC "alloc error"
#define DAC_ERR_COPY "copy data error"
#define DAC_ERR_REHASH "rehash error"
#define DAC_ERR_INSERT "insert data failed"
#define DAC_ERR_EXISTS "insert failed as the element exist"
#define DAC_ERR_PUSH "push failed"
#define DAC_ERR_PULL "pull failed"
#define DAC_ERR_MISSIG_OPEN "missing open %c"
#define DAC_ERR_MISSIG_CLOSE "missing close %c"
#define DAC_ERR_MISSIG_SPERATOR "missing seperator %c"
#define DAC_ERR_MISSIG_LOOKAHEAD "missing lookahead charactor"

#define DacInfo(prefix, flow, format, ...) \
    (fprintf(flow, "%s:%s:%d" prefix, __FILE__, __func__, __LINE__), \
     fprintf(flow, format,##__VA_ARGS__), \
     fputs(".\n", flow))

#define DacErr(ret, format, ...) \
    (DacInfo(":ERR: ", stderr, format,##__VA_ARGS__), (ret))

#define DacWarn(ret, format, ...) \
    (DacInfo(":WARN: ", stderr, format,##__VA_ARGS__), (ret))

#define DacGoto(tag, code, ...) \
    do {DacErr(-1, code,##__VA_ARGS__); goto tag;} while (0)

#define DacCheck(expr, ret) \
    if (expr) return DacErr((ret), "%s", strerror(errno))

#define DacCheckAndFree(expr, old, ret) \
    if (expr) return DacErr((ret), "%s", strerror(errno)), free(old), (ret)

#endif
