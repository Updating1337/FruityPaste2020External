#pragma once

#include "includes.h"

#include <Windows.h>
#include <string>

class util_t
{
public:
	void check_thread()
	{
		while (true)
		{
			if (!FindWindowA(_("UnityWndClass").c_str(), _("Rust").c_str())) exit(0);
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}

	std::string gen_random(const int len)
	{
		static const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
		std::string tmp_s;
		tmp_s.reserve(len);

		for (int i = 0; i < len; ++i) {
			tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		return tmp_s;
	}

	unsigned long get_time()
	{
		return std::chrono::system_clock::now().time_since_epoch().count() / 10000;
	}

	bool find_string(std::string string, std::string sub_str)
	{
		return string.find(sub_str) != std::string::npos;
	}
}util;