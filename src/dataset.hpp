#ifndef __DATASET_HPP__
#define __DATASET_HPP__

#include <cstring>
#include <string>
#include <vector>
#include <ostream>

class CsvReader;

/**
 * Store data set
 */
class DataSet
{
public:
    /**
     * @brief setRowLength Clear container and set row length to presented
     * @param rowLength New row length
     */
    void setRowLength(size_t rowLength);

    /**
     * @brief Hmm. Yoy say I cannot use 3rdparty libraries so lets invite simpliest csv parser.
     * It will:
     *  - skip header
     *  - treat columns from xColFirst to xColLast as features
     *  - treat column yCol as answer
     *
     * @param filename Name of csv file
     * @param xColFirst First feature column index
     * @param xColLast Last feature column index
     * @param yColumn Index of column with answer if presented
     */
    void readCSV(CsvReader& reader, int idCol, int xColFirst, int xColLast, int yCol = -1);

    void writeAnswers(std::ostream& stream);

    /**
     * @brief Get features row by index
     * @param rowRow index
     * @return raw pointer to data row
     */
    double* operator[](size_t row);
    const double* operator[](size_t row) const;

    /**
     * @brief Get answer by row index
     * @param row Row index
     * @return +1/-1 or zero if no class set
     */
    double& answer(size_t row);
    const double& answer(size_t row) const;

    /**
     * @brief Get id of data row
     * @param row Row index
     * @return id
     */
    size_t id(size_t row) const;

    /**
     * @brief Get total rows count
     * @return count
     */
    size_t rowsCount() const;

    /**
     * @brief Get total number of columns
     * @return
     */
    size_t colsCount() const;

private:
    void addRow();

    std::vector<double> m_data;
    std::vector<size_t> m_ids;
    std::vector<double> m_answers;

    size_t m_rowLehgth = 0;
    size_t m_rowsCount = 0;
};

#endif // __DATASET_HPP__
