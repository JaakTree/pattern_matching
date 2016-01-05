#ifndef RABINKARP_H
#define RABINKARP_H

#include <string>
#include <vector>
#include <set>
#include <iostream>

class RabinKarp
{
	std::string genome;
	std::vector<int> powers;

	const int default_power_length = 1001;
	const int prime = 1000000009;


	void makePowers()
	{
		this->powers.resize(default_power_length);
		this->powers[0] = 1;
		for (int i = 1; i < default_power_length; ++i)
			this->powers[i] = (2 * this->powers[i - 1]) % this->prime;
	};

	// redo with iterators.
	int makeHash(const std::string &substring) { 
		long long hash = 0;
		for (int i = substring.length() - 1; i > -1; --i)
		{
			hash += (substring[i] * this->powers[substring.length() - i - 1]) % this->prime;
			hash %= this->prime;
		}
		return hash % this->prime;
	};


	int remakeHash(int currentHash, const char &previousSymbol, const char &nextSymbol, const std::string &pattern)
	{
		
		currentHash -= ( (previousSymbol*this->powers[pattern.length() - 1]) - this->prime );
		currentHash %= this->prime;
		currentHash *= 2;
		currentHash %= this->prime;
		currentHash += nextSymbol;
		currentHash %= this->prime;
		return currentHash %= this->prime;;
	};
	
	public:
		bool hasPattern(const std::string &pattern) { 
			if (RabinKarp::firstOccurence(pattern) > -1)
				return true;
			return false;
		};
		
		int firstOccurence(const std::string &pattern) {
			if (pattern.length() <= genome.length())
			{
				std::string substring = genome.substr(0, pattern.length());
				int hashForGenome = makeHash( substring );
				int hashForPattern = makeHash( pattern );
				int index = genome.length() - pattern.length() + 1;
				if (hashForPattern == hashForGenome && genome.compare(0, pattern.length(), pattern) == 0)
					return 0;

				for (int i = 1; i < index; ++i)
				{
					hashForGenome = remakeHash(hashForGenome, this->genome[i - 1], this->genome[pattern.length() + i - 1], pattern);
					if (hashForPattern == hashForGenome && genome.compare(i, pattern.length(), pattern) == 0)
						return i;
				}
				return -1;
			}
			return -1;
		};
		
		std::set<int> allMatches(const std::string &pattern) { 
			std::set<int> v;  
			if (pattern.length() <= genome.length())
			{
				std::string substring = genome.substr(0, pattern.length());
				int hashForGenome = makeHash(substring);
				int hashForPattern = makeHash(pattern);
				int index = genome.length() - pattern.length() + 1;
				if (hashForPattern == hashForGenome && genome.compare(0, pattern.length(), pattern) == 0)
					v.insert(0);

				for (int i = 1; i < index; ++i)
				{
					hashForGenome = remakeHash(hashForGenome, this->genome[i - 1], this->genome[pattern.length() + i - 1], pattern);
					if (hashForPattern == hashForGenome && genome.compare(i, pattern.length(), pattern) == 0)
						v.insert(i);
				}
			}
			if( v.empty() )
				v.insert(-1);
			return v; 
		};

		RabinKarp::RabinKarp(const std::string &genome) :genome(genome){
			makePowers();
		};
		RabinKarp::~RabinKarp() {};
};


#endif RABINKARP_H