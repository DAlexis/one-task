#include "preprocessor.hpp"
#include <cmath>

void Preprocessor::standardize(DataSet& data)
{
    size_t cols = data.colsCount();
    size_t rows = data.rowsCount();
    for (size_t c=0; c<cols; c++)
    {
        // Standartizing column c
        double mse = 0.0;
        double average = 0.0;
        // Calculating average value
        for (size_t r=0; r<rows; r++)
        {
            average += data[r][c];
        }
        average /= rows;

        // Moving to zero and calculating mse
        for (size_t r=0; r<rows; r++)
        {
            double &d = data[r][c];
            d -= average;
            mse += d*d;
        }
        mse = sqrt(mse/rows);

        if (mse == 0.0) // If one feature is always constant
            continue;

        // Dividing by mse
        for (size_t r=0; r<rows; r++)
        {
            data[r][c] /= mse;
        }
    }
}
