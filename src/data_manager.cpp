#include "data_manager.h"

// TODO: NaN handler
void parse_csv(const std::string& path,
	std::vector<std::vector<double>>& X,
	std::vector<double>& y,
	bool strip_top,
	bool label_encode)
{
	// This assumes a homogenous block. If this isn't true then the user can define
	// their own.
	// This does not assume this is for classification or regression, therefore it 
	// returns double

	std::ifstream file(path);

	// Used in label encode cases
	std::unordered_map<std::string, int> labels;
	int label_idx = 0;

if (!file.is_open())
	{
		std::cerr << "Failed to open file\n";
		return;
	}

	std::string line;
	while(std::getline(file, line))
	{
		// Prevents issues with column names
		if (strip_top)
		{
			strip_top = false;
			continue;
		}
		std::vector<double> x_row;
		// We need to push everything left of label to X, and everything right to y	
		std::string component = "";
		for (size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] == ',')
			{
				x_row.push_back(std::stod(component));
				component = "";
			}
			else component += line[i];
		}

		X.push_back(x_row);

		// Y column label encoding logic
		if (label_encode)
		{
			auto it = labels.find(component);
			if (it == labels.end())
			{
				labels[component] = label_idx;
				++label_idx;
			}

			y.push_back(labels[component]);
		}
		else
		{
			y.push_back(std::stod(component));
		}
	}
}


void shuffle_data(
	std::vector<std::vector<double>>& X,
	std::vector<double>& y)
{
	std::mt19937 generator(std::random_device{}());

	for (size_t i = X.size(); i-- > 1;)
	{
		std::uniform_int_distribution<int> dist(0, i);
		int j = dist(generator);

		std::swap(X[i], X[j]);
		std::swap(y[i], y[j]);
	}
}


void train_test_split(
	std::vector<std::vector<double>>& X,
	std::vector<double>& y,
	std::vector<std::vector<double>>& X_train,
	std::vector<std::vector<double>>& X_test,
	std::vector<double>& y_train,
	std::vector<double>& y_test,
	double train_balance,
	bool shuffle)
{
	if (shuffle) shuffle_data(X, y);

	int idx = X.size() * train_balance;
	std::copy(X.begin(), X.begin() + idx, std::back_inserter(X_train));
	std::copy(X.begin() + idx, X.end(), std::back_inserter(X_test));
	std::copy(y.begin(), y.begin() + idx, std::back_inserter(y_train));
	std::copy(y.begin() + idx, y.end(), std::back_inserter(y_test));
}
