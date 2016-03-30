#include <stdarg.h>
#include <string>
#include "apps_string.h"
void strmcat(int n,std::string destr,const std::string str, ...) {
	va_list ap;
	std::string val;
	va_start(ap, str);
	destr += str;
	//strcat(destr, str);
	for (int i = 0; i < n; i++) {
		val = va_arg(ap, char*);
		//strcat(destr, val);
		destr += val;
	}
}

std::string strtolower(std::string str)
{
	//for (int i = 0; i < strlen(str); i++) {
	std::string cache = str;
	for (int i = 0; i < str.length(); i++){
		cache[i] = tolower(str[i]);
	}
	return cache;
}

std::string delspace(std::string str)
{
	int start = 0;
	//int stop = strlen(str);
	int stop = str.length();
	for (int i = 0; i < stop; i++) {
		if (isspace(str[i])) {
			start++;
		}
		else break;
	}
	for (int i = stop; i > start; i--) {
		if (isspace(str[i])) {
			stop--;
		}
		else break;
	}
	return std::string(str, start, stop - start);
	//return strncpy(start, stop, str);
}
/*
std::string strncpy(int sr, int sp, std::string str)
{
	//std::string re_s = new std::string(sp-sr, ' ');
	for (int i = 0; i < (sp - sr); i++) {
		re_s[i] = str[i + sr];
	}
	return re_s;
}
*/
