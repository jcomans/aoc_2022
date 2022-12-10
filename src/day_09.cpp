#include "jc_file.hpp"
#include "jc_string.hpp"

#include <cassert>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string_view>
#include <vector>

enum class Motion
{
    left,
    right,
    up,
    down
};

struct Point
{
    int x;
    int y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    void move(Motion dir)
    {
        switch (dir)
        {
        case Motion::left: x -= 1; break;
        case Motion::right: x += 1; break;
        case Motion::up: y += 1; break;
        case Motion::down: y -= 1; break;
        }
    }

    void follow(Point head)
    {
        const auto delta = head - *this;

        if (std::abs(delta.x) + std::abs(delta.y) <= 1)
            return;

        if (delta.y == 0)
        {
            x += std::clamp(delta.x, -1, 1);
            return;
        }

        if (delta.x == 0)
        {
            y += std::clamp(delta.y, -1, 1);
            return;
        }

        if (std::abs(delta.x) + std::abs(delta.y) == 2)
            return;

        x += std::clamp(delta.x, -1, 1);
        y += std::clamp(delta.y, -1, 1);
    }

    Point operator-(Point rhs) { return {x - rhs.x, y - rhs.y}; }

    
};

bool operator<(Point lhs, Point rhs) { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }

namespace
{
    const std::map<char, Motion> to_motion{
        {'L', Motion::left}, {'R', Motion::right}, {'U', Motion::up}, {'D', Motion::down}};
}

int main()
{
    auto file = jc::File("day_09.txt");

    auto head  = Point{};
    auto tail  = head;
    auto tails = std::vector<Point>(9, head);

    std::set<Point> tail_visited;
    std::set<Point> long_tail_visited;

    for (const auto& l: file)
    {
        const auto line = std::string_view{l.str()};

        const auto dir     = to_motion.at(line.front());
        const auto repeats = jc::to<int>(line.substr(2));

        for (auto i = 0; i < repeats; ++i)
        {
            head.move(dir);
            tail.follow(head);

            tails.front().follow(head);
            for (auto j = 1; j < tails.size(); ++j) tails.at(j).follow(tails.at(j - 1));

            tail_visited.insert(tail);
            long_tail_visited.insert(tails.back());

        }
    }

    std::cout << "Tail visited: " << tail_visited.size() << "\n";
    std::cout << "Long tail visited: " << long_tail_visited.size() << "\n";

    assert(tail_visited.size() == 6030);
    assert(long_tail_visited.size() == 2545);
}