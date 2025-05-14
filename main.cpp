// main.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Huffman.h"
#include "ErrorTree.h"

int main() {
    // 1) read log file
    std::cout << "enter log filename: ";
    std::string fname;
    std::getline(std::cin, fname);
    std::ifstream in(fname);
    if (!in.is_open()) {
        std::cerr << "cannot open " << fname << "\n";
        return 1;
    }

    // read lines & build full text
    std::string line, text;
    std::vector<std::string> lines;
    while (std::getline(in, line)) {
        lines.push_back(line);
        text += line + "\n";
    }
    in.close();

    // 2) compress via Huffman
    HuffmanTree ht;
    ht.build(text);
    std::string bits = ht.encode(text);
    std::ofstream comp("compressed.txt");
    comp << bits;
    comp.close();
    std::cout << "compressed output written to compressed.txt\n";

    // optional: show codes
    // ht.printCodes();

    // 3) error analysis (lines containing "ERROR")
    ErrorTree et;
    for (auto& l : lines) {
        if (l.find("ERROR") != std::string::npos) {
            et.insert(l);
        }
    }

    // 4) top 10 errors
    auto top = et.getTopErrors(10);
    std::ofstream report("error_report.txt");
    report << "top error messages:\n";
    std::cout << "\ntop error messages:\n";
    for (auto& p : top) {
        report << p.first << " (" << p.second << " times)\n";
        std::cout << p.first << " (" << p.second << " times)\n";
    }
    report.close();

    std::cout << "\nanalysis complete.\n";
    return 0;
}
