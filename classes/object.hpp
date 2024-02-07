#pragma once

#include "includes.h"

class Object
{
public:
	std::string get_class_name()
	{
		return driver.read_str(driver.read_chain<uintptr_t>(reinterpret_cast<uintptr_t>(this), { 0x0,0x10 }));
	}

	template<typename T>
	T get_class()
	{
		return driver.read_chain<T>(reinterpret_cast<uintptr_t>(this), { 0x10,0x28 });
	}
};