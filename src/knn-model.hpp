#ifndef KNNMODEL_HPP
#define KNNMODEL_HPP

#include "imodel.hpp"

#include <vector>

class KNNModel : public IModel
{
public:
    KNNModel(int nearestCount = 5);
    void fit(const DataSet& data) override;
    void predict(DataSet& data) override;

private:
    struct DistAnswer
    {
        DistAnswer(double distance, double ans) : distance(distance), ans(ans) {}

        double distance = 0.0;
        double ans = 0.0;

        bool operator<(const DistAnswer& right) const { return distance < right.distance; }
    };

    double dist(const double p1[], const double p2[]);
    void buildDistsWA(const double p[]);
    double getMostProbableAnswer();

    const DataSet* m_train = 0;
    int m_dim = 0;
    int m_nearestCount;

    std::vector<DistAnswer> m_distsWithAnsrews;
};

#endif // KNNMODEL_HPP
