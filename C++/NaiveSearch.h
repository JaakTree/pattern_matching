#ifndef NAIVESEARCH_H
#define NAIVESEARCH_H


#include <string>
#include <vector>
#include <set>


class NaiveSearch
{
	std::string &genome;

public:
	bool hasPattern(std::string &pattern) {
		if (NaiveSearch::firstOccurence(pattern) > -1)
			return true;
		return false;
	};

	int firstOccurence(std::string &pattern) {
		int steps = genome.length() - pattern.length() + 1;
		for (int i = 0; i < steps; ++i)
		{
			int genome_index = i, pattern_index = 0;
			while (pattern_index < pattern.length() && genome[genome_index++] == pattern[pattern_index++]);
			
			if (pattern_index == pattern.length() && genome[i + pattern.length() - 1] == pattern[pattern.length() - 1])
				return i;
		}
		return -1;
	};

	std::set<int> allMatches(std::string &pattern) {
		std::set<int> v;
		int steps = genome.length() - pattern.length() + 1;
		for (int i = 0; i < steps; ++i)
		{
			int genome_index = i, pattern_index = 0;
			while (pattern_index < pattern.length() && genome[genome_index++] == pattern[pattern_index++]);

			if (pattern_index == pattern.length() && genome[i + pattern.length() - 1] == pattern[pattern.length() - 1])
				v.insert(i);
		}
		if (v.empty())
			v.insert(-1);

		return v;
	};

	NaiveSearch::NaiveSearch(std::string &genome) :genome(genome) {};
	NaiveSearch::~NaiveSearch() {};
};


#endif NAIVESEARCH_H