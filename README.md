# map2json-cpp
A command line conversion tool written in C++ to convert binary .map files used in Lego Rock Raiders to a JSON format usable by [Raiders](https://github.com/marcbizal/Raiders). 

*This version of `map2json` is being deprecated in favor of a [NodeJS alternative](https://github.com/marcbizal/map2json).*

## Build Instructions
To build `map2json` on unix systems, please use the following commands:

```bash
git clone https://github.com/marcbizal/map2json-cpp.git
cd map2json-cpp
cmake
make && sudo make install
```

For non-unix systems, generate a build solution using cmake for your preferred toolset (e.g. `cmake -G "Visual Studio 13 Win64"`),
and build the solution. Once built, copy the executable to a folder included in your system PATH.

## Usage
```
-h [ --help ]         print help docs
-v [ --version ]      print version string
-i [ --input ] arg    name of legacy map source folder
-o [ --output ] arg   name of output json file
-p [ --pad-zeros ]    pad output nodes with zeros
```

The `--input` flag is required by `map2json`, to convert a legacy map folder (e.g. `Level05`) to a JSON map file use command `map2json -i Level05`.
If the `--output` flag is not provided `map2json` will generate a file based on the folder name (i.e. `Level05.js`).
The `--pad-zeros` flag can be provided to pad tile values with zeros, this is primarily to add readability when hand modifying the generated files.
