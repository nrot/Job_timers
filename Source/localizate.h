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

using json = nlohmann::json;

class localizate {
public:
	localizate(char* lc);
private:
	std::ofstream file;
	ERRORS_CODES error = OK;
	json json_str;
};

#endif /* LOCALIZATE_H_ */
