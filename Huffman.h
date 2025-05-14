// Huffman.h

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>

// node in the huffman tree
struct HuffNode {
    char ch;           // character (for leaves)
    int  freq;         // frequency
    HuffNode* left;    // 0?branch
    HuffNode* right;   // 1?branch

    HuffNode(char c, int f)
        : ch(c), freq(f), left(nullptr), right(nullptr) {
    }
};

// builds codes and encodes text
class HuffmanTree {
private:
    HuffNode* root;                               // tree root
    std::unordered_map<char, std::string> codes;  // char->binary code

    void deleteTree(HuffNode* node);              // free nodes
    void buildCodes(HuffNode* node, const std::string& prefix); // fill codes

public:
    HuffmanTree();
    ~HuffmanTree();

    void build(const std::string& text);          // build from input text
    std::string encode(const std::string& text) const; // encode to bits
    void printCodes() const;                      // optional: print code table
};

#endif
