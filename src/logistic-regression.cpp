#include "logistic-regression.hpp"
#include "dataset.hpp"

#include <cmath>
#include <cstdlib>

LogisticRegression::LogisticRegression(double gradStep) :
    m_gradStep(gradStep)
{

}

void LogisticRegression::fit(const DataSet& data)
{
    m_dim = data.colsCount();
    m_w.resize(m_dim+1);
    // Generating random weights
    for (int i=0; i<m_dim+1; i++)
    {
        m_w[i] = double(rand() - RAND_MAX/2) / RAND_MAX;
    }

    for (size_t i=0; i<data.rowsCount()/m_gradStep; i++)
    {
        makeStochasticIteration(data);
    }
}

void LogisticRegression::predict(DataSet& data)
{
    for (size_t i=0; i<data.rowsCount(); i++)
    {
        const double* x = data[i];
        data.answer(i) = getDist(x) > 0.0 ? 1.0 : -1.0;
    }
}

double LogisticRegression::sigma(double M)
{
    return 1 / (1+exp(-M));
}

void LogisticRegression::makeStochasticIteration(const DataSet& data)
{
    // Getting random element to optimize it
    size_t row = rand() % data.rowsCount();

    /*
     * W_(t+1) = W_(t) + step * y_row * x_row * ( 1-sigma( <x_row*w> * y_row ) )
     */

    const double *x = data[row];
    double answer = data.answer(row);

    double M = getDist(x) * answer;

    double brace = (1 - sigma(M));

    for (size_t i=0; i<data.colsCount(); i++)
    {
        m_w[i] += m_gradStep * answer * x[i] * brace;
    }
    m_w.back() += m_gradStep * answer * (-1.0) * brace;
}

double LogisticRegression::getDist(const double x[])
{
    double M = 0.0;
    for (int i = 0; i<m_dim; i++)
    {
        M += x[i] * m_w[i];
    }
    M += -1 * m_w.back();
    return M;
}
