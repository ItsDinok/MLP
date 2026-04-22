#include <iostream>
#include "neuron.h"
#include "neuron_functions.h"

int main()
{
	Neuron neuron(Activations::ReLU, Initialisers::n_kaiming_he, 5);

	// Inputs
	std::vector<double> x = {1, 1, 1, 1, 1};
	double out = neuron.forward(x);
	std::cout << "Output: " << out << std::endl;
	return 0;
}
