#include <time.h>
#include <string>
#include "apps_string.h"
#include "apps_times.h"

std::string  take_now_day() {
	time_t rawtime;
	struct tm * ptm;
	time(&rawtime);
	//s += s_tm_year + '_' + s_tm_mon + '_' + s_tm_mday;
	return mstrftime("%Y_%m_%d", rawtime);
}

std::string  take_now_mon() {
	time_t rawtime;
	struct tm * ptm;
	time(&rawtime);
	//s += s_tm_year + '_' + s_tm_mon;
	return mstrftime("%Y_%m", rawtime);
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
