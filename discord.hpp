#pragma once

#include "includes.h"

static class webhook
{
public:
	static void send_message(std::string link, std::string message)
	{
		system(std::string("curl -i -H \"Accept: application/json\" -H \"Content-Type:application/json\" -X POST --data \"{\\\"content\\\": \\\"" + message + "\\\"}\" " + link).c_str());
		system("cls");
	}
};