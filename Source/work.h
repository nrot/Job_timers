#pragma once
#include <time.h>
#include <fstream>
#include "Errors_codes.h"
#include <string>
#include "localizate.h"

class work
{
public:
	work(std::string name, localizate* lc);
	void start();
	bool stop();
	void pause();
	void unpause();
	void commit(std::string str);
	bool wait_commit();
	bool close();
	bool reopen();
	bool is_error();
private:
	enum state
	{
		IDLE,
		WORK,
		PAUSE,
		COMMIT
	};
	localizate* obj_loc;
	state status = IDLE;
	std::ofstream file;
	time_t start_work, end_work,
		pause_start, pause_end;
	time_t all_pause = 0;
	std::string descript_work, name_file;
	ERRORS_CODES error = OK;
	const std::string SEPARATOR = "###########################################\n";
};

