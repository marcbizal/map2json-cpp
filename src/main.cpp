#include "Writer.h"
#include "Map.h"

#include <iostream>
#include <string>
using namespace std;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main(int argc, char* argv[])
{
	try {
		po::options_description desc("Usage");
		desc.add_options()
			("help,h", "print help docs")
			("version,v", "print version string")
			("input,i", po::value<string>(), "name of legacy map source folder")
			("output,o", po::value<string>(), "name of output json file")
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
			cout << "0.0.1" << endl;
			return 0;
		}

		Writer* jsonWriter = NULL;
		if (vm.count("input"))
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
			jsonWriter->saveAs(vm["output"].as<string>());
		}
		else
		{
			jsonWriter->save();
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
