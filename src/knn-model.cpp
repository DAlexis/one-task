#include "knn-model.hpp"
#include "utils.hpp"
#include "dataset.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

KNNModel::KNNModel(int nearestCount) :
    m_nearestCount(nearestCount)
{
}

void KNNModel::fit(const DataSet& data)
{
    m_train = &data;
    m_dim = m_train->colsCount();
}

void KNNModel::predict(DataSet& data)
{
    ASSERT(m_dim != 0, std::runtime_error("Cannot predict for not fitted model"));

    for (size_t i=0; i<data.rowsCount(); i++)
    {
        const double* point = data[i];
        buildDistsWA(point);
        data.answer(i) = getMostProbableAnswer();
    }
}

double KNNModel::dist(const double p1[], const double p2[])
{
    double d = 0.0;
    for (int i=0; i<m_dim; i++)
    {
        double dx = p1[i] - p2[i];
        d += dx*dx;
    }
    d = sqrt(d);
    return d;
}

void KNNModel::buildDistsWA(const double p[])
{
    m_distsWithAnsrews.clear();
    for (size_t i=0; i<m_train->rowsCount(); i++)
    {
        m_distsWithAnsrews.emplace_back(dist(p, (*m_train)[i]), m_train->answer(i));
    }

    // We need to find nearest m_nearestCount elements, so lets do it with std function
    std::nth_element(m_distsWithAnsrews.begin(), m_distsWithAnsrews.begin() + m_nearestCount, m_distsWithAnsrews.end());
}

double KNNModel::getMostProbableAnswer()
{
    double sum = 0.0;
    for (int i=0; i<m_nearestCount; i++)
        sum += m_distsWithAnsrews[i].ans;

    return sum > 0.0 ? 1.0 : -1.0;
}
