#include "logistic-regression.hpp"
#include "dataset.hpp"

#include <cmath>
#include <cstdlib>

LogisticRegression::LogisticRegression()
{

}

void LogisticRegression::fit(const DataSet& data)
{
    m_wdim = data.rowsCount() + 1;
    m_w.resize(m_wdim);
    // Generating random weights
    for (int i=0; i<m_wdim; i++)
    {
        m_w[i] = double(rand() - RAND_MAX/2) / RAND_MAX;
    }
}

void LogisticRegression::predict(DataSet& data)
{
}

double LogisticRegression::sigma(double M)
{
    return 1 / (1+exp(-M));
}
