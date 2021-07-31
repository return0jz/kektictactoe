#pragma once
#include <iostream>
#include <array>
#include <cstdlib>
#include <array>
#include <vector>
#include <unordered_map>
#include <map>

struct Player {
    enum {
        goOn = 0,
        white = 1,
        tie = 2,
        black = 4
    };
};

std::uint8_t isDone(const std::array<std::uint8_t,9> &arr);
double evaluate(const std::array<std::uint8_t,9> &arr, bool turn);
std::vector< std::array<std::uint8_t,9> > generateMoves(const std::array<std::uint8_t,9> &arr, bool turn);
