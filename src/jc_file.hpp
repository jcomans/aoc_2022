#ifndef JC_FILE
#define JC_FILE

#include <fstream>
#include <string>

namespace jc
{
    /// <summary>
    /// A class that can read a full line from an input stream
    /// </summary>
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

    /// <summary>
    /// A simple file read wrapper targetted at reading files line by line (in a range based for)
    /// </summary>
    class File
    {
    public:
        File(const char* file_name)
            : file_{ std::ifstream(file_name) }
        {
        }

        std::istream_iterator<Line> begin()
        {
            return std::istream_iterator<Line>(file_);
        }

        std::istream_iterator<Line> end()
        {
            return std::istream_iterator<Line>();
        }

    private:
        std::ifstream file_;
    };
}

#endif // !JC_FILE
