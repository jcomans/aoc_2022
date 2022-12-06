#include <charconv>
#include <chrono>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "jc_file.hpp"

int main()
{
    //jc::File file{"day_05.txt"};
    jc::File file{"aoc_2022_day05_large_input.txt"};

    bool in_header = true;

    //std::vector<std::deque<char>> stacks(9);
    //std::vector<std::deque<char>> stacks_2(9);

    std::vector<std::vector<char>> stacks(9);
    std::vector<std::vector<char>> stacks_2(9);

    std::cout << "Reading stacks" << std::endl;

    const auto start_time = std::chrono::high_resolution_clock::now();
    auto counter = 0;
    for (auto& line: file)
    {
        if (in_header)
        {
            if (line.str().empty())
            {
                in_header = false;
                stacks_2  = stacks;
                std::cout << "\nStarting command parsing" << std::endl;
            }
                

            for (auto i = 1, n = 0; i < line.str().length(); i += 4, ++n)
            {
                const auto character = line.str().at(i);

                if (!std::isdigit(character) && character != ' ')
                    stacks.at(n).insert(stacks.at(n).begin(), character);
            }
        }
        else
        {
            const auto cmd = std::string_view(line.str());
            int count, src, dst;

            const auto start_cnt = 5;
            const auto end_cnt   = cmd.find(' ', start_cnt);
            std::from_chars(&cmd.data()[start_cnt], &cmd.data()[end_cnt], count);

            const auto start_src = cmd.find(' ', end_cnt + 1) + 1;
            const auto end_src   = cmd.find(' ', start_src);
            std::from_chars(&cmd.data()[start_src], &cmd.data()[end_src], src);

            const auto start_dst = cmd.find(' ', end_src + 1) + 1;
            const auto end_dst   = cmd.find(' ', start_dst);
            std::from_chars(&cmd.data()[start_dst], &cmd.data()[end_dst], dst);


            for (auto i = 0; i < count; ++i)
            {
                stacks.at(dst - 1).push_back(stacks.at(src - 1).back());
                stacks.at(src - 1).pop_back();
            }

            auto& src_stack = stacks_2.at(src - 1);
            auto& dst_stack = stacks_2.at(dst - 1);
            std::move(src_stack.end() - count, src_stack.end(), std::back_inserter(dst_stack));
            src_stack.erase(src_stack.end() - count, src_stack.end());
        }

        ++counter;
        if (counter > 1000) {
            std::cout << ".";
            counter = 0;
        }
    }
    std::cout << "\n";
    const auto delta = std::chrono::high_resolution_clock::now() - start_time;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::seconds>(delta).count()
              << " s\n";
    
    std::cout << "CrateMover 9000\n";
    for (const auto& stack: stacks)
    {
        if (stack.size())
            std::cout << stack.back();
    }

    std::cout << "\nCrateMover 9001\n";
    for (const auto& stack: stacks_2)
    {
        if (stack.size())
            std::cout << stack.back();
    }
    std::cout << "\n";
}