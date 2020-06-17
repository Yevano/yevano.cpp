#pragma once

#include <Windows.h>

#define _WD(x) L##x
#define WD(x) _WD(x)

#define panic_if_win_err(code, ...) _panic_if_win_err(code, __LINE__, WD(__FILE__))
#define panic_if_win_null(value) _panic_if_win_null(value, __LINE__, WD(__FILE__))

[[noreturn]] void panic_win(int line, WCHAR const* file);

void _panic_if_win_err_impl(DWORD error_code, int line, WCHAR const* file);

template<typename value_type>
inline value_type _panic_if_win_null(value_type value, int line, WCHAR const* file) {
    if(value) {
        return value;
    }

    panic_win(line, file);
}

template<typename... arg_types>
inline auto _panic_if_win_err(auto value, int line, WCHAR const* file, arg_types... args) {
    if constexpr(sizeof...(args) == 0) {
        _panic_if_win_err_impl((DWORD) (LONGLONG) value, line, file);
        return value;
    } else {
        if(((value == args) || ... || false)) {
            return value;
        }

        _panic_if_win_err_impl((DWORD) (LONGLONG) value, line, file);
    }
}