// ErrorTree.cpp
// niaz hussain
// log-file compressor & analyzer
// cst 202 – data structures

#include "ErrorTree.h"
#include <algorithm>

ErrorTree::ErrorTree() : root(nullptr) {}
ErrorTree::~ErrorTree() { deleteTree(root); }

void ErrorTree::deleteTree(ErrorNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void ErrorTree::insertRec(ErrorNode*& node, const std::string& msg) {
    if (!node) {
        node = new ErrorNode(msg);
        return;
    }
    if (msg == node->msg) {
        node->count++;
    }
    else if (msg < node->msg) {
        insertRec(node->left, msg);
    }
    else {
        insertRec(node->right, msg);
    }
}

void ErrorTree::insert(const std::string& msg) {
    insertRec(root, msg);
}

void ErrorTree::collect(ErrorNode* node, std::vector<ErrorNode*>& out) {
    if (!node) return;
    collect(node->left, out);
    out.push_back(node);
    collect(node->right, out);
}

std::vector<std::pair<std::string, int>> ErrorTree::getTopErrors(int topN) {
    std::vector<ErrorNode*> nodes;
    collect(root, nodes);

    // build pairs and sort by count descending
    std::vector<std::pair<std::string, int>> pairs;
    for (auto n : nodes) {
        pairs.emplace_back(n->msg, n->count);
    }
    std::sort(pairs.begin(), pairs.end(),
        [](auto& a, auto& b) { return a.second > b.second; });

    if ((int)pairs.size() > topN) pairs.resize(topN);
    return pairs;
}
