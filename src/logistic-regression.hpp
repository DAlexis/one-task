#ifndef LOGISTICREGRESSION_HPP
#define LOGISTICREGRESSION_HPP

#include "imodel.hpp"

#include <vector>

class LogisticRegression : public IModel
{
public:
    LogisticRegression(double gradStep = 0.01);
    void fit(const DataSet& data) override;
    void predict(DataSet& data) override;

private:
    static double sigma(double M);
    void makeStochasticIteration(const DataSet& data);
    double getDist(const double x[]);

    // Dimension of weights vector. Last weight is weight of fake always "-1" feature
    int m_dim = 0;
    size_t m_rows = 0;
    std::vector<double> m_w;
    double m_gradStep;
};

#endif // LOGISTICREGRESSION_HPP
