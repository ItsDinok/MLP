#include "data_manager.h"

Dataset::Dataset(const std::vector<std::vector<double>>& X, const std::vector<double>& y)
{
	verify_integrity(X, y);

	// Easiest case, y is numeric
	for (size_t i = 0; i < X.size(); ++i)
	{
		// TODO: Add row-length enforcement
		std::vector<double> row = X[i];
		row.push_back(y[i]);
		data.push_back(row);
	}
}


//
// OVERRIDES
//
std::vector<double>& Dataset::operator[](std::size_t index)
{
	if (index >= data.size())
	{
		throw std::out_of_range("Index out of bounds");
	}
	return data[index];
}

const std::vector<double>& Dataset::operator[](std::size_t index) const
{
	if (index >= data.size())
	{
		throw std::out_of_range("Index out of bounds.");
	}
	return data[index];
}


//
// GETTERS
//
size_t Dataset::length() const
{
	return data.size();
}

size_t Dataset::width() const
{
	return data[0].size();
}

std::pair<size_t, size_t> Dataset::shape() const
{
	// returns a pair of length then width
	return std::make_pair(data.size(), data[0].size());
}


//
// MISC METHODS
//

void Dataset::verify_integrity(const std::vector<std::vector<double>>& X,
	const std::vector<double>& y) const
{
	if (X.size() != y.size()) throw std::invalid_argument("X, y size mismatch.");
	if (X.empty()) throw std::invalid_argument("X block empty.");
	if (y.empty()) throw std::invalid_argument("Y column empty.");

	const size_t width = X[0].size();
	for (const auto& row : X)
	{
		if (row.size() != width) throw std::invalid_argument("Non-rectangular input.");
	}
}
