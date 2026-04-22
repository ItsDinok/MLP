#include "neuron_functions.h"

// SECTION: Initialisation
// TODO: Docstrings and explanations
std::vector<double> n_kaiming_he_initialisation(int fan_in, Activations activation, bool fan_out)
{
	// Calculate variance
	double deviation = -1.0;
	switch(activation)
	{
		case Activations::ReLU:
			deviation = std::sqrt(2.0 / fan_in);
			break;
		case Activations::leaky_ReLU:
			// TODO implement this
			break;

		case Activations::input:
			return std::vector<double> {1.0};
		default:
			// Xavier-like initialisation
			deviation = std::sqrt(1.0 / fan_in);
			break;
	}

	// Create generator
	std::mt19937 generator(std::random_device{}());
	std::normal_distribution<double> distribution(0, deviation);

	// Fill weights vector
	std::vector<double> weights;
	for (int i = 0; i < fan_in; ++i)
	{
		weights.push_back(distribution(generator));
	}
	return weights;
}

std::vector<double> u_kaiming_he_initialisation(int fan_in)
{
	// Get bounds
	double l_bound = -std::sqrt(6.0 / fan_in);
	double u_bound = std::sqrt(6.0 / fan_in);

	// Create generator
	std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<double> distribution(l_bound, u_bound);

	// Fill weights vector
	std::vector<double> weights;
	for (int i = 0; i < fan_in; ++i)
	{
		weights.push_back(distribution(generator));
	}
	return weights;
}


// SECTION: Activation
double ReLU(double x)
{
	if (x < 0) return 0;
	return x;
}

double sigmoid(double x)
{
	if (x < 0.5) return 0;
	return 1;
}
