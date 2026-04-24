#include "data_manager.h"

Dataset::Dataset(const std::vector<std::vector<double>>& X, const std::vector<double>& y)
{
	verify_integrity(X, y);

	// Easiest case, y is numeric
	for (size_t i = 0; i < X.size(); ++i)
	{
		std::vector<double> row = X[i];
		row.push_back(y[i]);
		data.push_back(row);
	}
}

// TODO: Adversarial cases handling
// TODO: Automatic label encoding or top stripping
Dataset::Dataset(const std::string& path, bool strip_top, bool label_encode)
{
	std::vector<std::vector<double>> X;
	std::vector<double> y;

	parse_csv(path, X, y, strip_top, label_encode);
	verify_integrity(X, y);
	for (size_t i = 0; i < X.size(); ++i)
	{
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
	if (data.empty()) return 0;
	return data.size();
}

size_t Dataset::width() const
{
	if (data.empty()) return 0;
	return data[0].size();
}

std::pair<size_t, size_t> Dataset::shape() const
{
	// returns a pair of length then width
	return std::make_pair(data.size(), data[0].size());
}


//
// CORRELATION ANALYSIS
//
std::unordered_map<std::string, double> Dataset::pearson_correlation(int feature)
{
	if ((size_t)feature >= width()) throw std::runtime_error("Feature index out of range.");

	// This measures the pearson correlation of each feature against a target feature
	std::unordered_map<std::string, double> correlations;
	size_t length = this->length();

	// Can be done in one loop per feature
	for (size_t i = 0; i < width(); ++i)
	{
		double sum_x = 0.0;
		double sum_y = 0.0;
		double sum_x2 = 0.0;
		double sum_y2 = 0.0;
		double sum_xy = 0.0;

		for (size_t j = 0; j < length; ++j)
		{
			sum_x += data[j][i];
			sum_y += data[j][feature];
			sum_xy += data[j][i] * data[j][feature];
			sum_x2 += data[j][i] * data[j][i];
			sum_y2 += data[j][feature] * data[j][feature];
		}

		// Inefficient but readable
		double numerator = length * sum_xy - (sum_x * sum_y);
		double denominator = std::sqrt((length * sum_x2 - (sum_x * sum_x)) *
				(length * sum_y2 - (sum_y * sum_y)));
		
		// Edge case for zero-variance columns
		if (denominator == 0) denominator = 0.00000000000000001;

		if (!column_names.empty())
		{
			correlations[column_names[i]] = numerator / denominator;
		}
		else
		{
			correlations[std::to_string(i)] = numerator / denominator;
		}
	}

	return correlations;
}


std::unordered_map<std::string, double> Dataset::spearman_correlation(int feature)
{
	std::unordered_map<std::string, double> correlations;
	return correlations;
}


//
// MUTATIONS
//

void Dataset::drop_columns(int column)
{
	if (data.empty()) throw std::runtime_error("Dataset is empty.");
	if ((size_t)column >= width()) throw std::runtime_error("Specified column out of bounds.");

	for (size_t i = 0; i < length(); ++i)
	{
		data[i].erase(data[i].begin() + column);
	}
}

void Dataset::drop_columns(const std::vector<int>& columns)
{
	if (data.empty()) throw std::runtime_error("Dataset is empty.");
	size_t width = this->width();
	for (size_t i = 0; i < columns.size(); ++i)
	{
		if ((size_t)columns[i] >= width) throw std::runtime_error("Column out of bounds.");
	}

	// Remove column for every row
	// Copy and sort descending
	std::vector<int> cols = columns;
	std::sort(cols.rbegin(), cols.rend());
	for (size_t i = 0; i < length(); ++i)
	{
		for (int col: cols)
		{
			data[i].erase(data[i].begin() + col);
		}
	}
}

void Dataset::drop_rows(int row)
{
	if (data.empty()) throw std::runtime_error("Dataset is empty.");
	if ((size_t)row >= length()) throw std::runtime_error("Row index out of bounds.");
	data.erase(data.begin() + row);
}

void Dataset::drop_rows(const std::vector<int>& rows)
{
	if (data.empty()) throw std::runtime_error("Dataset is empty.");
	size_t length = this->length();
	for (size_t i = 0; i < rows.size(); ++i)
	{
		if ((size_t)rows[i] >= length) throw std::runtime_error("Row index out of bounds.");
	}

	std::vector<int> r = rows;
	std::sort(r.rbegin(), r.rend());
	for (size_t i = 0; i < r.size(); ++i)
	{
		data.erase(data.begin() + r[i]);
	}
}

void Dataset::drop_rows(const std::pair<size_t, size_t>& range)
{
	if (data.empty()) throw std::runtime_error("Dataset is empty.");
	if (range.first >= length() || range.second >= length())
		throw std::runtime_error("Row index out of bounds.");
	if (range.first > range.second) throw std::runtime_error("Range is inverted.");

	for (int i = static_cast<int>(range.second); i >= static_cast<int>(range.first); --i)
	{
		data.erase(data.begin() + i);
	}
}

//
// MISC METHODS
//

void Dataset::shuffle()
{
	std::mt19937 generator(std::random_device{}());

	for (size_t i = length(); i-- > 1;)
	{
		std::uniform_int_distribution<size_t> dist(0, i);
		int j = dist(generator);
		std::swap(data[i], data[j]);
	}
}

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
