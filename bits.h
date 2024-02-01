#ifndef __bits_h__
#define __bits_h__

#include <stddef.h>
#include <stdint.h>

#define EVALARGS(...) __VA_ARGS__

typedef struct
{
    uint8_t val;
    char *desc;
} bits_desc_t;

typedef struct
{
    uint8_t fst : 3;
    uint8_t lst : 3;
    char *desc;
    bits_desc_t *bits;
} bits_group_t;

typedef struct
{
    bits_group_t **groups;
    char *desc;
} bits_value_t;

#define BITS_GROUP(_name, _fst, _lst, ...)                      \
    bits_desc_t _name##_bits[] = {__VA_ARGS__, {.desc = NULL}}; \
    bits_group_t _name = {.fst = _fst, .lst = _lst, .desc = #_name, .bits = _name##_bits}

#define BITS_SINGLE(_name, _fst, ...) BITS_GROUP(_name, _fst, _fst, __VA_ARGS__)

#define DESC(_val, _desc)          \
    {                              \
        .val = _val, .desc = _desc \
    }

#define BITS_N_VA_ARGS_(_15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N
#define BITS_N_VA_ARGS(...) BITS_N_VA_ARGS_(__VA_ARGS__ __VA_OPT__(, ) 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define BITS_FOREACH_0(FN, ...)
#define BITS_FOREACH_1(FN, E, ...) FN(E)
#define BITS_FOREACH_2(FN, E, ...) FN(E) BITS_FOREACH_1(FN, __VA_ARGS__)
#define BITS_FOREACH_3(FN, E, ...) FN(E) BITS_FOREACH_2(FN, __VA_ARGS__)
#define BITS_FOREACH_4(FN, E, ...) FN(E) BITS_FOREACH_3(FN, __VA_ARGS__)
#define BITS_FOREACH_5(FN, E, ...) FN(E) BITS_FOREACH_4(FN, __VA_ARGS__)
#define BITS_FOREACH_6(FN, E, ...) FN(E) BITS_FOREACH_5(FN, __VA_ARGS__)
#define BITS_FOREACH_7(FN, E, ...) FN(E) BITS_FOREACH_6(FN, __VA_ARGS__)
#define BITS_FOREACH_8(FN, E, ...) FN(E) BITS_FOREACH_7(FN, __VA_ARGS__)
#define BITS_FOREACH_9(FN, E, ...) FN(E) BITS_FOREACH_8(FN, __VA_ARGS__)
#define BITS_FOREACH_10(FN, E, ...) FN(E) BITS_FOREACH_9(FN, __VA_ARGS__)
#define BITS_FOREACH_11(FN, E, ...) FN(E) BITS_FOREACH_10(FN, __VA_ARGS__)
#define BITS_FOREACH_12(FN, E, ...) FN(E) BITS_FOREACH_11(FN, __VA_ARGS__)
#define BITS_FOREACH_13(FN, E, ...) FN(E) BITS_FOREACH_12(FN, __VA_ARGS__)
#define BITS_FOREACH_14(FN, E, ...) FN(E) BITS_FOREACH_13(FN, __VA_ARGS__)
#define BITS_FOREACH_15(FN, E, ...) FN(E) BITS_FOREACH_14(FN, __VA_ARGS__)

#define BITS_FOREACH__(FN, NARGS, ...) BITS_FOREACH_##NARGS(FN, __VA_ARGS__)
#define BITS_FOREACH_(FN, NARGS, ...) BITS_FOREACH__(FN, NARGS, __VA_ARGS__)
#define BITS_FOREACH(FN, ...) BITS_FOREACH_(FN, BITS_N_VA_ARGS(__VA_ARGS__), __VA_ARGS__)

#define BITS_AMPERSAND(x) &x,

#define BITS_VALUE(_name, ...)                                                         \
    bits_group_t *_name##_groups[] = {BITS_FOREACH(BITS_AMPERSAND, __VA_ARGS__) NULL}; \
    bits_value_t _name = {.desc = #_name, .groups = _name##_groups}

#define DEFINE_BITS(b) extern bits_value_t b;

#endif