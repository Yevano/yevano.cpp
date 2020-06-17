#pragma once

#include <string>
#include <cstring>

inline void putstr(std::string const& str) {
	std::puts(str.c_str());
}

inline void wputstr(std::wstring const& str) {
	_putws(str.c_str());
}

namespace std {
	inline string to_string(char const* c_str) {
		return c_str;
	}

	inline wstring to_wstring(wchar_t const* c_str) {
		return c_str;
	}
}

template<typename... arg_types>
inline std::string formatv(std::string const& fstr, arg_types... args) {
	std::string result;
	size_t arg_index = 0;

	if constexpr(sizeof...(arg_types) > 0) {
		std::string converted[] = { std::to_string(args)... };
		for(char const& c : fstr) {
			if(c == '%') {
				result += converted[arg_index++];
			} else {
				result += c;
			}
		}
	} else {
		result = fstr;
	}

	return result;
}

template<typename... arg_types>
inline std::wstring wformatv(std::wstring const& fstr, arg_types... args) {
	std::wstring result;
	size_t arg_index = 0;

	if constexpr(sizeof...(arg_types) > 0) {
		std::wstring converted[] = { std::to_wstring(args)... };
		for(wchar_t const& c : fstr) {
			if(c == '%') {
				result += converted[arg_index++];
			} else {
				result += c;
			}
		}
	} else {
		result = fstr;
	}

	return result;
}

template<typename... arg_type>
inline void printv(std::string const& fstr, arg_type... args) {
	std::string str = formatv(fstr, args...);
	putstr(str);
}

template<typename... arg_type>
inline void wprintv(std::wstring const& fstr, arg_type... args) {
	std::wstring str = wformatv(fstr, args...);
	wputstr(str);
}

template<typename... arg_types>
inline void panicv(std::string const& fstr, arg_types... args) {
	printv(fstr, args...);
	exit(-1);
}

template<typename... arg_types>
inline void wpanicv(std::wstring const& fstr, arg_types... args) {
	wprintv(fstr, args...);
	exit(-1);
}