/*
 * localizate.h
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: nrot
 */

#ifndef LOCALIZATE_H_
#define LOCALIZATE_H_

#include <fstream>
#include "Errors_codes.h"
#include "src/json.hpp"
#include <string>

using json = nlohmann::json;

class localizate {
public:
	localizate(char* lc);
	std::string find_loc(std::string f);
	std::string separator();
	bool is_error();
private:
	std::string now_local = "en_US";
	std::ifstream file;
	ERRORS_CODES error = OK;
	json local_json;
};

#endif /* LOCALIZATE_H_ */
