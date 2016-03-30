#include "work.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include "apps_times.h"
#include <cmath>

work::work(std::string name) {
	file.open(name, std::fstream::app | std::fstream::out);
	if (file.rdstate() && std::fstream::failbit != 0){
		std::cout << "Failed to create or open file: "<< name;
		error = FILENOTOPEN;
	}
	else
	{
		std::cout << "File open normal: " << name << "\n:";
		name_file = name;
	}
}

void work::start()
{
	if (status == IDLE) {
		start_work = time(NULL);
		status = WORK;
		std::cout << "Work started: " << ctime(&start_work)<<"\n:";
		file << SEPARATOR << "Work started: " << ctime(&start_work) << "\n";
		reopen();
		return;
	} 
	else{
		switch (status)
		{
		case work::WORK:
			std::cout << "Work already start, u can use stop (e) \n:";
			return;
		break;
		case work::PAUSE:
			std::cout << "Work on pause, u can use unpause (u) \n:";
			return;
		break;
		case work::COMMIT:
			std::cout << "Work not start, u can use start (b) \n:";
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
		std::cout << "Work not start, u can use start (b) \n:";
		return false;
		break;
	case work::WORK:
		end_work = time(NULL);
		tt = end_work - start_work - all_pause;
		take_time = gmtime(&tt);
		status = COMMIT;
		std::cout << "Work stoped: " << ctime(&end_work) << "\n Time take:"<<ctime(&tt);
		file << "Take time: ";
		if (sec_to_day(tt) > 0) file << "days= " << sec_to_day(tt) << ";";
		if (sec_to_fhour(tt) > 0) file << "hours= " << (floor(sec_to_fhour(tt))*10)/10 << ";";
		if (sec_to_mins(tt) > 0) file << "mins= " << sec_to_mins(tt) << ";";
		if (!reopen()) {
			return false;
		}
		std::cout << "\nWrite commit:\n";
		//file << "Work stoped: " << ctime(&end_work) << "\n" << SEPARATOR;
		return true;
		break;
	case work::PAUSE:
		std::cout << "Work on pause, u can use unpause (u) \n:";
		return false;
		break;
	case work::COMMIT:
		std::cout << "Please write commit without smth command on start string\n:";
		return false;
		break;
	}
}

void work::pause()
{
	switch (status)
	{
	case work::IDLE:
		std::cout << "Work not start, u can use start (b) \n:";
		return;
		break;
	case work::WORK:
		pause_start = time(NULL);
		status = PAUSE;
		std::cout << "Work on puase: " << ctime(&pause_start) << "\n:";
		file << "Work on puase: " << ctime(&pause_start) << "\n";
		reopen();
		return;
		break;
	case work::PAUSE:
		std::cout << "work already pause, u can use unpause (u) \n:";
		return;
		break;
	case work::COMMIT:
		std::cout << "Please write commit without smth command on start string\n:";
		return;
		break;
	}
}

void work::unpause()
{
	switch (status)
	{
	case work::IDLE:
		std::cout << "Work not starteds, u can use start (b)\n:";
		return;
		break;
	case work::WORK:
		std::cout << "Work not pause, u can use pause (p)\n:";
		return;
		break;
	case work::PAUSE:
		pause_end = time(NULL);
		all_pause += pause_end - pause_start;
		status = WORK;
		std::cout << "Work unpause on:" << ctime(&pause_end) << "\n:";
		file << "Work unpause on:" << ctime(&pause_end) << "\n";
		reopen();
		return;
		break;
	case work::COMMIT:
		std::cout << "Please write commit without smth command on start string\n:";
		return;
		break;
	}
}

void work::commit(std::string str)
{
	switch (status)
	{
	case work::IDLE:
		std::cout << "Work not start, u can use start (b)\n:";
		return;
		break;
	case work::WORK:
		std::cout << "Work not stoped, u can use stop (e)\n:";
		return;
		break;
	case work::PAUSE:
		std::cout << "Work on pause, u can use unpause (u) and stop (e)\n:";
		return;
		break;
	case work::COMMIT:
		//std::cout << "U write this commit:" << str < "\n:";
		std::cout << "Commit write\n";
		file << "\nWhat do: " << str << "\n" << "Work stoped: " << ctime(&end_work) << "" << SEPARATOR;
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
	const std::string ByeBye = "ByeBye\n";
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
		std::cout << " Work on pause. Commit and exit or just exit? (c/e)\n";
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

bool work::reopen()
{
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
	}
}

