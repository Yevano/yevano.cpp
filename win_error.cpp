#include "win_error.h"
#include "format.h"
#include "defer.h"

#include <optional>

constexpr size_t min_error_message_length = 1024;
WCHAR* win_error_message_buffer;

[[noreturn]] void panic_win(int line, WCHAR const* file) {
    auto error_code = GetLastError();

    if(!error_code) {
        wprintv(L"[% line %]\nGot null, but no error code found.", file, line);
        exit(-1);
    }

    DWORD char_count = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, nullptr, error_code, 0, (LPWSTR) (void*) &win_error_message_buffer, min_error_message_length, nullptr);
    defer(if(win_error_message_buffer) LocalFree(win_error_message_buffer), win_error_message_buffer);

    if(char_count == 0) {
        // The error code did not exist in the system errors.
        // Try Ntdsbmsg.dll for the error code.

        HINSTANCE lib = LoadLibraryA("Ntdsbmsg.dll");

        if(lib != NULL) {
            char_count = FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, lib, error_code, 0, (LPWSTR) (void*) &win_error_message_buffer, min_error_message_length, nullptr);
            FreeLibrary(lib);
        }
    }

    if(char_count == 0) {
        wprintv(L"[% line %]\nUnknown Windows error: %", file, line, error_code);
        exit(-1);
    }

    wprintv(L"[% line %]\n%", file, line, win_error_message_buffer);
    exit(-1);
}

void _panic_if_win_err_impl(DWORD error_code, int line, WCHAR const* file) {
    if(error_code == S_OK) return;
    SetLastError(error_code);
    panic_win(line, file);
}