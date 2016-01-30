#include "RabinKarp.h"
#include "KnuthMorrisPratt.h"
#include "BoyerMoore.h"
#include <iostream>

int main()
{
	std::string testString = "Long Big String To Find Elements";
	std::string subStringOne = "String";
	std::string substringTwo = "Nothing";
	std::string g = "g";
	std::string breakTest = "Big Ben";
	//RabinKarp
	RabinKarp Test(testString);
	std::cout << Test.firstOccurence(subStringOne) << std::endl;
	std::cout << Test.firstOccurence(substringTwo) << std::endl;
	std::vector<ll> v = Test.allMatches(g);
	for (ll i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	std::cout << Test.hasPattern(g) << std::endl;
	std::cout << Test.hasPattern(breakTest) << std::endl;
	
	//KnuthMorrisPratt
	KnuthMorrisPratt Test2(testString);
	std::cout << "KnuthMorrisPratt: " << std::endl;
	std::cout << Test2.firstOccurence(subStringOne) << std::endl;
	std::cout << Test2.firstOccurence(substringTwo) << std::endl;
	
	
	v = Test2.allMatches(g);
	for (ll i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	std::cout << Test2.hasPattern(g) << std::endl;
	std::cout << Test2.hasPattern(breakTest) << std::endl;
	
	
	//BoyerMoore
	BoyerMoore Test3(testString);
	std::cout << "BoyerMoore:" << std::endl;
	std::cout << Test3.firstOccurence(subStringOne) << std::endl;
	std::cout << Test3.firstOccurence(substringTwo) << std::endl;

	v = Test3.allMatches(g);
	for (ll i = 0; i < v.size(); ++i)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	std::cout << Test3.hasPattern(g) << std::endl;
	std::cout << Test3.hasPattern(breakTest) << std::endl;

	//AhoCorasik


	system("pause");
	return 0;
}