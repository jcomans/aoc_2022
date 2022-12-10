#include "jc_file.hpp"

#include <cassert>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using Grid = std::vector<std::vector<int>>;

void scan(const Grid& grid, int rs, int re, int ri, int cs, int ce, int ci, auto pred)
{
    for (auto r = rs; r != re; r += ri)
    {
        for (auto c = cs; c != ce; c += ci) { pred(grid[r][c]); }
    }
}

int is_visible(const Grid& grid, size_t r, size_t c)
{
    const auto grid_size = grid.size();

    if (r == 0 || r == grid_size - 1 || c == 0 || c == grid_size - 1)
        return 1;

    auto visible = true;

    const auto h = grid[r][c];
    auto checker = [h, &visible](auto v)
    {
        if (v >= h)
            visible = false;
    };

    scan(grid, r, r + 1, 1, 0, c, 1, checker);

    if (!visible)
    {
        visible = true;
        scan(grid, r, r + 1, 1, c + 1, grid_size, 1, checker);
    }

    if (!visible)
    {
        visible = true;
        scan(grid, 0, r, 1, c, c + 1, 1, checker);
    }

    if (!visible)
    {
        visible = true;
        scan(grid, r + 1, grid_size, 1, c, c + 1, 1, checker);
    }

    return visible;
}

int get_scenic_score(const Grid& grid, size_t r, size_t c)
{
    const auto grid_size = grid.size();
    if (r == 0 || r == grid_size - 1 || c == 0 || c == grid_size - 1)
        return 0;

    auto score   = 1;
    auto dist    = 0;
    auto stop    = false;
    const auto h = grid[r][c];
    auto checker = [h, &dist, &stop](auto v)
    {
        if (!stop)
        {
            ++dist;
            stop = h <= v;
        }
    };

    dist = 0;
    stop = false;
    scan(grid, r - 1, -1, -1, c, c + 1, 1, checker);
    score *= dist;

    dist = 0;
    stop = false;
    scan(grid, r, r + 1, 1, c - 1, -1, -1, checker);
    score *= dist;

    dist = 0;
    stop = false;
    scan(grid, r, r + 1, 1, c + 1, grid_size, 1, checker);
    score *= dist;

    dist = 0;
    stop = false;
    scan(grid, r + 1, grid_size, 1, c, c + 1, 1, checker);
    score *= dist;

    return score;
}

int main()
{
    auto file = jc::File("day_08.txt");

    Grid grid;

    for (const auto& l: file)
    {
        grid.emplace_back();
        std::ranges::transform(l.str(), std::back_inserter(grid.back()),
                               [](auto v) { return v - '0'; });
    }

    const auto grid_size = grid.size();
    assert(grid_size == grid.front().size());

    auto visible_trees = 0;
    auto max_score     = 0;

    for (auto row = 0; row < grid_size; ++row)
    {
        for (auto column = 0; column < grid_size; ++column)
        {
            visible_trees += is_visible(grid, row, column);
            max_score = std::max(max_score, get_scenic_score(grid, row, column));
        }
    }

    std::cout << "Visible trees: " << visible_trees << "\n";
    std::cout << "Max scenic score: " << max_score << "\n";

    assert(visible_trees == 1560);
    assert(max_score == 252000);
}