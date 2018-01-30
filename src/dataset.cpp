#include "dataset.hpp"
#include "utils.hpp"
#include "csvreader.hpp"

#include <fstream>
#include <stdexcept>
#include <algorithm>

void DataSet::setRowLength(size_t rowLength)
{
    m_data.clear();
    m_rowLehgth = rowLength;
}

void DataSet::read_csv(CsvReader& reader, int idCol, int xColFirst, int xColLast, int yCol)
{
    std::vector<std::string> line;
    setRowLength(xColLast - xColFirst + 1);
    while (reader.getLine(line))
    {
        addRow();

        m_ids.back() = std::stoul(line[idCol]);
        if (yCol != -1)
            m_answers.back() = std::stod(line[yCol]);
        else
            m_answers.back() = 0.0;

        for (int i=xColFirst; i<=xColLast; i++)
        {
            (*this)[rowsCount()-1][i-xColFirst] = std::stod(line[i]);
        }


    }
    /*
    std::ifstream infile(filename);
    if (!infile.is_open())
        throw std::runtime_error("Cannot open file " + filename);

    std::vector<int> sortedColumns = xColumns;
    std::sort(sortedColumns.begin(), sortedColumns.end());*/

}

double* DataSet::operator[](size_t row)
{
    ASSERT(row < m_rowsCount, std::range_error("Selected row is out of range!"));
    return &m_data[row*m_rowLehgth];
}

size_t DataSet::rowsCount()
{
    return m_rowsCount;
}

void DataSet::addRow()
{
    m_ids.push_back(0);
    m_data.resize(m_data.size() + m_rowLehgth);
    m_answers.push_back(0.0);

    m_rowsCount++;
}
