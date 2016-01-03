#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#define ll signed long long

class BoyerMoore
{
	std::string &genome;
	std::vector<ll> prefixFunction(const std::string &pattern) {
		std::vector<ll> P(pattern.length());

		ll k = 0;
		P[0] = 0;
		for (ll i = 1; i < pattern.length(); ++i) {
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

	ll firstOccurence(std::string &pattern) {
		if (this->genome.length() >= pattern.length())
		{
			typedef std::unordered_map<char, ll> PatternStopsTable;
			typedef std::unordered_map<ll, ll> PatternSuffixesTable;
			
			PatternStopsTable stopsTable;
			PatternSuffixesTable suffixesTable;

			for (ll i = 0; i < pattern.length(); ++i)
				stopsTable[pattern[i]] = i;

			std::string reversePattern(pattern.rbegin(), pattern.rend());
			
			std::vector<ll> p = BoyerMoore::prefixFunction(pattern), 
						    pr = BoyerMoore::prefixFunction(reversePattern);

			for (ll i = 0; i < pattern.length() + 1; ++i)
				suffixesTable[i] = pattern.length() - p.back();

			for (ll i = 1; i < pattern.length(); ++i) {
				ll j = pr[i];
				suffixesTable[j] = std::min(suffixesTable[j], i - pr[i] + 1);
			}

			for (ll shift = 0; shift <= this->genome.length() - pattern.length();) {
				ll pos = pattern.length() - 1;


				while (pattern[pos] == this->genome[pos + shift]) {
					if (pos == 0)
						return shift;
					--pos;
				}

				if (pos == pattern.length() - 1) {
					PatternStopsTable::const_iterator stop_symbol = stopsTable.find(this->genome[pos + shift]);
					ll stop_symbol_additional = pos - (stop_symbol != stopsTable.end() ? stop_symbol->second : -1);
					shift += stop_symbol_additional;
				}
				else {
					shift += suffixesTable[pattern.length() - pos - 1];
				}
			}
		}
		return -1;
	};


	std::vector<ll> allMatches(std::string &pattern) {
		std::vector<ll> v;
		if (this->genome.length() >= pattern.length())
		{
			typedef std::unordered_map<char, ll> PatternStopsTable;
			typedef std::unordered_map<ll, ll> PatternSuffixesTable;

			PatternStopsTable stopsTable;
			PatternSuffixesTable suffixesTable;

			for (ll i = 0; i < pattern.length(); ++i)
				stopsTable[pattern[i]] = i;

			std::string rt(pattern.rbegin(), pattern.rend());

			std::vector<ll> p = BoyerMoore::prefixFunction(pattern), pr = BoyerMoore::prefixFunction(rt);

			for (ll i = 0; i < pattern.length() + 1; ++i)
				suffixesTable[i] = pattern.length() - p.back();

			for (ll i = 1; i < pattern.length(); ++i) {
				ll j = pr[i];
				suffixesTable[j] = std::min(suffixesTable[j], i - pr[i] + 1);
			}

			for (ll shift = 0; shift <= this->genome.length() - pattern.length();) {
				ll pos = pattern.length() - 1;

				while (pattern[pos] == this->genome[pos + shift]) {
					if (pos == 0)
					{
						v.push_back(shift);
						shift += 1;
						break;
					}
					--pos;
				}

				if (pos == pattern.length() - 1) {
					PatternStopsTable::const_iterator stop_symbol = stopsTable.find(this->genome[pos + shift]);
					ll stop_symbol_additional = pos - (stop_symbol != stopsTable.end() ? stop_symbol->second : -1);
					shift += stop_symbol_additional;
				}
				else {
					shift += suffixesTable[pattern.length() - pos - 1];
				}
			}
		}
		if (v.empty())
			v.push_back(-1);
		return v;
	};

	BoyerMoore(std::string &genome) :genome(genome) {};
	~BoyerMoore() {};
};