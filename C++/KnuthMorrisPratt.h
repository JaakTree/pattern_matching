#pragma once
#include <string>
#include <vector>
#define ll signed long long


class KnuthMorrisPratt
{
	std::string &genome;
	std::vector<ll> prefixFunction(const std::string &pattern) {
		ll patternLength = pattern.length();
		std::vector<ll> P(patternLength + 1, -1);

		for (ll i = 1; i < patternLength + 1; ++i)
		{
			ll j = P[i - 1];
			while (j != -1 && pattern[i - 1] != pattern[j])
				j = P[j];
			
			P[i] = j + 1;
		}
		return P;
	};

	public:
		bool hasPattern(std::string &pattern) {
			if (KnuthMorrisPratt::firstOccurence(pattern) > -1)
				return true;
			return false;
		};

		ll firstOccurence(std::string &pattern) {
			std::vector<ll> P = KnuthMorrisPratt::prefixFunction(pattern);
		
			ll patternIndex = 0;
			for (ll genomeIndex = 0; genomeIndex < genome.length(); ++genomeIndex)
			{
				while (patternIndex != -1 && (patternIndex == pattern.size() || pattern[patternIndex] != genome[genomeIndex]))
					patternIndex = P[patternIndex];

				++patternIndex;

				if (patternIndex == pattern.length())
					return genomeIndex - pattern.length() + 1;
			}
			return -1;
		};

		std::vector<ll> allMatches(std::string &pattern) {
			std::vector<ll> v;

			if (pattern.length() <= genome.length())
			{
				std::vector<ll> P = KnuthMorrisPratt::prefixFunction(pattern);

				ll patternIndex = 0;
				for (ll genomeIndex = 0; genomeIndex < genome.length(); ++genomeIndex)
				{
					while (patternIndex != -1 && (patternIndex == pattern.size() || pattern[patternIndex] != genome[genomeIndex]))
						patternIndex = P[patternIndex];

					++patternIndex;

					if (patternIndex == pattern.length())
						v.push_back(genomeIndex - pattern.length() + 1);
				}
			}

			if (v.empty())
				v.push_back(-1);
		
			return v;
		};

		KnuthMorrisPratt(std::string &genome) :genome(genome) {};
		~KnuthMorrisPratt() {};
};