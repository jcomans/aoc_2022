#ifndef JC_STRING_HPP
#define JC_STRING_HPP

#include <cassert>

#include <charconv>
#include <string_view>

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
} // namespace jc

#endif // !JC_STRING_HPP
