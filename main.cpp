#include "compiler.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <cstdlib>


#ifdef _WIN32
#include <direct.h>
#define mkdir(dir) _mkdir(dir)
#else
#include <sys/stat.h>
#define mkdir(dir) mkdir(dir, 0755)
#endif


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <command> <arguments>" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "compile") {
        if (argc < 4) {
            std::cerr << "Usage: " << argv[0] << " compile <input_file> <output_file>" << std::endl;
            return 1;
        }
        std::string input_file = argv[2];
        std::string output_file = argv[3];
        std::string input_text;
        std::vector<uint8_t> bytecode;
        std::ifstream input_stream(input_file);
        if (!input_stream) {
            std::cerr << "Failed to open input file: " << input_file << std::endl;
            return 1;
        }
        input_text.assign((std::istreambuf_iterator<char>(input_stream)), std::istreambuf_iterator<char>());
        bytecode = compile(input_text);
        std::ofstream output_stream(output_file, std::ios::binary);
        output_stream.write(reinterpret_cast<const char*>(bytecode.data()), bytecode.size());
    } else if (command == "decompile") {
        if (argc < 4) {
            std::cerr << "Usage: " << argv[0] << " decompile <input_file> <output_file>" << std::endl;
            return 1;
        }
        std::string input_file = argv[2];
        std::string output_file = argv[3];
        std::vector<uint8_t> bytecode;
        std::ifstream input_stream(input_file, std::ios::binary);
        if (!input_stream) {
            std::cerr << "Failed to open input file: " << input_file << std::endl;
            return 1;
        }
        bytecode.assign((std::istreambuf_iterator<char>(input_stream)), std::istreambuf_iterator<char>());
        std::string decompiled_code = decompile(bytecode);
        std::ofstream output_stream(output_file);
        output_stream << decompiled_code;
    } else if (command == "run") {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " run <input_file>" << std::endl;
            return 1;
        }
        std::string input_file = argv[2];
        std::system((std::string(argv[0]) + " compile " + input_file + " main").c_str());
        std::system("chmod +x main");
        std::system("./main");
    } else if (command == "print") {
        if (argc < 4) {
            std::cerr << "Usage: " << argv[0] << " print <text> <output_file>" << std::endl;
            return 1;
        }
        std::string text = argv[2];
        std::string cpp_code = "#include <iostream>\nint main(){std::cout<<R\"(" + text + ")\"<<std::endl;return 0;}";
        mkdir("build");
        std::ofstream cpp_file("build/main.cpp");
        cpp_file << cpp_code;
        cpp_file.close();
        std::system("g++ build/main.cpp -o build/main");
        std::vector<uint8_t> bytecode;
        std::ifstream input_stream("build/main", std::ios::binary);
        bytecode.assign((std::istreambuf_iterator<char>(input_stream)), std::istreambuf_iterator<char>());
        std::string output_file = argv[3];
        std::string output_string = decompile(bytecode);
        std::ofstream output_stream(output_file);
        output_stream << output_string;
    } else if (command == "parse") {
        if (argc < 4) {
            std::cerr << "Usage: " << argv[0] << " parse <input_file> <output_file>" << std::endl;
            return 1;
        }
        std::string input_file = argv[2];
        std::string output_file = argv[3];
        mkdir("build");
        std::system(("g++ " + input_file + " -o build/main").c_str());
        std::vector<uint8_t> bytecode;
        std::ifstream input_stream("build/main", std::ios::binary);
        bytecode.assign((std::istreambuf_iterator<char>(input_stream)), std::istreambuf_iterator<char>());
        std::string output_string = decompile(bytecode);
        std::ofstream output_stream(output_file);
        output_stream << output_string;
    } else if (command == "help") {
        std::cout << "Usage: " << argv[0] << " <command> <arguments>" << std::endl;
        std::cout << "Commands:" << std::endl;
        std::cout << "  compile <input_file> <output_file>   Compile a .sheep file to bytecode" << std::endl;
        std::cout << "  decompile <input_file> <output_file> Decompile bytecode to a .sheep file" << std::endl;
        std::cout << "  run <input_file>                     Compile and run a .sheep file" << std::endl;
        std::cout << "  print <text> <output_file>           Print text to a .sheep file" << std::endl;
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
        return 1;
    }

    return 0;
}
