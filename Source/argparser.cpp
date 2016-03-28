#include <cstring>
#include <iostream>
int parser(int n, char* argvs[]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(argvs[i], "--help") == 0 || strcmp(argvs[i], "-h")) {
			std::cout << "Helping need working";
			return 0;
		}
		else if (strcmp(argvs[i], "-d") == 0 || strcmp(argvs[i], "--day")){
			std::cout << "Days";
			return 1;
		} 
		else if (strcmp(argvs[i], "--months") == 0 || strcmp(argvs[i], "-m")){
			std::cout << "Monhts";
			return 2;
		}
		else{
			return 3;
		}
	}
}
