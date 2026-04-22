#include "multilayer_perceptron.h"
// TODO: Implement loop-based construction, deleting vector isn't it

Initialisers MultiLayerPerceptron::parse_initialiser(const std::string& initialiser)
{
	auto it = initialiser_map.find(initialiser);
	if (it != initialiser_map.end())
	{
		return it->second;
	}
	throw std::runtime_error("Invalid initialisation function.");
}

bool MultiLayerPerceptron::parse_layer_sizes(const std::vector<int>& layer_sizes)
{
	// Checks to see if all numbers are valid
	for (size_t i = 0; i< layer_sizes.size(); ++i)
	{
		if (layer_sizes[i]<= 0) return false;
	}
	return true;
}

std::vector<Activations> MultiLayerPerceptron::parse_activators(
		const std::vector<std::string>& activations)
{
	std::vector<Activations> checked_activators;

	// This checks to see if all of the activation functions are valid
	for (size_t i = 0; i < activations.size(); ++i)
	{
		auto it = activation_map.find(activations[i]);
		if (it != activation_map.end())
		{
			checked_activators.push_back(it->second);
		}
		else throw std::runtime_error("Invalid activator.");
	}
	return checked_activators;
}

MultiLayerPerceptron::MultiLayerPerceptron(
	std::vector<int>& layer_sizes,
	std::vector<std::string>& activation_functions,
	const std::string& initialisation_function
)
{
	/*
	layer_sizes: each entry corresponds to a new layer with that many neurons
	activation_functions: each entry corresponds to a layer with that function
	initialisation_function: the model's weights initialisation function
	*/

	// Basic error checking
	if (!parse_layer_sizes(layer_sizes))
	{
		throw std::runtime_error("Layer size cannot be zero or below.");
	}
	if (layer_sizes.size() != activation_functions.size())
	{
		throw std::runtime_error("Every layer needs an activation function.");
	}

	std::vector<Activations> a_functions = parse_activators(activation_functions);
	Initialisers initialiser = parse_initialiser(initialisation_function);

	// Construct network
	// Create initial layer
	for (int i = 0; i < layer_sizes[0]; ++i)
	{
		input_layer.push_back(InputNeuron(0));
	}
	size_t fan_in = layer_sizes[0];
	layer_sizes.erase(layer_sizes.begin());
	a_functions.erase(a_functions.begin());

	while (!layer_sizes.empty())
	{
		std::vector<Neuron> layer;
		for (int i = 0; i < layer_sizes[0]; ++i)
		{
			layer.push_back(Neuron(a_functions[0], initialiser, fan_in)); 
		}
		layers.push_back(layer);
		fan_in = layer_sizes[0];
		layer_sizes.erase(layer_sizes.begin());
		a_functions.erase(a_functions.begin());
	}
}


std::vector<double> MultiLayerPerceptron::forward(const std::vector<double>& input)
{
	// The forward function is the predictor function
	// It takes a sample as input and outputs a prediction
	// It does this by pushing it through the network

	// Safety check
	if (input.size() != input_layer.size())
	{
		throw std::runtime_error("Input size mismatch");
	}

	// Move through layers
	std::vector<double> values = input;
	for (size_t i = 1; i < layers.size(); ++i)
	{
		std::vector<double> new_values;
		for (size_t j = 0; j < layers[i].size(); ++j)
		{
			new_values.push_back(layers[i][j].forward(values));
		}
		values = new_values;
	}
	
	return values;
}
