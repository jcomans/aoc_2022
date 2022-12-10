#include <algorithm>
#include <iostream>
#include <set>
#include <span>
#include <vector>

#include <cassert>

#include "jc.hpp"

using Set = std::set<char>;

auto to_priority(char element)
{
    return std::islower(element) ? (1 + element - 'a') : (27 + element - 'A');
}

auto create_set(auto span) { return Set{std::begin(span), std::end(span)}; }

auto set_intersection(auto set1, auto set2)
{
    Set result;
    std::ranges::set_intersection(set1, set2, std::inserter(result, result.end()));
    return result;
}

auto badge_total_addition(auto data)
{
    static auto count = 0;
    static auto intersection = Set{};

    // There's no intersection to be calculated for the first line in each group of three
    intersection = intersection.size() ? set_intersection(intersection, data) : data;
    count++;

    // When we are at the third line, the intersection should be a single element and we can return
    // its priority
    if (count == 3)
    {
        count = 0;

        assert(intersection.size() == 1);
        const auto value = *intersection.begin();
        intersection.clear();

        return to_priority(value);
    }

    return 0;
}

auto total_addition(auto front, auto back)
{
    Set result;
    std::ranges::set_intersection(front, back, std::inserter(result, result.end()));

    assert(result.size() == 1);

    return to_priority(*result.begin());
}

int main()
{
    jc::File file{"day_03.txt"};

    auto total       = 0;
    auto badge_total = 0;

    for (const auto& line: file)
    {
        const auto full_contents    = std::span(line.str());
        const auto compartment_size = full_contents.size() / 2;

        const auto front_set = create_set(full_contents.subspan(0, compartment_size));
        const auto back_set  = create_set(full_contents.subspan(compartment_size));
        const auto full_set  = create_set(full_contents);

        total += total_addition(front_set, back_set);
        badge_total += badge_total_addition(full_set);
    }

    std::cout << "Total:\t\t" << total << "\n";
    std::cout << "Badge total:\t" << badge_total << "\n";

    auto check = jc::Check{};

    check.add(total == 7990);
    check.add(badge_total == 2602);

    return check.returnValue();
}
