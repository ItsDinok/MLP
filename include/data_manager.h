#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <random>
#include <utility>

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
