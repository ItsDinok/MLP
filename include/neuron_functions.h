#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <unordered_map>

enum class Activations
{
	ReLU,
	leaky_ReLU,

	input,
	undefined,
	user_defined
};

// Used to verify user input
const std::unordered_map<std::string, Activations> activation_map = 
{

};

enum class Initialisers
{
	n_kaiming_he,
	u_kaiming_he,
	n_xavier,
	u_xavier,

	input,
	undefined,
	user_defined
};

const std::unordered_map<std::string, Initialisers> initialiser_map =
{

};

// SECTION: Initialisation
// TODO: All of the offshoot functions for KH
std::vector<double> n_kaiming_he_initialisation(int fan_in, Activations activation, bool fan_out = false);
std::vector<double> u_kaiming_he_initialisation(int fan_in);
double xavier_initialisation(std::vector<double> weights);

// SECTION: Activation
double ReLU(double x);
double sigmoid(double x);

