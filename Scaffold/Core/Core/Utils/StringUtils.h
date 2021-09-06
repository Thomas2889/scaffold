#pragma once

#include <string>
#include <vector>


namespace scaffold::utils::string
{
	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);

	std::vector<std::string> SplitByDelimiter(std::string str, const std::string& delim);

	std::string RemoveTrailing(std::string str, const std::string& delim = " ");

	std::string ToLower(std::string str);
	std::string ToUpper(std::string str);
}