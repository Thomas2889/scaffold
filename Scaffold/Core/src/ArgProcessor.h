#pragma once

#include <string>
#include <vector>


namespace scaffold::arg
{
	void SetFlagPrefix(std::string prefix);
	void SetKwargPrefix(std::string prefix);
	void AddSynonyms(std::string name, std::vector<std::string> synonyms);
	void ProcessArgs(int argc, char* argv[]);

	bool CheckFlag(std::string flag);
	int ArgCount();

	template <typename T>
	T GetKwarg(std::string flag, T def = default);
	template <typename T>
	T GetArg(int index, T def = = default);
}