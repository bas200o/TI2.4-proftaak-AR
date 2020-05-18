#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

class StringUtil
{
public:
	inline static std::vector<std::string> split(const std::string& input, std::string delimiter)
	{
		std::vector<std::string> output = std::vector<std::string>();
		std::string s = input;

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos)
		{
			token = s.substr(0, pos);
			output.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		output.push_back(s);

		return output;
	}

	inline static std::string removeNeighboringSpaces(const std::string& input)
	{
		std::stringstream stream;

		if (input.length() != 0)
		{
			char lastChar = input[0];
			stream << input[0];
			for (int i = 1; i < input.length(); i++)
			{
				if (input[i] == ' ' && input[i] == lastChar)
					continue;

				stream << input[i];
				lastChar = input[i];
			}
		}

		return stream.str();
	}

	inline static bool isNumber(const std::string& input)
	{
		std::string::const_iterator it = input.begin();
		while (it != input.end() && std::isdigit(*it)) ++it;
		return !input.empty() && it == input.end();
	}

	static void lTrim(std::string& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
			}));
	}

	static void rTrim(std::string& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	static void trim(std::string& s)
	{
		lTrim(s);
		rTrim(s);
	}
};