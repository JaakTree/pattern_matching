#ifndef KNUTHMORRISPRATT_H
#define KNUTHMORRISPRATT_H

#include <string>
#include <vector>


class KnuthMorrisPratt
{
	std::string &genome;
	std::vector<int> prefixFunction(const std::string &pattern) {
		int patternLength = pattern.length();
		std::vector<int> P(patternLength + 1, -1);

		for (int i = 1; i < patternLength + 1; ++i)
		{
			int j = P[i - 1];
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

		int firstOccurence(std::string &pattern) {
			std::vector<int> P = KnuthMorrisPratt::prefixFunction(pattern);
		
			int patternIndex = 0;
			for (int genomeIndex = 0; genomeIndex < genome.length(); ++genomeIndex)
			{
				while (patternIndex != -1 && (patternIndex == pattern.size() || pattern[patternIndex] != genome[genomeIndex]))
					patternIndex = P[patternIndex];

				++patternIndex;

				if (patternIndex == pattern.length())
					return genomeIndex - pattern.length() + 1;
			}
			return -1;
		};

		std::set<int> allMatches(std::string &pattern) {
			std::set<int> v;

			if (pattern.length() <= genome.length())
			{
				std::vector<int> P = KnuthMorrisPratt::prefixFunction(pattern);

				int patternIndex = 0;
				for (int genomeIndex = 0; genomeIndex < genome.length(); ++genomeIndex)
				{
					while (patternIndex != -1 && (patternIndex == pattern.size() || pattern[patternIndex] != genome[genomeIndex]))
						patternIndex = P[patternIndex];

					++patternIndex;

					if (patternIndex == pattern.length())
						v.insert(genomeIndex - pattern.length() + 1);
				}
			}

			if (v.empty())
				v.insert(-1);
		
			return v;
		};

		KnuthMorrisPratt::KnuthMorrisPratt(std::string &genome) :genome(genome) {};
		KnuthMorrisPratt::~KnuthMorrisPratt() {};
};


#endif KNUTHMORRISPRATT_H