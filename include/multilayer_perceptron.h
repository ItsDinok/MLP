#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include "neuron_functions.h"
#include "neuron.h"

class MultiLayerPerceptron
{
public:
	MultiLayerPerceptron(
		std::vector<int>& layer_sizes,
		std::vector<std::string>& activation_functions,
		const std::string& initialisation_function
	);

	std::vector<double> forward(const std::vector<double>& input);

private:
	// Attributes
	std::vector<InputNeuron> input_layer;
	std::vector<std::vector<Neuron>> layers;

	// Functions
	std::vector<Activations> parse_activators(
			const std::vector<std::string>& activations);
	Initialisers parse_initialiser(const std::string& initialiser);
	bool parse_layer_sizes(const std::vector<int>& layer_sizes);
};
