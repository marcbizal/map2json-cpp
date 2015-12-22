#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const bool FIX_SOIL = true;

std::string padWithZeros(const unsigned int numZeros, const std::string &original);

class Map
{
private:
	typedef struct MAP_HEADER
	{
		char MAP[4];
		uint32_t chunkSize;
		uint32_t width;
		uint32_t height;
	};

	vector<vector<uint32_t>> tile_;
	uint32_t width_; uint32_t height_;
public:
	Map();
	Map(string filename);
	~Map();
	uint32_t getWidth() { return width_; }
	uint32_t getHeight() { return height_; }
	void loadBinary(const string &filename);
	std::string jsonify(const bool padZeros);
};
