#pragma once

#include <vector>
#include <string>
#include <cmath>

namespace Utilities
{
	template<typename T>
	inline T concatNumbers(T pA, T pB)
	{
		T lB_copy{ pB };

		while (lB_copy > 0)
		{
			pA *= 10;
			lB_copy /= 10;
		}

		return pA + pB;
	}

	template<typename T>
	inline T positiveModulo(T value, T mod)
	{
		return ((value % mod) + mod) % mod;
	}

	std::string getCookieFromFile(const std::string& filepath);

	std::vector<std::string> getUrlContent(const std::string& cookie, const std::string& url);

	std::vector<std::string> getPromptContent();


	struct Range
	{
		size_t start{ 0 };

		size_t end{ 0 };

		Range(size_t s, size_t e) : start(s), end(e) {};

		explicit Range(std::string_view rangeStr);

		/**
		 * Tries to merge another range into this one.
		 * 
		 * @param other The other range to merge.
		 * 
		 * @returns True if the ranges were merged, false otherwise.
		 */
		bool tryMerge(const Range& other);
	};
};

struct Tile
{
	int64_t x{ 0 };
	int64_t y{ 0 };

	Tile() = default;

	Tile(int64_t x, int64_t y) : x(x), y(y) {}

	explicit Tile(const std::string& str)
	{
		const size_t commaPos{ str.find(',') };
		x = std::stoull(str.substr(0, commaPos));
		y = std::stoull(str.substr(commaPos + 1));
	}

	Tile abs() const
	{
		return Tile(std::abs(x), std::abs(y));
	}

	bool operator==(const Tile& other) const = default;

	Tile operator+(const Tile& other) const
	{
		return Tile(x + other.x, y + other.y);
	}

	Tile operator-(const Tile& other) const
	{
		return Tile(x - other.x, y - other.y);
	}

	double distanceTo(const Tile& other) const
	{
		return std::sqrt(std::pow(static_cast<double>(x) - static_cast<double>(other.x), 2) + std::pow(static_cast<double>(y) - static_cast<double>(other.y), 2));
	}

	size_t area() const
	{
		return std::abs(x * y);
	}
};