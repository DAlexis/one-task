#include "dataset.hpp"
#include "utils.hpp"
#include "csvreader.hpp"

#include <iostream>

using namespace std;

int main()
{
    CsvReader csv("train.csv");
    vector<string> line;

    DataSet ds;
    ds.read_csv(csv, 0, 1, 5, 6);
    return 0;
}
