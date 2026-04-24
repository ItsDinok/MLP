#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <random>
#include <utility>
#include <stdexcept>

// TODO: Make a dataloader struct/class

// TODO: Document class assumptions
// TODO: add constructors for difficult y cases
class Dataset
{
public:
	Dataset(const std::vector<std::vector<double>>& X, const std::vector<double>& y);
	Dataset(const std::string& path, bool strip_top = true, bool label_encode = false);

	// Getters
	size_t length() const;
	size_t width() const;
	std::pair<size_t, size_t> shape() const;

	// Overrides
	std::vector<double>& operator[](std::size_t index);
	const std::vector<double>& operator[](std::size_t index) const;

	// Correlation functions
	std::unordered_map<std::string, double> pearson_correlation(int feature);
	// TODO: Implement
	std::unordered_map<std::string, double> spearman_correlation(int feature);
	// TODO: Implement
	std::vector<std::vector<double>> correlation_matrix(const std::string& option);

	// TODO: Add seeding option
	void shuffle();

	// Interface

private:
	// Methods
	void verify_integrity(const std::vector<std::vector<double>>& X, 
		const std::vector<double>& y) const;

	// Attributes
	std::vector<std::vector<double>> data;
	// TODO: Implement
	std::pair<std::string, int> label_mapping;
	// TODO: Implement
	std::vector<std::string> column_names;
};

void parse_csv(const std::string& path, 
	std::vector<std::vector<double>>& X, 
	std::vector<double>&,
	bool strip_top = true,
	bool label_encode = false);

void shuffle_data(
	std::vector<std::vector<double>>& X,
	std::vector<double>& y);

void train_test_split(
	std::vector<std::vector<double>>& X,
	std::vector<double>& y,
	std::vector<std::vector<double>>& X_train,
	std::vector<std::vector<double>>& X_test,
	std::vector<double>& y_train,
	std::vector<double>& y_test,
	double train_balance = 0.7,
	bool shuffle = false);


// UNIMPLEMENTED
// NOTE: LDA/PCA is probably beyond me
void describe();
void standardise();
void min_max_normalisation();
void fit_scaler();
void apply_scaler();

// NOTE TODO: batching is done by the model
