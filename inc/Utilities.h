#pragma once

#include <vector>
#include <string>

namespace Utilities
{
	inline size_t concatNumbers(size_t pA, size_t pB)
	{
		size_t lB_copy{ pB };

		while (lB_copy > 0)
		{
			pA *= 10;
			lB_copy /= 10;
		}

		return pA + pB;
	}

	std::string getCookieFromFile(const std::string& filepath);

	std::vector<std::string> getUrlContent(const std::string& cookie, const std::string& url);
};

