#pragma once 
#include <utility>

// Helper for std::visit with multiple lambdas
template<class... Ts>
struct overloaded : Ts... {
	using Ts::operator()...;
};

// Deduction guide (C++17+)
template<class... Ts>
overloaded(Ts...)->overloaded<Ts...>;
