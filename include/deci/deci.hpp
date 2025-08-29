/**
 * @brief deci VM main header
 * @file deci.hpp
 * @author timur
 */

#pragma once
#ifndef __DECI_HEADER__
#define __DECI_HEADER__

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

//#include "value_t.hpp"
//#include "number_t.hpp"
//#include "string_t.hpp"
//#include "reference_t.hpp"
//#include "array_t.hpp"
//#include "dictionary_t.hpp"
//#include "stack_t.hpp"
//#include "vm_t.hpp"
//#include "function_t.hpp"
//#include "func_lib.hpp"
//#include "program_t.hpp"
#include "ast_t.hpp"
#include "compiler_t.hpp"
#include "symbol_table.hpp"

namespace deci {

template <typename T, size_t N>
constexpr size_t countof(T const (&)[N]) noexcept
{
	return N;
}

template<typename T>
constexpr size_t countof(T const& item) noexcept
{
	return item.size();
}

inline std::string ToUpper(const std::string& src) {
	std::string result;
	result.reserve(src.size());
	for (auto ch : src) {
		result.push_back((char)(toupper(ch)));
	}
	return result;
}

inline std::string ToLower(const std::string& src) {
	std::string result;
	result.reserve(src.size());
	for (auto ch : src) {
		result.push_back((char)(tolower(ch)));
	}
	return result;
}

}

#endif /* __DECI_HEADER__ */
