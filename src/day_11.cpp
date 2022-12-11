#include "jc.hpp"

#include <algorithm>
#include <array>
#include <numeric>
#include <vector>

class Monkey;

using MonkeyList = std::vector<Monkey>;

const auto max_rounds = 10000;

class Monkey
{
  public:
    Monkey(const jc::split_t& si, const jc::split_t& op, int test, size_t ta, size_t fa,
           MonkeyList& ml)
        : operation_(op[0].at(0))
        , operand_{op[1] == "old" ? -1000 : jc::to<int>(op[1])}
        , test_{test}
        , true_target_{ta}
        , false_target_{fa}
        , monkey_list_{ml}
        , activity_count_{0}
    {
        std::ranges::transform(si, std::back_inserter(items_),
                               [](auto v) { return jc::to<size_t>(v); });
    }

    void process(int modulo = 0)
    {
        for (auto& item: items_)
        {
            ++activity_count_;

            item = modulo > 0 ? apply_operation(item) % modulo : apply_operation(item) / 3;

            const auto condition = (item % test_) == 0;

            const auto target = condition ? true_target_ : false_target_;

            monkey_list_.at(target).throwItem(item);
        }
        items_.clear();
    }

    void throwItem(size_t item) { items_.push_back(item); }

    int activity() const { return activity_count_; }

  private:
    size_t apply_operation(size_t item)
    {
        if (operation_ == '+')
        {
            return item + operand_;
        }
        else
        {
            return (operand_ == -1000) ? item * item : item * operand_;
        }
    }

    std::vector<size_t> items_;

    char operation_;
    int operand_;
    int test_;
    size_t true_target_;
    size_t false_target_;

    MonkeyList& monkey_list_;

    int activity_count_;
};

template <typename T, size_t N>
class MultiMax
{
  public:
    MultiMax(T initval = T{}) { std::ranges::fill(data_, initval); }

    void add(T val)
    {
        for (auto& max_entry: data_)
        {
            if (val > max_entry)
                std::swap(val, max_entry);
        }
    }

    T operator[](size_t idx) const { return data_.at(idx); }

  private:
    std::array<T, N> data_;
};

int main()
{
    auto file = jc::File{"day_11.txt"};

    MonkeyList monkey_list;
    MonkeyList monkey_list_2;

    auto modulo = 1;

    do {
        std::array<std::string, 6> lines;
        for (auto& entry: lines) entry = file.getLine();

        const auto sisv = lines.at(1).substr(18);
        const auto opsv = lines.at(2).substr(23);

        const auto start_items  = jc::split(sisv, ", ");
        const auto operation    = jc::split(opsv, " ");
        const auto test         = jc::to<int>(lines.at(3).substr(21));
        const auto true_action  = jc::to<size_t>(lines.at(4).substr(29));
        const auto false_action = jc::to<size_t>(lines.at(5).substr(30));

        modulo = std::lcm(modulo, test);

        monkey_list.emplace_back(start_items, operation, test, true_action, false_action,
                                 monkey_list);

        monkey_list_2.emplace_back(start_items, operation, test, true_action, false_action,
                                   monkey_list_2);

    } while (file.stripLine());

    for (auto i = 0; i < max_rounds; ++i)
    {
        if (i < 20)
            for (auto& monkey: monkey_list) { monkey.process(); }

        for (auto& monkey: monkey_list_2) { monkey.process(modulo); }
    }

    MultiMax<size_t, 2> max;
    for (const auto& monkey: monkey_list) { max.add(monkey.activity()); }

    const auto result = max[0] * max[1];

    std::cout << "\nMax: " << result << "\n";

    MultiMax<size_t, 2> max_2;
    for (const auto& monkey: monkey_list_2) { max_2.add(monkey.activity()); }

    const auto result_2 = max_2[0] * max_2[1];

    std::cout << "\nMax: " << result_2 << "\n";

    auto check = jc::Check{};

    check.add(result == 56350);
    check.add(result_2 == 13954061248);

    return check.returnValue();
}