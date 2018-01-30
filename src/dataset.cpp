#include "dataset.hpp"
#include "utils.hpp"
#include "csvreader.hpp"

#include <stdexcept>
#include <algorithm>

void DataSet::setRowLength(size_t rowLength)
{
    m_data.clear();
    m_rowLehgth = rowLength;
}

void DataSet::readCSV(CsvReader& reader, int idCol, int xColFirst, int xColLast, int yCol)
{
    ASSERT(xColFirst < xColLast, std::range_error("xColFirst must be lesser than xColLast!"));
    std::vector<std::string> line;
    setRowLength(xColLast - xColFirst + 1);
    int maxCol = reader.header().size()-1;
    if (maxCol < xColLast || maxCol < idCol || maxCol < yCol)
    {
        throw std::range_error("To few columns in csv file!");
    }
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
}

void DataSet::writeAnswers(std::ostream& stream)
{
    for (size_t i=0; i<rowsCount(); i++)
    {
        stream << id(i) << "," << int(answer(i)) << std::endl;
    }
}

double* DataSet::operator[](size_t row)
{
    ASSERT(row < m_rowsCount, std::range_error("Selected row is out of range!"));
    return &m_data[row*m_rowLehgth];
}

const double* DataSet::operator[](size_t row) const
{
    ASSERT(row < m_rowsCount, std::range_error("Selected row is out of range!"));
    return &m_data[row*m_rowLehgth];
}

double& DataSet::answer(size_t row)
{
    ASSERT(row < m_rowsCount, std::range_error("Selected row is out of range!"));
    return m_answers[row];
}

const double& DataSet::answer(size_t row) const
{
    ASSERT(row < m_rowsCount, std::range_error("Selected row is out of range!"));
    return m_answers[row];
}


size_t DataSet::id(size_t row) const
{
    ASSERT(row < m_rowsCount, std::range_error("Selected row is out of range!"));
    return m_ids[row];
}

size_t DataSet::rowsCount() const
{
    return m_rowsCount;
}

size_t DataSet::colsCount() const
{
    return m_rowLehgth;
}

void DataSet::addRow()
{
    m_ids.push_back(0);
    m_data.resize(m_data.size() + m_rowLehgth);
    m_answers.push_back(0.0);

    m_rowsCount++;
}
