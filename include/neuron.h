#pragma once
#include <vector>
#include <functional>
#include <stdexcept>
#include "neuron_functions.h"

/*
I still need to implement Kaiming-He or Xavier initialisation
I still need to implement activation functions
*/

struct Neuron
{
	// TODO: Research standard default init behaviour
	Neuron(double bias, Activations activation, Initialisers init, int fan_in);
	Neuron(Activations activation, Initialisers init, int fan_in);

	// The activation function that is used to generate the output
	// These are included to reduce linearity
	Activations activation;

	// Weights are a multiplier that changes the value from prior neurons
	// Weights are initialised via an initialisation function
	std::vector<double> weights;
	double bias;

	double forward(const std::vector<double>& x);
};

struct InputNeuron
{
	InputNeuron(double value);
	void set_value(double new_value);
	
	double value;
};
