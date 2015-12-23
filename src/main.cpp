#include "Writer.h"
#include "Map.h"

#include <iostream>
#include <string>
using namespace std;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include "config.h"

int main(int argc, char* argv[])
{
	try {
		po::options_description desc("Usage");
		desc.add_options()
		("help,h", "print help docs")
		("version,v", "print version string")
		("all,a", "attempts to convert all subdirectories of the current directory")
		("input,i", po::value<string>(), "name of legacy map source folder")
		("output,o", po::value<string>(), "name of output json file")
		("pad-zeros,z", "pad output nodes with zeros")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help"))
		{
			cout << desc << endl;
			return 0;
		}

		if (vm.count("version"))
		{
			cout << VERSION << endl;
			return 0;
		}

		bool padZeros = vm.count("pad-zeros");

		Writer* jsonWriter = NULL;
		if (vm.count("all"))
		{
			fs::path working_directory(fs::current_path());
			fs::directory_iterator end_itr;

			for (fs::directory_iterator itr(working_directory); itr != end_itr; ++itr)
			{
				if (fs::is_directory(itr->status()))
				{
					jsonWriter = new Writer(itr->path().filename().string());
					jsonWriter->save(padZeros);
					delete jsonWriter;
				}
			}
		}
		else if (vm.count("input"))
		{
			jsonWriter = new Writer(vm["input"].as<string>());
		}
		else
		{
			cerr << "Input option is required!" << endl;
			cout << desc << endl;
			return 1;
		}

		if (vm.count("output"))
		{
			jsonWriter->saveAs(vm["output"].as<string>(), padZeros);
		}
		else
		{
			jsonWriter->save(padZeros);
		}
		delete jsonWriter;
	}
	catch(exception& e) {
		cerr << "error: " << e.what() << "\n";
		return 1;
	}
	catch(...) {
		cerr << "Exception of unknown type!\n";
	}

	return 0;
}
