#include "RabinKarp.h"
#include "KnuthMorrisPratt.h"
#include "BoyerMoore.h"
#include "NaiveSearch.h"
#include "BoyerMooreHorspool.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>

// 10E+6
const int GENOME_LENGTH = 1000000;

// 
double averageTime(std::vector<double> v)
{
	double time = 0;
	for (int i = 0; i < v.size(); ++i)
		time += v[i];
	return time / v.size();
}

std::vector<std::string> readFromFile(std::ifstream &fin)
{
	std::vector<std::string> v;
	std::string help_string;
	while (fin >> help_string)
		v.push_back(help_string);
	return v;
}

int main()
{
	auto begin_time = std::chrono::high_resolution_clock::now();
	auto end_time = std::chrono::high_resolution_clock::now();

	std::string genome;
	std::ifstream fin("processed.txt");
	std::ofstream fout("results.txt");

	char ch;
	fin >> genome;

	/*for (int i = 0; i < GENOME_LENGTH; ++i)
	{
		fin >> ch;
		genome += ch;
	}
	*/

	//fin >> genome;
	//genome = genome.substr(0, GENOME_LENGTH);
	std::cout << "I have read it!" << std::endl;
	fin.close();

	//genome = genome.substr(0, GENOME_LENGTH);
	
	std::vector<std::string> pattern_vector;
	std::vector< std::vector< std::string > > pattern_matrix;

	fin.open("5.txt");
	std::cout << "5" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("10.txt");
	std::cout << "10" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("15.txt");
	std::cout << "15" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("20.txt");
	std::cout << "20" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("25.txt");
	std::cout << "25" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("30.txt");
	std::cout << "30" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("50.txt");
	std::cout << "50" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("100.txt");
	std::cout << "100" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("150.txt");
	std::cout << "150" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("200.txt");
	std::cout << "200" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("250.txt");
	std::cout << "250" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();
	fin.open("300.txt");
	std::cout << "300" << std::endl;
	pattern_vector = readFromFile(fin);
	pattern_matrix.push_back(pattern_vector);
	fin.close();

	std::vector<double> v;
	std::vector<double> averageTimeExecution;

	//std::set<int> s0, s1, s2, s3, s4;

	//Need to consider how to do it better.

	//BoyerMooreHorspool
	BoyerMooreHorspool Test0(genome);
	RabinKarp Test(genome);
	KnuthMorrisPratt Test2(genome);
	BoyerMoore Test3(genome);
	NaiveSearch Test4(genome);

	std::cout << "BoyerMooreHorspool: " << std::endl;
	for (int i = 0; i < pattern_matrix.size(); ++i)
	{
		v.clear();
		std::cout << "i: " << i << std::endl;

		for (int j = 0; j < pattern_matrix[i].size(); ++j)
		{
			begin_time = std::chrono::high_resolution_clock::now();
			Test0.allMatches(pattern_matrix[i][j]);
			/*
			//s1 = Test.allMatches(pattern_matrix[i][j]);
			//s2 = Test2.allMatches(pattern_matrix[i][j]);
			//s3 = Test3.allMatches(pattern_matrix[i][j]);
			//s4 = Test4.allMatches(pattern_matrix[i][j]);
			if (s0 != s1 || s0 != s2 || s0 != s3 || s0 != s4)
			{
				std::cout << "Epic fail: BoyerMooreHorspool - " << s0.size() << " RabinKarp: " << s1.size() << " KnuthMorrisPratt: " << s2.size() << " BoyerMoore: " << s3.size() << " NaiveSearch: " << s4.size() << std::endl;
				//for (std::set<int>::iterator it = s4.begin(); it != s4.end(); ++it)
				//	std::cout << (*it) << " ";
				//std::cout << std::endl;
			}
			else
				std::cout << "OK!" << std::endl;
			*/
			end_time = std::chrono::high_resolution_clock::now();
			v.push_back(std::chrono::duration_cast<std::chrono::duration<float>>(end_time - begin_time).count());
		}
		averageTimeExecution.push_back(averageTime(v));
	}

	for (int i = 0; i < averageTimeExecution.size(); ++i)
	{
		fout << std::to_string(averageTimeExecution[i]) << " ";
	}
	fout << std::endl;


	//RabinKarp
	

	std::cout << "RabinKarp: " << std::endl;
	for (int i = 0; i < pattern_matrix.size(); ++i)
	{
		v.clear();
		std::cout << "i: " << i << std::endl;

		for (int j = 0; j < pattern_matrix[i].size(); ++j)
		{
			begin_time = std::chrono::high_resolution_clock::now();
			Test.allMatches(pattern_matrix[i][j]);
			end_time = std::chrono::high_resolution_clock::now();
			v.push_back(std::chrono::duration_cast<std::chrono::duration<float>>(end_time - begin_time).count());
		}
		averageTimeExecution.push_back(averageTime(v));
	}

	for (int i = 0; i < averageTimeExecution.size(); ++i)
	{
		fout << std::to_string(averageTimeExecution[i]) << " ";
	}
	fout << std::endl;


	//...

	//KnuthMorrisPratt

	std::cout << "KnuthMorrisPratt: " << std::endl;
	averageTimeExecution.clear();
	for (int i = 0; i < pattern_matrix.size(); ++i)
	{
		v.clear();
		std::cout << "i: " << i << std::endl;

		for (int j = 0; j < pattern_matrix[i].size(); ++j)
		{
			begin_time = std::chrono::high_resolution_clock::now();
			Test2.allMatches(pattern_matrix[i][j]);
			end_time = std::chrono::high_resolution_clock::now();
			v.push_back(std::chrono::duration_cast<std::chrono::duration<float>>(end_time - begin_time).count());
		}
		averageTimeExecution.push_back(averageTime(v));
	}

	for (int i = 0; i < averageTimeExecution.size(); ++i)
	{
		fout << std::to_string(averageTimeExecution[i]) << " ";
	}
	fout << std::endl;
	
	
	/*
	//BoyerMoore
	std::cout << "BoyerMoore: " << std::endl;
	averageTimeExecution.clear();
	for (int i = 0; i < pattern_matrix.size(); ++i)
	{
		v.clear();
		std::cout << "i: " << i << std::endl;

		for (int j = 0; j < pattern_matrix[i].size(); ++j)
		{
			begin_time = std::chrono::high_resolution_clock::now();
			Test3.allMatches(pattern_matrix[i][j]);
			end_time = std::chrono::high_resolution_clock::now();
			v.push_back(std::chrono::duration_cast<std::chrono::duration<float>>(end_time - begin_time).count());
		}
		averageTimeExecution.push_back(averageTime(v));
	}
	

	for (int i = 0; i < averageTimeExecution.size(); ++i)
	{
		fout << std::to_string(averageTimeExecution[i]) << " ";
	}
	fout << std::endl;
	*/

	//NaiveSearch

	std::cout << "NaiveSearch: " << std::endl;
	averageTimeExecution.clear();
	for (int i = 0; i < pattern_matrix.size(); ++i)
	{
		v.clear();
		std::cout << "i: " << i << std::endl;

		for (int j = 0; j < pattern_matrix[i].size(); ++j)
		{
			begin_time = std::chrono::high_resolution_clock::now();
			Test4.allMatches(pattern_matrix[i][j]);
			end_time = std::chrono::high_resolution_clock::now();
			v.push_back(std::chrono::duration_cast<std::chrono::duration<float>>(end_time - begin_time).count());
		}
		averageTimeExecution.push_back(averageTime(v));
	}

	for (int i = 0; i < averageTimeExecution.size(); ++i)
	{
		fout << std::to_string(averageTimeExecution[i]) << " ";
	}
	fout << std::endl;
	
	system("pause");
	return 0;
}