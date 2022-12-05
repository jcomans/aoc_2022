#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "jc_file.hpp"

int main()
{
    jc::File file{"day_05.txt"};

    bool in_header = true;

    std::vector<std::deque<char>> stacks(9);
    std::vector<std::deque<char>> stacks_2(9);

    for (auto& line: file)
    {
        if (in_header)
        {
            if (line.str().empty())
            {
                in_header = false;
                stacks_2  = stacks;
            }
                

            for (auto i = 1, n = 0; i < line.str().length(); i += 4, ++n)
            {
                const auto character = line.str().at(i);

                if (!std::isdigit(character) && character != ' ')
                    stacks.at(n).push_front(character);
            }
        }
        else
        {
            std::stringstream ss(line.str());
            std::string dummy1, dummy2, dummy3;
            int count, src, dst;
            ss >> dummy1 >> count >> dummy2 >> src >> dummy3 >> dst;
            std::cout << count << "\t" << src << "->" << dst << "\n";

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
    }
    
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