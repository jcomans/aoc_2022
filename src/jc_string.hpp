#ifndef JC_STRING_HPP
#define JC_STRING_HPP

#include <cassert>

#include <charconv>
#include <string_view>
#include <vector>

namespace jc
{
    template <typename T>
    T to(std::string_view input)
    {
        T val;

        const auto res = std::from_chars(input.data(), input.data() + input.size(), val);

        assert(res.ec == std::errc{});

        return val;
    }

    using split_t = std::vector<std::string_view>;
    inline split_t split(std::string_view input, std::string_view delim)
    {
        split_t result;

        auto search_start = size_t{0};
        auto next_split   = input.find(delim, search_start);

        while (next_split != input.npos)
        {
            result.emplace_back(input.substr(search_start, next_split-search_start));

            search_start = next_split + delim.length();

            next_split = input.find(delim, search_start);
        }

        result.emplace_back(input.substr(search_start));

        return result;
    }
} // namespace jc

#endif // !JC_STRING_HPP
