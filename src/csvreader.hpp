#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <string>
#include <vector>
#include <fstream>

/**
 * @brief Lets invent simple csv reader that skips header parses file line-by-line
 * It checks that all lines has the same lenght
 */
class CsvReader
{
public:
    /**
     * @brief Construct reader and read header if needed
     * @param filename
     * @param hasHeader
     */
    CsvReader(const std::string& filename, bool hasHeader = true);

    /**
     * @brief Get next line as vector of strings if possible
     * @param line Will put here line presented as array of strings
     * @return false if end of file
     */
    bool getLine(std::vector<std::string>& line);

    const std::vector<std::string>& header();
private:
    std::vector<std::string> m_header;
    std::ifstream m_file;
    size_t m_rowLength = 0;
};

#endif // CSVREADER_HPP
