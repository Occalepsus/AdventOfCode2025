#pragma once

#include <vector>
#include <string>

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

