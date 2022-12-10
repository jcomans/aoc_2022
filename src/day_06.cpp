
#include <iostream>
#include <set>
#include <string_view>

#include "jc.hpp"

int main()
{
    jc::File file{"day_06.txt"};

    auto packet_position = 0;
    auto message_postion = 0;

    for (auto& line: file)
    {
        const auto data = std::string_view{line.str()};

        auto packet_found = false;
        auto msg_found    = false;

        for (auto i = 0; i < data.length() - 4; ++i)
        {
            const auto packetstr = data.substr(i, 4);
            const auto packetset = std::set(std::begin(packetstr), std::end(packetstr));
            if (packetset.size() == 4 && !packet_found)
            {
                packet_position = i + 4;
                packet_found    = true;
            }

            if (i < data.length() - 14 && !msg_found)
            {
                const auto msgstr = data.substr(i, 14);
                const auto msgset = std::set(std::begin(msgstr), std::end(msgstr));
                if (msgset.size() == 14)
                {
                    message_postion = i + 14;
                    msg_found       = true;
                }
            }

            if (msg_found && packet_found)
                break;
        }
    }

    std::cout << "Packet Position: " << packet_position << "\n";
    std::cout << "Message Position: " << message_postion << "\n";

    auto check = jc::Check{};

    check.add(packet_position == 1850);
    check.add(message_postion == 2823);

    return check.returnValue();
}
