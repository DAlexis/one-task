#include "dataset.hpp"
#include "utils.hpp"
#include "csvreader.hpp"
#include "preprocessor.hpp"
#include "knn-model.hpp"
#include "logistic-regression.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
    try
    {
        string method = "log";
        string trainFile = "train.csv";
        string testFile = "test.csv";
        string outFile = "submission.csv";

        if (argc > 1)
        {
            if (string(argv[1]) == "help") {
                cout << "Usage: ivr-task [method (log|knn)] [train file] [test file] [submission file]" << endl;
                cout << "   or: ivr-task help" << endl;
                return EXIT_SUCCESS;
            } else {
                method = argv[1];
            }
        }
        if (argc > 2)
        {
            trainFile = argv[2];
        }
        if (argc > 3)
        {
            testFile = argv[3];
        }
        if (argc > 4)
        {
            outFile = argv[4];
        }

        cout << "Reading training data " << trainFile << std::endl;
        CsvReader csvTrain(trainFile);
        DataSet train;
        train.readCSV(csvTrain, 0, 1, 5, 6);
        Preprocessor::standardize(train);

        cout << "Reading test data " << testFile << std::endl;
        CsvReader csvTest(testFile);
        DataSet test;
        test.readCSV(csvTest, 0, 1, 5);
        Preprocessor::standardize(test);

        std::unique_ptr<IModel> model;

        if (method == "log")
        {
            model.reset(new LogisticRegression(0.01));
        } else if (method == "knn")
        {
            model.reset(new KNNModel());
        } else {
            cerr << "Unknown method: " << method << ". Use log or knn" << endl;
            return EXIT_FAILURE;
        }

        cout << "Fitting" << std::endl;
        model->fit(train);
        cout << "Predicting" << std::endl;
        model->predict(test);

        cout << "Making output to " << outFile << std::endl;
        std::ofstream output(outFile);

        output << "\"ID\",\"y\"" << std::endl;
        test.writeAnswers(output);
        return EXIT_SUCCESS;
    }
    catch (std::exception& ex) {
        cerr << "Error occured: " << ex.what() << endl;
        return EXIT_FAILURE;
    }
    catch(...) {
        cerr << "Unknown error occured!" << endl;
        return EXIT_FAILURE;
    }
}
