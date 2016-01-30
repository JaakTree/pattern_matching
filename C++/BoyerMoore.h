#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

class BoyerMoore
{
	std::string &genome;
	std::vector<int> prefixFunction(const std::string &pattern) {
		std::vector<int> P(pattern.length());

		int k = 0;
		P[0] = 0;
		for (int i = 1; i < pattern.length(); ++i) {
			while (k > 0 && pattern[k] != pattern[i])
				k = P[k - 1];

			if (pattern[k] == pattern[i])
				++k;

			P[i] = k;
		}
		return P;
	}

public:
	bool hasPattern(std::string &pattern) {
		if (BoyerMoore::firstOccurence(pattern) > -1)
			return true;
		return false;
	};

	int firstOccurence(std::string &pattern) {
		if (this->genome.length() >= pattern.length())
		{
			typedef std::unordered_map<char, int> PatternStopsTable;
			typedef std::unordered_map<int, int> PatternSuffixesTable;
			
			PatternStopsTable stopsTable;
			PatternSuffixesTable suffixesTable;

			for (int i = 0; i < pattern.length(); ++i)
				stopsTable[pattern[i]] = i;

			std::string reversePattern(pattern.rbegin(), pattern.rend());
			
			std::vector<int> p = BoyerMoore::prefixFunction(pattern), 
						    pr = BoyerMoore::prefixFunction(reversePattern);

			for (int i = 0; i < pattern.length() + 1; ++i)
				suffixesTable[i] = pattern.length() - p.back();

			for (int i = 1; i < pattern.length(); ++i) {
				int j = pr[i];
				suffixesTable[j] = std::min(suffixesTable[j], i - pr[i] + 1);
			}

			for (int shift = 0; shift <= this->genome.length() - pattern.length();) {
				int pos = pattern.length() - 1;


				while (pattern[pos] == this->genome[pos + shift]) {
					if (pos == 0)
						return shift;
					--pos;
				}

				if (pos == pattern.length() - 1) {
					PatternStopsTable::const_iterator stop_symbol = stopsTable.find(this->genome[pos + shift]);
					int stop_symbol_additional = pos - (stop_symbol != stopsTable.end() ? stop_symbol->second : -1);
					shift += stop_symbol_additional;
				}
				else {
					shift += suffixesTable[pattern.length() - pos - 1];
				}
			}
		}
		return -1;
	};


	std::set<int> allMatches(std::string &pattern) {
		std::set<int> v;
		if (this->genome.length() >= pattern.length())
		{
			typedef std::unordered_map<char, int> PatternStopsTable;
			typedef std::unordered_map<int, int> PatternSuffixesTable;

			PatternStopsTable stopsTable;
			PatternSuffixesTable suffixesTable;

			for (int i = 0; i < pattern.length(); ++i)
				stopsTable[pattern[i]] = i;

			std::string rt(pattern.rbegin(), pattern.rend());

			std::vector<int> p = BoyerMoore::prefixFunction(pattern), pr = BoyerMoore::prefixFunction(rt);

			for (int i = 0; i < pattern.length() + 1; ++i)
				suffixesTable[i] = pattern.length() - p.back();

			for (int i = 1; i < pattern.length(); ++i) {
				int j = pr[i];
				suffixesTable[j] = std::min(suffixesTable[j], i - pr[i] + 1);
			}

			for (int shift = 0; shift <= this->genome.length() - pattern.length();) {
				int pos = pattern.length() - 1;

				while (pattern[pos] == this->genome[pos + shift]) {
					if (pos == 0)
					{
						v.insert(shift);
						shift += 1;
						break;
					}
					--pos;
				}

				if (pos == pattern.length() - 1) {
					PatternStopsTable::const_iterator stop_symbol = stopsTable.find(this->genome[pos + shift]);
					int stop_symbol_additional = pos - (stop_symbol != stopsTable.end() ? stop_symbol->second : -1);
					shift += stop_symbol_additional;
				}
				else {
					shift += suffixesTable[pattern.length() - pos - 1];
				}
			}
		}
		if (v.empty())
			v.insert(-1);
		return v;
	};

	BoyerMoore::BoyerMoore(std::string &genome) :genome(genome) {};
	BoyerMoore::~BoyerMoore() {};
};


#endif BOYERMOORE_H