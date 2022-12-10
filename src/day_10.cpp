#include "jc.hpp"

#include "jc_file.hpp"
#include "jc_string.hpp"

#include <cassert>

#include <iostream>

class CPU
{
  public:
    CPU() : cycle_{1}, reg_x_{1}, strength_{0} {}

    void step(std::string_view cmd, std::string_view arg)
    {
        if (cmd == "noop")
        {
            increase_PC();
        }
        else if (cmd == "addx")
        {
            increase_PC();
            increase_PC();
            reg_x_ += jc::to<int>(arg);
        }
    }

    int strength() const { return strength_; }
    const std::string& screen() const { return screen_; }

  private:
    void draw_pixel()
    {
        const auto pos    = (cycle_ - 1) % 40;
        const auto sp_pos = reg_x_ - 1;

        if (cycle_ > 1 && pos == 0)
            screen_ += "\n";

        if (pos >= sp_pos && pos < sp_pos + 3)
            screen_ += "#";
        else
            screen_ += ".";
    }
    void increase_PC()
    {
        if ((cycle_ + 20) % 40 == 0)
            strength_ += cycle_ * reg_x_;

        draw_pixel();

        ++cycle_;
    }

    int cycle_;
    int reg_x_;

    int strength_;

    std::string screen_;
};

int main()
{
    auto file = jc::File{"day_10.txt"};

    auto cpu = CPU{};

    for (const auto& l: file)
    {
        const auto line = std::string_view{l.str()};

        const auto cmd = line.substr(0, 4);
        const auto arg = line.size() > 5 ? line.substr(5) : std::string_view{};

        cpu.step(cmd, arg);
    }

    std::cout << "Strength: " << cpu.strength() << "\n";
    std::cout << cpu.screen() << "\n";


    auto check = jc::Check{};

    check.add(cpu.strength() == 13860);
    check.add(cpu.screen() == R"(###..####.#..#.####..##....##..##..###..
#..#....#.#..#.#....#..#....#.#..#.#..#.
#..#...#..####.###..#.......#.#....###..
###...#...#..#.#....#.##....#.#....#..#.
#.#..#....#..#.#....#..#.#..#.#..#.#..#.
#..#.####.#..#.#.....###..##...##..###..)");

    return check.returnValue();
}
