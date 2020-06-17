#pragma once

#include <tuple>

#define __defer_helper(code, count, tup)                           \
struct __defer_struct_##count {                                    \
    decltype(tup) const& params;                                   \
    __defer_struct_##count(decltype(tup) const& t) : params(t) { } \
    ~__defer_struct_##count() { using namespace std; code; }        \
};                                                                 \
__defer_struct_##count __defer_variable_##count (tup)

#define __defer_ind(code, count, tup) __defer_helper(code, count, tup)

#define defer(code, ...) __defer_ind(code, __COUNTER__, std::make_tuple(__VA_ARGS__))