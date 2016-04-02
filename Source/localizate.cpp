/*
 * localizate.cpp
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: nrot
 */

#include "localizate.h"
#include "src/json.hpp"
#include <string>\

using json = nlohmann::json;

localizate::localizate(char* lc) {
	if (lc == NULL){
		//lc = "en_US";
	}
	std::string name_file = "local.json";
	std::string cache;
	file.open(name_file, std::fstream::in);
	if (file.rdstate() && std::fstream::failbit != 0){
		std::cout << "Failed to create or open file: "<< name_file;
		error = FILENOTOPEN;
	}
	else
	{
		//std::cout << "File open normal: " << name_file << "\n:";
		//file >> cache;
		json_str = json::parse(cache);
		if (json_str.find(lc) == json_str.end()){
			//lc = "en_US";
		}
	}
}

