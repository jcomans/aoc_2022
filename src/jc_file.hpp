#ifndef JC_FILE
#define JC_FILE

#include <fstream>
#include <iterator>
#include <string>

namespace jc
{
    /// A class that can read a full line from an input stream
    class Line
    {
      public:
        friend std::istream& operator>>(std::istream& is, Line& line)
        {
            return std::getline(is, line.data_);
        }

        auto length() const { return data_.length(); }
        const auto& str() const { return data_; }

      private:
        std::string data_;
    };

    /// A simple file read wrapper targetted at reading files line by line
    class File
    {
      public:
        File(const char* file_name) : file_{std::ifstream(file_name)} {}

        std::istream_iterator<Line> begin() { return std::istream_iterator<Line>(file_); }

        std::istream_iterator<Line> end() { return std::istream_iterator<Line>(); }

        bool stripLine()
        {
            std::string line;
            if (std::getline(file_, line))
                return true;

            return false;
        }

        std::string getLine()
        {
            std::string line;
            std::getline(file_, line);
            return line;
        }

      private:
        std::ifstream file_;
    };
} // namespace jc

#endif // !JC_FILE
