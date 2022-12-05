#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>

#include <cassert>

#include "jc_file.hpp"

auto split(std::string_view data, char split_token)
{
    const auto idx = data.find(split_token);
    assert(idx != data.npos);

    const auto left  = data.substr(0, idx);
    const auto right = data.substr(idx + 1);

    return std::make_pair(left, right);
}


int main()
{
    jc::File file{"day_04.txt"};
    //jc::File file{"tmp.txt"};

    auto contained = 0;
    auto overlap   = 0;

    for (const auto& line: file)
    {

        const auto [elf1, elf2] = split(line.str(), ',');

        const auto [l1s, u1s] = split(elf1, '-');
        const auto [l2s, u2s] = split(elf2, '-');

        const auto l1 = std::stoi(std::string(l1s));
        const auto l2 = std::stoi(std::string(l2s));
        const auto u1 = std::stoi(std::string(u1s));
        const auto u2 = std::stoi(std::string(u2s));
        
        const auto low1 = (l1 <= l2) ? l1 : l2;
        const auto low2 = (l1 <= l2) ? l2 : l1;
        const auto up1  = (l1 <= l2) ? u1 : u2;
        const auto up2  = (l1 <= l2) ? u2 : u1;

        std::cout << line.str() << " ";


        if ((low1 >= low2 && up1 <= up2) || (low2 >= low1 && up2 <= up1))
        {
            contained++;
            overlap++;
            std::cout << " * +";
        }
        else if (up1 >= low2 && up1 <= up2)
        {
            overlap++;
            std::cout << " +";
        }
        std::cout << "\n";

    }

    std::cout << "Contained:\t" << contained << "\n";
    std::cout << "Overlap:\t" << overlap << "\n"; // 417 too low
}
