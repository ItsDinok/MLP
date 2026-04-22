#include "neuron.h"

// TODO: This will probably need to be redesigned the more initialisers there are
std::vector<double> initialiser(int fan_in, Initialisers init, Activations activations)
{
	switch(init)
	{
		case Initialisers::n_kaiming_he:
			return n_kaiming_he_initialisation(fan_in, activations);
		case Initialisers::u_kaiming_he:
			return u_kaiming_he_initialisation(fan_in);
		case Initialisers::u_xavier:
			// TODO: Implement this
		case Initialisers::n_xavier:
			// TODO: Implement this

		case Initialisers::user_defined:
			// TODO: Implement this
		case Initialisers::undefined:
		default:
			std::runtime_error("Initialisation undefined");
	}
}

Neuron::Neuron(double bias, Activations activation, Initialisers init, int fan_in)
{
	this->bias = bias;
	this->activation = activation;
	weights = initialiser(fan_in, init, activation);
}

Neuron::Neuron(Activations activation, Initialisers init, int fan_in)
{
	this->activation = activation;
	bias = 0.0;
	weights = initialiser(fan_in, init, activation);
}

double activate(double x, Activations activation)
{
	// This is used to clean up the logic by hiding the fuck-off switch statement
	switch(activation)
	{
		case Activations::ReLU:
			return ReLU(x);
		case Activations::leaky_ReLU:
			return ReLU(x);
	
		case Activations::input:
			return x;

		case Activations::user_defined:
			// TODO: Implement this
		case Activations::undefined:
		default:
			throw std::runtime_error("Activation undefined.");
	}
}

double Neuron::forward(const std::vector<double>& x)
{
	// This is the function that determines the output of the neuron
	// It multiplies the weight of the prior nodes, adds the bias and then sends
	// it through the activation function
	// x is the input vector of the prior layer

	if (x.size() != weights.size())
	{
		throw std::runtime_error("Input size mismatch");
	}

	double sum = bias;

	for (size_t i = 0; i < weights.size(); ++i)
	{
		sum += weights[i] * x[i];
	}

	return activate(sum, activation);
}

InputNeuron::InputNeuron(double value)
{
	this->value = value;
}

void InputNeuron::set_value(double new_value)
{
	value = new_value;
}
