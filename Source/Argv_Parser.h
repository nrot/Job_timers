#pragma once
#include <string>

class Argv_Parser
{
public:
	bool help = false;
	bool day = false;
	bool mon = true;
	std::string name_file = "journal";
	Argv_Parser(int n, char* argvs[]);
};

