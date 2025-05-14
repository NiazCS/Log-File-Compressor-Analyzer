// ErrorTree.h

#ifndef ERRORTREE_H
#define ERRORTREE_H

#include <string>
#include <vector>
#include <utility>

// node for error-message BST
struct ErrorNode {
    std::string msg;   // full error line
    int count;         // occurrences
    ErrorNode* left;
    ErrorNode* right;
    ErrorNode(const std::string& m)
        : msg(m), count(1), left(nullptr), right(nullptr) {
    }
};

// BST to count frequencies of error lines
class ErrorTree {
private:
    ErrorNode* root;

    void deleteTree(ErrorNode* node);
    void insertRec(ErrorNode*& node, const std::string& msg);
    void collect(ErrorNode* node, std::vector<ErrorNode*>& out);

public:
    ErrorTree();
    ~ErrorTree();

    void insert(const std::string& msg);
    // return top N messages (msg, count) sorted by descending count
    std::vector<std::pair<std::string, int>> getTopErrors(int topN);
};

#endif
