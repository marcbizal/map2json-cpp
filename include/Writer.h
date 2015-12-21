#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/utility.hpp>
#include <map>
#include "Map.h"

void to_lower(std::string &s);
std::string to_lower(const std::string &s);
std::vector<std::string> split(string &s, const string &delim);

const boost::regex MAP_FILTER("(cror|path|dugg|high|surf|fall).*map", boost::regex::icase);

class Writer
{
private:
	std::map<std::string, Map> map_;
	std::string name_;
	enum { MAP_TYPE, LEVEL_NUM, FILE_TYPE };
public:
	Writer(const std::string &input_folder);
	~Writer();

	void saveAs(const std::string &output_file);
	void save();
};
