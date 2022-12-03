#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

#include "jc_file.hpp"

namespace
{
    const auto LOSE = 0;
    const auto DRAW = 3;
    const auto WIN  = 6;
} // namespace

int main()
{
    jc::File file("day_02.txt");

    int first_score  = 0;
    int second_score = 0;

    for (const auto& line: file)
    {
        const auto lhs = line.str().at(0);
        const auto rhs = line.str().at(2);

        first_score += (1 + rhs - 'X');

        // A X Rock     1
        // B Y Paper    2
        // C Z Scissors 3

        switch (lhs)
        {
        case 'A': // Rock
            first_score += (rhs == 'X' ? DRAW : (rhs == 'Y' ? WIN : LOSE));
            break;
        case 'B': // Paper
            first_score += (rhs == 'X' ? LOSE : (rhs == 'Y' ? DRAW : WIN));
            break;
        case 'C': // Scissors
            first_score += (rhs == 'X' ? WIN : (rhs == 'Y' ? LOSE : DRAW));
            break;
        }

        switch (rhs)
        {
        case 'X': // Lose
            second_score += 0 + (lhs == 'A' ? 3 : (lhs == 'B' ? 1 : 2));
            break;
        case 'Y': // Draw
            second_score += 3 + (lhs == 'A' ? 1 : (lhs == 'B' ? 2 : 3));
            break;
        case 'Z': // Win
            second_score += 6 + (lhs == 'A' ? 2 : (lhs == 'B' ? 3 : 1));
            break;
        }
    }

    std::cout << "My first score: " << first_score << "\n";
    std::cout << "My second score: " << second_score << "\n";
}