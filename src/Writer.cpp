#include "Writer.h"

// UTILITY FUNCTIONS

void to_lower(std::string &s)
{
	for (decltype(s.size()) i = 0; i < s.length(); i++)
	{
		s[i] = tolower(s[i]);
	}
}

std::string to_lower(const std::string &s)
{
	std::string ret = s;
	to_lower(ret);
	return ret;
}

std::vector<std::string> split(string &s, const string &delim)
{
	std::vector<std::string> tokens;

	size_t current;
	size_t next = -1;
	do
	{
		current = next + 1;
		next = s.find_first_of(delim, current);
		tokens.push_back(s.substr(current, next - current));
	}
	while(next != string::npos);

	return tokens;
}

// CLASS IMPLEMENTATION

Writer::Writer(const std::string &input_folder)
{
	name_ = input_folder;
	using boost::filesystem::directory_iterator;

	std::string filename = "";
	for (directory_iterator iterator(input_folder); iterator != directory_iterator(); ++iterator)
	{
		filename = iterator->path().filename().string();

		boost::smatch match;
		if (boost::regex_search(filename, match, MAP_FILTER))
		{
			std::vector<std::string> tokens = split(filename, "_.");

			std::string map_type = tokens[MAP_TYPE];
			to_lower(map_type);

			//std::cout << map_type << std::endl;
			map_[map_type] = Map(iterator->path().string());
		}
	}
}

Writer::~Writer()
{

}

void Writer::saveAs(const std::string &output_file, const bool padZeros = false)
{
	fstream jsonFile;
	jsonFile.open(output_file, std::ios::out | std::ios::trunc);

	if (jsonFile.is_open())
	{
		jsonFile << "{\n";

		// Write header information
		jsonFile << "\"name\": \"" << name_ << "\",\n";
		jsonFile << "\"width\": " << map_["surf"].getWidth() << ",\n";
		jsonFile << "\"height\": " << map_["surf"].getHeight() << ",\n";

		// Write actual map data
		std::string mapJSON;
		for (auto it = map_.begin(); it != map_.end(); it++)
		{
			mapJSON = it->second.jsonify(padZeros);
			jsonFile << "\"" << to_lower(it->first) << "\": " << mapJSON;

			if (next(it) != map_.end()) jsonFile << ",\n";
		}

		jsonFile << "}\n";
	}
	else
	{
		std::cerr << "[!!] Could not open file " << output_file << " for writing." << std::endl;
	}

	jsonFile.close();
}

void Writer::save(const bool padZeros = false)
{
	saveAs(name_ + ".json", padZeros);
}
