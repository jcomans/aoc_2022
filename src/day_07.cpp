#include "jc.hpp"

#include <algorithm>
#include <charconv>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

#include <cassert>

int main()
{
    // auto file = jc::File{"tmp.txt"};
    auto file = jc::File{"day_07.txt"};

    std::vector<std::string> dirstack;
    std::map<std::string, int> folder_sizes;

    for (const auto& l: file)
    {
        const auto line = std::string_view{l.str()};

        if (line.substr(0, 1) == "$")
        {
            if (line.substr(2, 2) == "cd")
            {
                if (line.substr(5, 2) == "..")
                {
                    assert(dirstack.size());
                    dirstack.pop_back();
                }
                else
                {
                    const auto dir = line.substr(5);
                    dirstack.emplace_back(dir);
                }
            }
        }
        else
        {
            if (line.substr(0, 3) != "dir")
            {
                const auto space_pos = line.find(" ");
                assert(space_pos != line.npos);
                const auto size_str = line.substr(0, space_pos);
                int filesize;
                std::from_chars(size_str.data(), size_str.data() + size_str.size(), filesize);

                std::string fulldir;
                for (const auto& dir: dirstack)
                {
                    fulldir += std::string(dir) + "/";
                    folder_sizes[fulldir] += filesize;
                }
            }
        }
    }

    std::vector<int> sizes;

    std::ranges::transform(folder_sizes, std::back_inserter(sizes),
                           [](const auto& e) { return e.second; });

    auto total_size =
        std::accumulate(std::begin(sizes), std::end(sizes), 0,
                        [](auto sum, auto val) { return (val <= 100000) ? sum + val : sum; });

    std::cout << "Total size: " << total_size << "\n";

    const auto root_size     = folder_sizes["//"];
    const auto free_size     = 70000000 - root_size;
    const auto required_size = 30000000 - free_size;

    std::ranges::sort(sizes);

    const auto elem = std::find_if(sizes.begin(), sizes.end(),
                                   [required_size](auto val) { return val >= required_size; });

    std::cout << "Removal dir size: " << *elem << "\n";

    auto check = jc::Check{};

    check.add(total_size == 1423358);
    check.add(*elem == 545729);

    return check.returnValue();
}
