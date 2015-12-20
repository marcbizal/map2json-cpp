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

const boost::regex MAP_FILTER("cror|path|dugg|high|surf|fall", boost::regex::icase);

class Writer
{
private:
	std::map<std::string, Map> map_;
	std::string name_;
public:
	Writer(const std::string &input_folder);
	~Writer();

	void saveAs(const std::string &output_file);
	void save();
};

