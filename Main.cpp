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
	std::string cache;

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
		std::cin >> input;
		input = strtolower(input);
		input = delspace(input);
		if (input == "start") {
			job.start();
		}
		else if (input == "stop") {
			if (job.stop()) {
				//std::cin >> cache;
				std::getline(std::cin, cache);
				job.commit(cache);
			}
		}
		else if (input == "pause") {
			job.pause();
		}
		else if (input == "unpause") {
			job.unpause();
		}
		else if (input == "exit") {
			if (job.close()) {
				global_work = false;
			}
			else std::cout << "HOW ????\n";
		}
	}
}
