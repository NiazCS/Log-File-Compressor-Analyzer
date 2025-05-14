// Huffman.cpp

#include "Huffman.h"
#include <queue>
#include <vector>
#include <iostream>

// min-heap by frequency
struct CompareH {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};

HuffmanTree::HuffmanTree() : root(nullptr) {}
HuffmanTree::~HuffmanTree() { deleteTree(root); }

// post-order delete
void HuffmanTree::deleteTree(HuffNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// traverse to build codes: left=0, right=1
void HuffmanTree::buildCodes(HuffNode* node, const std::string& prefix) {
    if (!node) return;
    if (!node->left && !node->right) {
        // leaf: record code (use "0" if single char)
        codes[node->ch] = prefix.empty() ? "0" : prefix;
    }
    buildCodes(node->left, prefix + '0');
    buildCodes(node->right, prefix + '1');
}

void HuffmanTree::build(const std::string& text) {
    // 1) count frequencies
    std::unordered_map<char, int> freqMap;
    for (char c : text) freqMap[c]++;

    // 2) create a leaf for each unique char
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, CompareH> pq;
    for (auto& kv : freqMap) {
        pq.push(new HuffNode(kv.first, kv.second));
    }

    // 3) special-case single-char input
    if (pq.size() == 1) {
        HuffNode* only = pq.top(); pq.pop();
        root = new HuffNode('$', only->freq);
        root->left = only;
    }
    else {
        // 4) build internal nodes until one root remains
        while (pq.size() > 1) {
            HuffNode* a = pq.top(); pq.pop();
            HuffNode* b = pq.top(); pq.pop();
            HuffNode* parent = new HuffNode('$', a->freq + b->freq);
            parent->left = a;
            parent->right = b;
            pq.push(parent);
        }
        root = pq.top(); pq.pop();
    }

    // 5) walk tree to assign codes
    buildCodes(root, "");
}

std::string HuffmanTree::encode(const std::string& text) const {
    std::string out;
    for (char c : text) {
        out += codes.at(c);
    }
    return out;
}

void HuffmanTree::printCodes() const {
    std::cout << "char : code\n";
    for (auto& kv : codes) {
        std::cout << "'" << kv.first << "' : " << kv.second << "\n";
    }
}
