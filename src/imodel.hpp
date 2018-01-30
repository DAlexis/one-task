#ifndef IMODEL_HPP
#define IMODEL_HPP

class DataSet;

/**
 * @brief Interface for any simple predicting model
 */
class IModel
{
public:
    virtual ~IModel() {}
    virtual void fit(const DataSet& data) = 0;
    virtual void predict(DataSet& data) = 0;
};

#endif // IMODEL_HPP
