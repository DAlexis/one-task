#include "csvreader.hpp"

#include <stdexcept>
#include <sstream>

CsvReader::CsvReader(const std::string& filename, bool hasHeader)
{
    m_file.open(filename);
    if (!m_file.is_open())
        throw std::runtime_error("Cannot open file " + filename);

    if (hasHeader)
    {
        if (!getLine(m_header))
            throw std::runtime_error("Cannot read header from " + filename);
        m_rowLength = m_header.size();
    }
}

bool CsvReader::getLine(std::vector<std::string>& line)
{
    line.clear();
    std::string l;
    if (!std::getline(m_file, l))
        return false;

    if (l.size() == 0)
        return false;

    if (l.back() == '\n')
        l.pop_back();

    if (l.back() == '\r')
        l.pop_back();

    size_t elementBegin = 0;
    size_t elementEnd = 0;

    do
    {
        elementEnd = l.find(",", elementBegin);

        if (elementEnd == std::string::npos)
        {
            line.push_back(l.substr(elementBegin, std::string::npos));
            break;
        } else {
            line.push_back(l.substr(elementBegin, elementEnd-elementBegin));
            elementBegin = elementEnd+1;
        }
    } while (elementEnd != std::string::npos);

    if (m_rowLength == 0)
    {
        // We have header-less file and this is first line, so get its lehght for referens
        m_rowLength = line.size();
    }

    if (line.size() != 0 && line.size() != m_rowLength)
    {
        throw std::range_error("Invalid row length in csv file");
    }

    return true;
}

const std::vector<std::string>& CsvReader::header()
{
    return m_header;
}
