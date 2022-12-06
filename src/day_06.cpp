
#include <iostream>
#include <set>
#include <string_view>

#include "jc_file.hpp"

int main()
{
     jc::File file{"day_06.txt"};
    //const auto file = {"mjqjpqmgbljsphdztnvjfqwrcgsmlb", "bvwbjplbgvbhsrlpgdmjqwftvncz",
    //                   "nppdvjthqldpwncqszvftbrmjlhg", "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
    //                   "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"};



    for (auto& line: file)
    {
        // As long as the line is not empty, we keep adding to the current elf's calories

        const auto data = std::string_view{line.str()};

            auto packet_found = false;
        auto msg_found    = false;

        for (auto i = 0; i < data.length() - 4; ++i)
        {
            const auto packetstr = data.substr(i, 4);
            const auto packetset = std::set(std::begin(packetstr), std::end(packetstr));
            if (packetset.size() == 4 && !packet_found)
            {
                std::cout << "Packet Position: " << i + 4 << "\n";
                packet_found = true;
            }

            if (i < data.length() - 14 && !msg_found)
            {
                const auto msgstr = data.substr(i, 14);
                const auto msgset = std::set(std::begin(msgstr), std::end(msgstr));
                if (msgset.size() == 14)
                {
                    std::cout << "Message Position: " << i + 14 << "\n";
                    msg_found = true;
                }
            }

            if (msg_found && packet_found)
                break;
        }
    }
}