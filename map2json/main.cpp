#include <string>
#include "Writer.h"
#include "Map.h"

using namespace std;

int main(int argc, char* argv[])
{
	Writer jsonWriter("Level05");
	jsonWriter.save();

	system("pause");
	return 0;
}