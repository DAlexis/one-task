#ifndef LOGISTICREGRESSION_HPP
#define LOGISTICREGRESSION_HPP

#include "imodel.hpp"

#include <vector>

class LogisticRegression : public IModel
{
public:
    LogisticRegression();
    void fit(const DataSet& data) override;
    void predict(DataSet& data) override;

private:
    int m_wdim = 0;
    std::vector<double> m_w;
    static double sigma(double M);
};

#endif // LOGISTICREGRESSION_HPP
