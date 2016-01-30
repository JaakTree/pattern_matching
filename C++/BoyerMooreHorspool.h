#ifndef BOYERMOOREHORSPOOL_H
#define BOYERMOOREHORSPOOL_H

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>


class BoyerMooreHorspool
{
	std::string &genome;
	int badCharShift(char c, std::map<char, int> shift_table)
	{
		if (shift_table.find(c) != shift_table.end())
			return shift_table[c];
		else
			return shift_table['!'];
	};
	
	std::map<char, int> badCharTable(std::string &pattern)
	{
		std::map<char, int> shift_table;
		for (int i = 1; i < pattern.length(); ++i)
		{
			if( shift_table.find(pattern[pattern.length() - i - 1]) == shift_table.end() )
				shift_table[pattern[pattern.length() - i - 1]] = i;
		}
		shift_table['!'] = pattern.length();
		return shift_table;
	}

public:
	bool hasPattern(std::string &pattern) {
		if (BoyerMooreHorspool::firstOccurence(pattern) > -1)
			return true;
		return false;
	};

	int firstOccurence(std::string &pattern) {
		if (genome.length() >= pattern.length())
		{
			std::map<char, int> shift_table = BoyerMooreHorspool::badCharTable(pattern);
			int skip = 0;
			while (this->genome.length() - skip >= pattern.length())
			{
				int i = pattern.length();
				while (this->genome[skip + (--i)] == pattern[i])
				{
					if (i == 0)
						return skip + i;
					//--i;
				}
				skip += badCharShift(this->genome[skip + pattern.length() - 1], shift_table);
			}
		}
		return -1;
	};

	/*
	def all_matches(self, pattern):
        """ returns indexes of all matches of a pattern in the text """

        pat_len = len(pattern)
        if pat_len > self.text_len:
            raise ValueError("Pattern length is bigger than text")

        bad_char_table = self._bad_char_table(pattern)
        indexes = []
        skip = 0
        while self.text_len - skip >= pat_len:
            i = pat_len - 1
            while self.text[skip + i] == pattern[i]:
                if i == 0:
                    indexes.append(skip + i)
                    break

                i -= 1

            skip = skip + self._bad_char_shift(self.text[skip + pat_len - 1], bad_char_table)

        return indexes
	*/

	std::set<int> allMatches(std::string &pattern) {
		std::set<int> v;
		if (genome.length() >= pattern.length())
		{
			std::map<char, int> bad_char_table = BoyerMooreHorspool::badCharTable(pattern);
			int skip = 0;
			//std::cout << "IN: " << std::endl;

			while (this->genome.length() - skip >= pattern.length())
			{
				int i = pattern.length() - 1;
				while (this->genome[skip + i] == pattern[i])
				{
					if (i == 0)
					{
						v.insert(skip + i);
						break;
					}
					i -= 1;
				}
				skip += badCharShift(this->genome[skip + pattern.length() - 1], bad_char_table);
				//std::cout << "Skip: " << skip << std::endl;
			}
			//std::cout << "OUT: " << std::endl;
		}
		if (v.empty())
			v.insert(-1);
		return v;
	};

	BoyerMooreHorspool(std::string &genome) :genome(genome) {};
	~BoyerMooreHorspool() {};
};

#endif BOYERMOOREHORSPOOL_H