#include <sstream>
#include <string>
#include <vector>

#include "jc.hpp"

int main()
{
    jc::File file{"day_05.txt"};

    bool in_header = true;

    std::vector<std::string> stacks_9000(9);
    std::vector<std::string> stacks_9001(9);

    for (auto& line: file)
    {
        if (in_header)
        {
            if (line.str().empty())
            {
                in_header   = false;
                stacks_9001 = stacks_9000;
            }

            for (auto i = 1, n = 0; i < line.str().length(); i += 4, ++n)
            {
                const auto character = line.str().at(i);

                if (!std::isdigit(character) && character != ' ')
                    stacks_9000.at(n).insert(0, 1, character);
            }
        }
        else
        {
            const auto tokens = jc::split(line.str(), " ");

            const auto count = jc::to<int>(tokens[1]);
            const auto src   = jc::to<int>(tokens[3]) - 1;
            const auto dst   = jc::to<int>(tokens[5]) - 1;

            // Move one by one for the 9000
            for (auto i = 0; i < count; ++i)
            {
                auto& src_9000 = stacks_9000.at(src);
                auto& dst_9000 = stacks_9000.at(dst);

                dst_9000.push_back(src_9000.back());
                src_9000.pop_back();
            }

            // Move in bulk for the 9001
            auto& src_stack = stacks_9001.at(src);
            auto& dst_stack = stacks_9001.at(dst);
            std::move(src_stack.end() - count, src_stack.end(), std::back_inserter(dst_stack));
            src_stack.erase(src_stack.end() - count, src_stack.end());
        }
    }

    std::string mover_9000;
    std::ranges::transform(stacks_9000, std::back_inserter(mover_9000),
                           [](const auto& v) { return v.back(); });

    std::cout << "CrateMover 9000: " << mover_9000 << "\n";

    std::string mover_9001;
    std::ranges::transform(stacks_9001, std::back_inserter(mover_9001),
                           [](const auto& v) { return v.back(); });

    std::cout << "CrateMover 9001: " << mover_9001 << "\n";

    auto check = jc::Check{};

    check.add(mover_9000 == "RFFFWBPNS");
    check.add(mover_9001 == "CQQBBJFCS");

    return check.returnValue();
}
