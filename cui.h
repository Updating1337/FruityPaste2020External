#include <Windows.h>
#include <iostream>

////#include "Obsidium/obsidium64.h"

namespace cui
{
	enum response
	{
		success,
		warning,
		failed
	};

	void set_color(int color)
	{
		//OBSIDIUM_VM_START;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		// OBSIDIUM_VM_END;
	}

	void print(char* str, response status)
	{
		//OBSIDIUM_VM_START;
		printf("%s\n", str);
		// OBSIDIUM_VM_END;
	}
	void printa(const char* str, response status)
	{
		//OBSIDIUM_VM_START;
		printf(str);

		set_color(0xf);
		printf(" [ ");
		switch (status)
		{
		case response::success:
			set_color(0xa);
			printf("OK");
			break;
		case response::failed:
			set_color(0x4);
			printf("ERROR");
			break;
		case response::warning:
			set_color(0xe);
			printf("WARNING");
			break;
		}
		set_color(0xf);
		printf(" ]\n");
		// OBSIDIUM_VM_END;
	}
	std::string input(char* str, response status)
	{
		//OBSIDIUM_VM_START;
		str[0] = toupper(str[0]);

		printf(str);

		set_color(0xf);
		printf(" [ ");
		switch (status)
		{
		case response::success:
			set_color(0xa);
			break;
		case response::failed:
			set_color(0x4);
			break;
		case response::warning:
			set_color(0x6);
			break;
		}
		printf("ENTER");

		set_color(0xf);
		printf(" ] ");

		std::string ret;
		//getline(cin, ret);
		// OBSIDIUM_VM_END;
		return ret;
	}
}