#include <iostream>
#include "neuron.h"
#include "neuron_functions.h"
#include "data_manager.h"

// URGENT TODO: ADD COMMENTS AND DOCSTRINGS EVERYWHERE

int main()
{
	Neuron neuron(Activations::ReLU, Initialisers::n_kaiming_he, 5);
	// Inputs
	std::vector<double> x = {1, 1, 1, 1, 1};
	double out = neuron.forward(x);
	std::cout << "Output: " << out << std::endl;

	std::vector<std::vector<double>> X;
	std::vector<double> y;

	parse_csv("iris.csv", X, y, true, true);
	
	Dataset dataset("iris.csv", true, true);
	dataset.show_column_names(Axis::X, 5);

	std::cout << "Correlations:\n" << std::endl;
	std::unordered_map<std::string, double> correlations = dataset.pearson_correlation(4);
	for (const auto& pair: correlations)
	{
		std::cout << pair.first << " -> " << pair.second << std::endl;
	}

	std::cout << "\n\n\n...\n" << std::endl;

	std::cout << "Dataset length: " << dataset.length() << ", width: " << dataset.width() << std::endl;

	shuffle_data(X, y);
	std::cout << "X Length: " << X.size() << ", X width: " << X[0].size() << std::endl;

	std::vector<std::vector<double>> X_train;
	std::vector<std::vector<double>> X_test;
	std::vector<double> y_train;
	std::vector<double> y_test;

	train_test_split(X, y, X_train, X_test, y_train, y_test, 0.7, true);
	std::cout << "X_train Length: " << X_train.size() << ", X_train width: " << X_train[0].size() << std::endl;

	return 0;
}
