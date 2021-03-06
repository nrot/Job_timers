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
	if (lc != NULL){
		now_local = "";
		for (int i=0; i<5; i++){
			now_local += ((const char*)lc)[i];
		}
	}
	std::string name_file = "local.json";
	std::string cache = "";
	file.open(name_file, std::fstream::in);
	if (file.rdstate() && std::fstream::failbit != 0){
		std::cout << "Failed to create or open file: "<< name_file;
		error = FILENOTOPEN;
	}
	else
	{
		//std::cout << "File open normal: " << name_file << "\n:";
		while (!file.eof()){
			std::string c;
			std::getline(file, c);
			cache += c;
		}
		local_json = json::parse(cache);
		std::string cache = "";
		for (int i=0; i<5; i++){
			cache += ((const char*)lc)[i];
		}
		if (local_json.find(cache) != local_json.end()){
			now_local = cache;
			//std::cout<<local_json.find(cache).value();
			local_json = json::parse(local_json.find(cache).value().dump());
		}
	}
}
std::string localizate::find_loc(std::string f){
	if (local_json.find(f) != local_json.end()){
		return local_json.find(f).value();
	} else {
		return f;
	}
}
std::string localizate::separator(){
	std::string sep = "separator";
	if (local_json.find(sep) != local_json.end()){
		return local_json.find(sep).value();
	} else {
		return "################################################################";
	}
}

bool localizate::is_error(){
	if (error != OK){
		return true;
	} else return false;
}
