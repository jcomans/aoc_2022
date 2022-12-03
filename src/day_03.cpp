#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include <cassert>

#include "jc_file.hpp"

using Set = std::set<char>;

auto to_priority(char element)
{
    return std::islower(element) ? (1 + element - 'a') : (27 + element - 'A');
}

template <typename T>
auto create_set(T& container)
{
    return Set{std::begin(container), std::end(container)};
}

template <typename T>
int badge_total_addition(const T& data)
{
    static auto count = 0;
    static auto accum = Set{};

    count++;

    Set res;
    switch (count)
    {
    case 1: accum = data; return 0;
    case 2:
        std::ranges::set_intersection(accum, data, std::inserter(res, res.end()));
        accum = res;
        return 0;
    case 3:
        std::ranges::set_intersection(accum, data, std::inserter(res, res.end()));
        count = 0;
        accum.clear();
        return to_priority(*res.begin());
    }
    return 0;
}

int main()
{
    jc::File file{"day_03.txt"};

    auto total       = 0;
    auto badge_total = 0;

    for (const auto& line: file)
    {
        const auto compartment_size = line.length() / 2;

        auto front_compartement = line.str().substr(0, compartment_size);
        auto back_compartement  = line.str().substr(compartment_size);

        auto front_set = create_set(front_compartement);
        auto back_set  = create_set(back_compartement);
        auto full_set  = create_set(line.str());

        Set result;
        std::ranges::set_intersection(front_set, back_set, std::inserter(result, result.end()));

        assert(result.size() == 1);
        total += to_priority(*result.begin());

        badge_total += badge_total_addition(full_set);
    }

    std::cout << "Total:\t\t" << total << "\n";
    std::cout << "Badge total:\t" << badge_total << "\n";
}
