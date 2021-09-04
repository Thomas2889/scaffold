#include "ArgProcessor.h"

#include <unordered_map>
#include <unordered_set>

#include "StringUtils.h"


namespace scaffold::arg
{
	struct SynonymData
	{
		std::unordered_set<std::string> synonyms;
		std::string name;
	};

	std::vector<std::string> args;

	std::string flagPrefix = "-";
	std::string kwargPrefix = "--";

	std::unordered_set<std::string> flagData;
	std::unordered_map<std::string, std::string> kwargData;
	std::vector<SynonymData> flagSynonyms;

	void SetFlagPrefix(std::string prefix)
	{
		flagPrefix = prefix;
	}
	void SetKwargPrefix(std::string prefix)
	{
		kwargPrefix = kwargPrefix;
	}
	void AddSynonyms(std::string name, std::vector<std::string> synonyms)
	{
		SynonymData data;
		data.name = utils::string::ToLower(name);
		for (std::string synonym : synonyms)
			data.synonyms.insert(utils::string::ToLower(synonym));
		flagSynonyms.push_back(data);
	}

	void ProcessArgs(int argc, char* argv[])
	{
		std::string currKwarg = "";
		std::string currQuotedArg = "";
		for (int i = 1; i < argc; i++)
		{
			std::string arg(argv[i]);

			if (currQuotedArg != "")
			{
				currQuotedArg += " " + arg;
				if (arg[arg.size() - 1] == '\"')
				{
					if (arg.size() > 1 && arg[arg.size() - 2] != '\\')
					{
						currQuotedArg.pop_back();
						if (currKwarg != "")
						{
							kwargData[currKwarg] = currQuotedArg;
							currKwarg = "";
						}
						else
						{
							args.push_back(currQuotedArg);
						}
						currQuotedArg = "";
					}
				}
			}
			else
			{
				if (arg.rfind("\"", 0) == 0)
				{
					arg.erase(0, 1);
					currQuotedArg = arg;
				}
				else if (arg.rfind(kwargPrefix, 0) == 0)
				{
					if (currKwarg != "")
					{
						kwargData[currKwarg] = "";
						currKwarg = "";
					}

					arg = utils::string::ToLower(arg);

					for (int i = 0; i < flagSynonyms.size(); i++)
					{
						if (flagSynonyms[i].synonyms.find(arg) != flagSynonyms[i].synonyms.end())
						{
							arg = flagSynonyms[i].name;
							break;
						}
					}

					currKwarg = arg;
				}
				else if (arg.rfind(flagPrefix, 0) == 0)
				{
					if (currKwarg != "")
					{
						kwargData[currKwarg] = "";
						currKwarg = "";
					}

					arg = utils::string::ToLower(arg);

					for (int i = 0; i < flagSynonyms.size(); i++)
					{
						if (flagSynonyms[i].synonyms.find(arg) != flagSynonyms[i].synonyms.end())
						{
							arg = flagSynonyms[i].name;
							break;
						}
					}

					flagData.insert(arg);
				}
				else
				{
					if (currKwarg != "")
					{
						kwargData[currKwarg] = arg;
						currKwarg = "";
					}
					else
					{
						args.push_back(arg);
					}
				}
			}
		}


		if (currQuotedArg != "")
		{
			if (currKwarg != "")
			{
				kwargData[currKwarg] = currQuotedArg;
				currKwarg = "";
			}
			else
			{
				args.push_back(currQuotedArg);
			}
		}
		if (currKwarg != "")
		{
			kwargData[currKwarg] = "";
			currKwarg = "";
		}

		flagSynonyms.clear();
	}

	bool CheckFlag(std::string flag)
	{
		return flagData.find(flag) != flagData.end();
	}
	int ArgCount()
	{
		return args.size();
	}

	template<>
	std::string GetKwarg(std::string flag, std::string def)
	{
		flag = utils::string::ToLower(flag);
		if (kwargData.find(flag) != kwargData.end())
			return kwargData[flag];
		kwargData[flag] = def;
		return def;
	}
	template<>
	int GetKwarg(std::string flag, int def)
	{
		flag = utils::string::ToLower(flag);
		if (kwargData.find(flag) != kwargData.end())
			return std::stoi(kwargData[flag]);
		kwargData[flag] = std::to_string(def);
		return def;
	}
	template<>
	float GetKwarg(std::string flag, float def)
	{
		flag = utils::string::ToLower(flag);
		if (kwargData.find(flag) != kwargData.end())
			return std::stof(kwargData[flag]);
		kwargData[flag] = std::to_string(def);
		return def;
	}

	template<>
	std::string GetArg(int index, std::string def)
	{
		if (index >= args.size())
			return def;
		return args[index];
	}
	template<>
	int GetArg(int index, int def)
	{
		if (index >= args.size())
			return def;
		return std::stoi(args[index]);
	}
	template<>
	float GetArg(int index, float def)
	{
		if (index >= args.size())
			return def;
		return std::stof(args[index]);
	}
}
