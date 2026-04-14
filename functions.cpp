#include <string>
#include <fstream>
#include <iostream>

std::string readFile(std::string file_name) {
    std::string text;
    std::ifstream file(file_name);

    if (file.is_open()) {
        // read all from start to end
        text.assign((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
        file.close();

    } else {
        std::cout << "warning: cannot open " << file_name << " will use default text\n";
        text = "test text RSA :>"; 
    }

    return text;
}