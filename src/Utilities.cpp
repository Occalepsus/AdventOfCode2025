#include "Utilities.h"

#include <fstream>
#include <curl/curl.h>

#include <filesystem>

namespace
{
	size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}
}

std::string Utilities::getCookieFromFile(const std::string& filepath)
{
	if (std::ifstream file(filepath);
		file.is_open())
	{
		if (std::string cookie;
			std::getline(file, cookie))
		{
			return cookie;
		}
	}

	return "";
}

std::vector<std::string> Utilities::getUrlContent(const std::string& cookie, const std::string& url)
{
	CURL* curl;
	std::string readBuffer;

	std::string session = "session=" + cookie;

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_COOKIE, session.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	// Put each line into a vector
	std::vector<std::string> input;
	std::istringstream iss{ readBuffer };
	std::string line;
	while (std::getline(iss, line)) {
		input.push_back(line);
	}

	return input;
}