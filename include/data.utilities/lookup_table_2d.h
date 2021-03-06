#pragma once
#include <vector>
#include <string>
#include <memory>

namespace DataUtilities
{
	class Lookup2D
	{
	public:
		virtual double operator()(double x, double y) const = 0;
	};

	class LookupTable2D : public Lookup2D
	{
	public:
		using Row = std::vector<double>;
		using Column = std::vector<double>;

		static std::unique_ptr<LookupTable2D> load(const std::string& filename);
		double lookup(size_t row, size_t column) const;
		double& lookup(size_t row, size_t column);
	
		Row xSamples;
		Column ySamples;
		std::vector<Row> fRows;
	};
}