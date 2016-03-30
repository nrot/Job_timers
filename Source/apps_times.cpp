#include <time.h>
#include <string>
#include "apps_string.h"
#include "apps_times.h"

std::string  take_now_day() {
	time_t rawtime;
	struct tm * ptm;
	time(&rawtime);
	ptm = gmtime(&rawtime);
	std::string s_tm_year = std::to_string(ptm->tm_year);
	std::string s_tm_mon = std::to_string(ptm->tm_mon + 1);
	std::string s_tm_mday = std::to_string(ptm->tm_mday);
	std::string s;
	//strmcat(4, s, s_tm_year.c_str(), '_', s_tm_mon.c_str(),'_', s_tm_mday.c_str());
	s += s_tm_year + '_' + s_tm_mon + '_' + s_tm_mday;
	return s;
}

std::string  take_now_mon() {
	time_t rawtime;
	struct tm * ptm;
	time(&rawtime);
	ptm = gmtime(&rawtime);
	std::string s_tm_year = std::to_string(ptm->tm_year);
	std::string s_tm_mon = std::to_string(ptm->tm_mon + 1);
	//std::string s_tm_mday = std::to_string(ptm->tm_mday);
	//char s[20];
	std::string s;
	//strmcat(2, s, s_tm_year.c_str(), '_', s_tm_mon.c_str());
	s += s_tm_year + '_' + s_tm_mon;
	return s;
}

int sec_to_mins(int n)
{
	int amount_min = (n - (n % 60)) / 60;
	if (n % 60 > 0) {
		amount_min++;
	}
	return amount_min;
}

int min_to_hour(int n)
{
	return (n - (n % 60)) / 60;
}

int hour_to_day(int n)
{
	return (n - (n % 24)) / 24;
}

int sec_to_hour(int n)
{
	return min_to_hour(sec_to_mins(n));
}

int sec_to_day(int n)
{
	return hour_to_day(sec_to_hour(n));
}
float sec_to_fhour(int n){
	return (sec_to_mins(n) / 60);
}

std::string mstrftime(std::string templ, time_t tn){
	char* buff;
	strftime(buff, sizeof buff, templ.c_str(), gmtime(&tn));
}
