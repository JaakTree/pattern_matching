#pragma once
#include <string>
#include <vector>
#define ll signed long long


class RabinKarp
{
	std::string &genome;
	std::vector<ll> powers;
	const ll prime = 1000000009;

	ll makeHash(const std::string &substring ) { 
		ll hash = 0;
		this->powers.clear();
		this->powers.resize(substring.length());
		this->powers[0] = 1;
		for (ll i = 1; i < substring.length(); ++i)
			this->powers[i] = 2 * this->powers[i - 1];

		for (ll i = substring.length() - 1; i > -1; --i)
		{
			hash += (substring[i] * this->powers[substring.length() - i - 1]) % this->prime;
			hash %= this->prime;
		}
		return hash % this->prime;
	};

	ll remakeHash(ll currentHash, const char &previousSymbol, const char &nextSymbol)
	{
		currentHash -= ( (previousSymbol*this->powers[this->powers.size() - 1]) - this->prime );
		currentHash %= this->prime;
		currentHash *= 2;
		currentHash %= this->prime;
		currentHash += nextSymbol;
		currentHash %= this->prime;
		return currentHash %= this->prime;;
	};
	
	public:
		bool hasPattern(std::string &pattern ) { 
			if (RabinKarp::firstOccurence(pattern) > -1)
				return true;
			return false;
		};
		
		ll firstOccurence(std::string &pattern) {
			if (pattern.length() <= genome.length())
			{
				ll hashForGenome = makeHash( genome.substr(0, pattern.length()) );
				ll hashForPattern = makeHash( pattern );
				ll index = genome.length() - pattern.length() + 1;
				if (hashForPattern == hashForGenome && genome.substr(0, pattern.length()) == pattern)
					return 0;

				for (ll i = 1; i < index; ++i)
				{
					hashForGenome = remakeHash(hashForGenome, this->genome[i - 1], this->genome[pattern.length() + i - 1]);
					if (hashForPattern == hashForGenome && genome.substr(i, pattern.length()) == pattern)
						return i;
				}
				return -1;
			}
			return -1;
		};
		
		std::vector<ll> allMatches(std::string &pattern) { 
			std::vector<ll> v;  
			if (pattern.length() <= genome.length())
			{
				ll hashForGenome = makeHash(genome.substr(0, pattern.length()));
				ll hashForPattern = makeHash(pattern);
				ll index = genome.length() - pattern.length() + 1;
				if (hashForPattern == hashForGenome && genome.substr(0, pattern.length()) == pattern)
					v.push_back(0);

				for (ll i = 1; i < index; ++i)
				{
					hashForGenome = remakeHash(hashForGenome, this->genome[i - 1], this->genome[pattern.length() + i - 1]);
					if (hashForPattern == hashForGenome && genome.substr(i, pattern.length()) == pattern)
						v.push_back(i);
				}
			}
			if( v.empty() )
				v.push_back(-1);
			return v; 
		};

		RabinKarp(std::string &genome) :genome(genome){};
		~RabinKarp() {};
};