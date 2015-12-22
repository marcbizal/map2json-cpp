#include "Map.h"
// UTILITY FUNCTIONS

std::string padWithZeros(const unsigned int numZeros, const std::string &original)
{
	return std::string(numZeros - original.length(), '0').append(original);
}

// CLASS IMPLEMENTATION

Map::Map()
{
}

Map::Map(string filename) : Map()
{
	loadBinary(filename);
}

Map::~Map()
{

}

void Map::loadBinary(const string &filename)
{
	std::ifstream* map_file = new std::ifstream(filename, std::ios::in | std::ios::binary);
	if (map_file->is_open())
	{
		// Read the header of the map file.
		MAP_HEADER header;
		map_file->read((char*)&header, sizeof(MAP_HEADER));
		width_ = header.width; height_ = header.height;

		tile_.resize(height_);
		for (auto &row : tile_)
		{
			row.resize(width_);
		}

		std::cout	<< "Loaded \"" << filename.c_str() << "\":"
					<< "\nwidth: " << header.width
					<< "\nheight: " << header.height
					<< "\nchunk size: " << header.chunkSize
					<< "\n\n";

		// Loop through the file reading two bytes at a time.
		uint16_t currentBlock;
		for (int y = 0; y < header.height; y++)
		{
			for (int x = 0; x < header.width; x++)
			{
				map_file->read((char*)&currentBlock, sizeof(uint16_t));

				// In some of the game files ground is actually soil...
				if (currentBlock == 5 && FIX_SOIL) currentBlock = 0;

				tile_[y][x] = currentBlock;
			}
		}
	}
	else
	{
		std::cerr << "Can't open input file " << filename.c_str() << "!" << std::endl;
	}

	map_file->close();
}

std::string Map::jsonify(const bool padZeros = false)
{
	std::string json = "";

	json += "[\n";
	for (int y = 0; y < height_; y++)
	{
		json += "\t[";

		for (int x = 0; x < width_; x++)
		{
			json += (padZeros ? padWithZeros(2, std::to_string(tile_[y][x])) : std::to_string(tile_[y][x]));
			if (x + 1 != width_) json += ", ";
		}
		json += "],\n";
	}
	json += "]";

	return json;
}
