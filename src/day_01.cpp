#include <array>
#include <iostream>
#include <numeric>

#include "jc_file.hpp"

int main()
{
    jc::File file{"day_01.txt"};

    auto global_maximum = 0;
    std::array<int, 3> top_three{0, 0, 0};

    auto elf_total = 0;
    for (auto& line: file)
    {
        // As long as the line is not empty, we keep adding to the current elf's calories
        if (line.length())
        {
            elf_total += std::stoi(line.str());
        }
        // When we find a newline, we have all the calories for the current elf
        else
        {
            global_maximum = std::max(global_maximum, elf_total);

            // The order of the top three doesn't matter. As soon as we find one that's
            // smaller, we just overwrite that one
            for (auto& entry: top_three)
            {
                if (elf_total > entry)
                {
                    entry = elf_total;
                    break;
                }
            }

            // Reset the total to start gatherig data for the next elf
            elf_total = 0;
        }
    }

    std::cout << "Single max:\t" << global_maximum << "\n";
    std::cout << "Multi max:\t" << std::accumulate(std::begin(top_three), std::end(top_three), 0)
              << "\n";
}