// Copyright 2022 NNTU-CS
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "tree.h"

int64_t getRandomNumber(int64_t min, int64_t max) {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int64_t> dis(min, max);
    return dis(gen);
}

int64_t factorial(int n) {
    int64_t res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

int main() {
    std::cout << std::left << std::setw(5) << "n"
        << std::setw(18) << "getAllPerms (ms)"
        << std::setw(15) << "getPerm1 (ms)"
        << std::setw(15) << "getPerm2 (ms)" << std::endl;
    std::cout << std::string(55, '-') << std::endl;

    for (int n = 1; n <= 10; ++n) {
        std::vector<char> in;
        for (int i = 1; i <= n; ++i) {
            in.push_back('0' + i);
        }

        PMTree tree(in);
        int64_t total_perms = factorial(n);

        int64_t random_num = getRandomNumber(1, total_perms);

        auto start = std::chrono::high_resolution_clock::now();
        auto all_perms = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_all = end - start;

        start = std::chrono::high_resolution_clock::now();
        auto p1 = getPerm1(tree, random_num);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_p1 = end - start;

        start = std::chrono::high_resolution_clock::now();
        auto p2 = getPerm2(tree, random_num);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_p2 = end - start;

        std::cout << std::left << std::setw(5) << n
            << std::setw(18) << t_all.count()
            << std::setw(15) << t_p1.count()
            << std::setw(15) << t_p2.count() << std::endl;
    }

    return 0;
}
