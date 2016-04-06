#include "work.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include "apps_times.h"
#include <cmath>
#include "localizate.h"

work::work(std::string name, localizate* lc){

	if (lc->is_error()){
		error = ERROR_LOCAL;
	}
	else {
		obj_loc = lc;
		file.open(name, std::fstream::app | std::fstream::out);
		if (file.rdstate() && std::fstream::failbit != 0){
			std::cout << obj_loc->find_loc("Couldnt create or open file:")<< name;
			error = FILENOTOPEN;
		}
		else
		{
			std::cout << obj_loc->find_loc("File is opened ok:") << name << "\n:";
			name_file = name;
		}
	}
}

void work::start()
{
	if (status == IDLE) {
		start_work = time(NULL);
		status = WORK;
		std::cout << obj_loc->find_loc("Work is started:") << ctime(&start_work)<<"\n:";
		file << SEPARATOR << obj_loc->find_loc("Work is started:") << ctime(&start_work) << "\n";
		reopen();
		return;
	} 
	else{
		switch (status)
		{
		case work::WORK:
			std::cout << obj_loc->find_loc("Work is already started, u can use end (e)")<< "\n:";
			return;
		break;
		case work::PAUSE:
			std::cout << obj_loc->find_loc("Work is paused, u can use unpause (u)") << "\n:";
			return;
		break;
		case work::COMMIT:
			std::cout << obj_loc->find_loc("Work is not started, u can use begin (b)") << "\n:";
			return;
		break;
		}
	}
}

bool work::stop()
{
	time_t tt;
	struct tm * take_time;
	switch (status)
	{
	case work::IDLE:
		std::cout << obj_loc->find_loc("Work is not started, u can use begin (b)")<< "\n:";
		return false;
		break;
	case work::WORK:
		end_work = time(NULL);
		tt = end_work - start_work - all_pause;
		take_time = gmtime(&tt);
		status = COMMIT;
		std::cout << obj_loc->find_loc("Work is ended:") << ctime(&end_work) << "\n"<< obj_loc->find_loc("Duration:")<<ctime(&tt);
		file << obj_loc->find_loc("Take time:");
		if (sec_to_day(tt) > 0) file << obj_loc->find_loc("days=") << sec_to_day(tt) << ";";
		if (sec_to_fhour(tt) > 0) file << obj_loc->find_loc("hours=") << (floor(sec_to_fhour(tt))*10)/10 << ";";
		if (sec_to_mins(tt) > 0) file << obj_loc->find_loc("mins=") << sec_to_mins(tt) << ";";
		reopen();
		std::cout << "\n"<< obj_loc->find_loc("Write your comment:")<< "\n";
		//file << "Work is ended: " << ctime(&end_work) << "\n" << SEPARATOR;
		return true;
		break;
	case work::PAUSE:
		std::cout << obj_loc->find_loc("Work is paused, u can use unpause (u)") << "\n:";
		return false;
		break;
	case work::COMMIT:
		std::cout << obj_loc->find_loc("Please dont write commands in the start of your comment:") << "\n";
		return false;
		break;
	}
}

void work::pause()
{
	switch (status)
	{
	case work::IDLE:
		std::cout << obj_loc->find_loc("Work is not started, u can use begin (b)") << "\n:";
		return;
		break;
	case work::WORK:
		pause_start = time(NULL);
		status = PAUSE;
		std::cout << obj_loc->find_loc("Work is paused:") << ctime(&pause_start) << "\n:";
		file << obj_loc->find_loc("Work is paused:") << ctime(&pause_start) << "\n";
		reopen();
		return;
		break;
	case work::PAUSE:
		std::cout << obj_loc->find_loc("Work is paused, u can use unpause (u)") << "\n:";
		return;
		break;
	case work::COMMIT:
		std::cout << obj_loc->find_loc("Please dont write commands in the start of your comment:") << "\n";
		return;
		break;
	}
}

void work::unpause()
{
	switch (status)
	{
	case work::IDLE:
		std::cout << obj_loc->find_loc("Work is not started, u can use begin (b)") << "\n:";
		return;
		break;
	case work::WORK:
		std::cout << obj_loc->find_loc("Work is not paused, u can use pause (p)") << "\n:";
		return;
		break;
	case work::PAUSE:
		pause_end = time(NULL);
		all_pause += pause_end - pause_start;
		status = WORK;
		std::cout << obj_loc->find_loc("Work is unpaused:") << ctime(&pause_end) << "\n:";
		file << obj_loc->find_loc("Work is unpaused:") << ctime(&pause_end) << "\n";
		reopen();
		return;
		break;
	case work::COMMIT:
		std::cout << obj_loc->find_loc("Please dont write commands in the start of your comment:") << "\n";
		return;
		break;
	}
}

void work::commit(std::string str)
{
	switch (status)
	{
	case work::IDLE:
		std::cout << obj_loc->find_loc("Work is not started, u can use begin (b)") << "\n:";
		return;
		break;
	case work::WORK:
		std::cout << obj_loc->find_loc("Work is not ended, u can use end (e)") << "\n:";
		return;
		break;
	case work::PAUSE:
		std::cout << obj_loc->find_loc("Work is paused, u can use unpause (u) and stop (e)") << "\n:";
		return;
		break;
	case work::COMMIT:
		//std::cout << "U write this commit:" << str < "\n:";
		std::cout << obj_loc->find_loc("The comment is saved") << "\n";
		file << "\n" << obj_loc->find_loc("Comment:") << str << "\n" << obj_loc->find_loc("Work is ended:") << ctime(&end_work) << "" << SEPARATOR;
		status = IDLE;
		reopen();
		return;
		break;
	}
}

bool work::wait_commit()
{
	if (status == COMMIT) return true;
	else return false;
}

bool work::close()
{
	const std::string ByeBye = obj_loc->find_loc("ByeBye") + "\n";
	std::string cache = "";
	std::string cache_2 = "";

	switch (status)
	{
	case work::IDLE:
		std::cout << ByeBye;
		file.close();
		return true;
		break;
	case work::WORK:
		if (stop()) {
			std::cin >> cache;
			commit(cache);
			std::cout << ByeBye;
			file.close();
			return true;
		}
		else return false;
		break;
	case work::PAUSE:
		std::cout << obj_loc->find_loc("Work is paused. Comment and exit or just exit? (c/e)") << "\n";
		std::cin >> cache;
		if (cache == "c") {
			unpause();
			stop();
			if (stop()) {
				std::cin >> cache_2;
				commit(cache_2);
				std::cout << ByeBye;
				file.close();
				return true;
			}
			else return false;
		}
		else if (cache == "e") {
			unpause();
			stop();
			if (stop()) {
				commit("Fast exit!!!\n");
				file.close();
				return true;
			}
			else return false;
		}
		break;
	case work::COMMIT:
		std::cout << "How u do this ?";
		file.close();
		return true;
		break;
	}
}

void work::reopen()
{
	file.flush();
	/*
	file.close();
	file.open(name_file, std::fstream::app | std::fstream::out);
	if (file.rdstate() && std::fstream::failbit != 0) {
		std::cout << "Failed to create or open file: " << name_file;
		error = FILENOTOPEN;
		return false;
	}
	else
	{
		return true;
	}*/
}

bool work::is_error(){
	if (error != OK){
		return true;
	} else return false;
}
