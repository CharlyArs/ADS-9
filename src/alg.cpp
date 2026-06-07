// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdint>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& in) {
    std::vector<char> sorted_in = in;
    std::sort(sorted_in.begin(), sorted_in.end());
    root = new Node('\0');
    buildTree(root, sorted_in);
}

PMTree::~PMTree() {
    delete root;
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;

    for (size_t i = 0; i < remaining.size(); ++i) {
        Node* child = new Node(remaining[i]);
        node->children.push_back(child);

        std::vector<char> next_remaining = remaining;
        next_remaining.erase(next_remaining.begin() + i);

        buildTree(child, next_remaining);
    }
}

static void collectPerms(Node* node,
                         std::vector<char>& current,
                         std::vector<std::vector<char>>& result) {
    if (!node) return;

    if (node->value != '\0') {
        current.push_back(node->value);
    }

    if (node->children.empty()) {
        if (!current.empty()) {
            result.push_back(current);
        }
    } else {
        for (Node* child : node->children) {
            collectPerms(child, current, result);
        }
    }

    if (node->value != '\0') {
        current.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    collectPerms(tree.root, current, result);
    return result;
}

static int64_t factorial(int n) {
    int64_t res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    if (num < 1 || num > static_cast<int>(perms.size())) {
        return {};
    }
    return perms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    if (!tree.root || tree.root->children.empty()) return {};

    int n = tree.root->children.size();
    int64_t total = factorial(n);

    if (num < 1 || num > total) return {};

    std::vector<char> result;
    Node* current = tree.root;

    while (!current->children.empty()) {
        int c = current->children.size();
        int64_t count_per_child = factorial(c - 1);

        int idx = (num - 1) / count_per_child;
        if (idx >= c) return {};

        current = current->children[idx];
        result.push_back(current->value);

        num = num - idx * count_per_child;
    }

    return result;
}
