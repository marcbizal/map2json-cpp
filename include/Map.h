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
		unsigned long chunkSize;
		unsigned long width;
		unsigned long height;
	};

	vector<vector<unsigned int>> tile_;
	unsigned int width_; unsigned int height_;
	string json_;

	void jsonify();
public:
	Map();
	Map(string filename);
	~Map();
	unsigned int getWidth() { return width_; }
	unsigned int getHeight() { return height_; }
	void loadBinary(const string &filename);
	std::string& getJSON();
};

