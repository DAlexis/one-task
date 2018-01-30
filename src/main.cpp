#include "dataset.hpp"
#include "utils.hpp"
#include "csvreader.hpp"
#include "preprocessor.hpp"
#include "knn-model.hpp"

#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

int main()
{
    cout << "Reading training data" << std::endl;
    CsvReader csvTrain("train.csv");
    DataSet train;
    train.readCSV(csvTrain, 0, 1, 5, 6);
    Preprocessor::standardize(train);

    cout << "Reading test data" << std::endl;
    CsvReader csvTest("test.csv");
    DataSet test;
    test.readCSV(csvTest, 0, 1, 5);
    Preprocessor::standardize(test);

    std::unique_ptr<IModel> model;

    model.reset(new KNNModel());

    cout << "Fitting" << std::endl;
    model->fit(train);
    cout << "Predicting" << std::endl;
    model->predict(test);

    cout << "Making output" << std::endl;
    std::ofstream output("out.txt");
    output << "\"ID\",\"y\"" << std::endl;
    test.writeAnswers(output);
    return 0;
}
