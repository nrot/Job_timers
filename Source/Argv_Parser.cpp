#include "Argv_Parser.h"
#include <cstring>

using namespace std;

Argv_Parser::Argv_Parser(int n, char* argvs[])
{
	for (int i = 0; i < n; i++) {
		if (strcmp(argvs[i], "--help") == 0 || strcmp(argvs[i], "-h")) {
			help = true;
		}
		else if (strcmp(argvs[i], "-d") == 0 || strcmp(argvs[i], "--day")) {
			day = true;
		}
		else if (strcmp(argvs[i], "--months") == 0 || strcmp(argvs[i], "-m")) {
			mon = true;
		}
		else if (i == 1) {
			name_file = argvs[1];
		}
	}
}
