#include <stdio.h>
#include <iostream>
#include <string>
#include "Source/apps_times.h"
#include "Source/Argv_Parser.h"
#include "Source/apps_string.h"
#include "Source/work.h"


int main(int argc, char* argv[]) {

	Argv_Parser args = Argv_Parser(argc, argv);
	std::string name_file;
	std::string input;
	std::string time;

	if (args.help) {

	}
	if (args.day) {
		time = take_now_day();
		//strmcat(1, name_file, args.name_file, time);
		name_file += args.name_file + "_" + time;
	}
	else if (args.mon) {
		time = take_now_mon();
		//strmcat(1, name_file, args.name_file, time);
		name_file += args.name_file + "_" + time;
	}
	else {
		name_file = args.name_file;
	}

	work job = work(name_file);

	bool global_work = true;
	while (global_work) {
		//std::cin >> input;
		//std::cin.clear();
		//std::cin.sync();
		std::getline(std::cin, input);
		input = strtolower(input);
		input = delspace(input);
		if (input == "start" or input == "b") {
			job.start();
		}
		else if (input == "stop" or input=="e") {
			if (job.stop()) {
				//std::cin >> cache;
				std::string s_commit;
				std::getline(std::cin, s_commit);
				//std::cin.clear();
				//std::cin.sync();
				job.commit(s_commit);
			}
		}
		else if (input == "pause" or input=="p") {
			job.pause();
		}
		else if (input == "unpause" or input=="u") {
			job.unpause();
		}
		else if (input == "exit" or input=="q") {
			if (job.close()) {
				global_work = false;
			}
			else std::cout << "HOW ????\n";
		}
	}
}
