// ConsoleApplication37.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cmath>
using namespace std;

struct MiniProduct{
	int tens;
	int ones;
	MiniProduct(int tens, int ones) {
		this->tens = tens;
		this->ones = ones;
	}
};

int main() {
	/*string answer = "";*/
	string a, b;
	while (cin >> a >> b && a!="0" && b!= "0") {
		std::cout << "+---";
		for (int i = 0; i < (a.size() - 1) * 3 + a.size(); ++i) {
			std::cout << '-';
		}
		std::cout << "---+\n";
		std::cout << "|   ";
		for (int i = 0; i < a.size(); ++i) {
			std::cout << a[i] << "   ";
		}
		std::cout << "|\n";
		
		//useful stuff
		vector<vector<MiniProduct> > lattice(a.size(), vector<MiniProduct>(b.size(), MiniProduct(0, 0)));
		for (int bIn = 0; bIn < b.size(); ++bIn) {
			for (int aIn = 0; aIn < a.size(); ++aIn) {
				int product = ((int)a[aIn] - 48) * ((int)b[bIn] - 48);
				//left to right to down
				lattice[aIn][bIn] = MiniProduct((product - product % 10) / 10, product % 10);
			}
		}

		/* 1 2 3
		   4 5 6
				  */
				  //aIn + 1 goes right 1
				  //bIn + 1 goes down 1
		int carry = 0;
		//round 1
		vector<int> answer;
	
		int bIn = b.size() - 1;
		for (int aIn = a.size() - 1; aIn >= 0; --aIn) {
			int sum = carry;
			sum += lattice[aIn][bIn].ones;
			int bIncrease = bIn;
			for (int aIncrease = aIn + 1; aIncrease < a.size(); ++aIncrease) {
				sum += lattice[aIncrease][bIncrease].tens; //get the tens
				if (--bIncrease >= 0) { //if not at the "roof, get the same aIndex ones"
					sum += lattice[aIncrease][bIncrease].ones;
				}
				else {
					break;
				}
				//move right again starting at tens
			}

			answer.insert(answer.begin(), sum % 10);
			carry = (sum - sum % 10) / 10;

		}
		//round 2
		int aIn = 0;
		for (int bIn = b.size() - 1; bIn >= 0; --bIn) { //start with 10s
			int sum = carry;
			sum += lattice[aIn][bIn].tens;
			int aIncrease = aIn;
			for (int bIncrease = bIn - 1; bIncrease >= 0; --bIncrease) {
				sum += lattice[aIncrease][bIncrease].ones;
				if (++aIncrease < a.size()) {
					sum += lattice[aIncrease][bIncrease].tens;
				}
				else {
					break;
				}
			}

			if (aIn == 0 && bIn == 0) {
				answer.insert(answer.begin(), sum );
			}
			else {
				answer.insert(answer.begin(), sum % 10);
				carry = (sum - sum % 10) / 10;
			}
		}
		int lastAnswer = -1;
		int thisAnswer = answer[0] == 0 ? -1 : answer[0];
		int ansIn = 0;
		for (int y = 0; y < b.size(); ++y) {
			std::cout << "| +";
			for (int i = 0; i < a.size(); ++i) {
				std::cout << "---+";
			}
			std::cout << " |\n";
			if (lastAnswer == -1) {
				std::cout << "| |";
			}
			else {
				std::cout << "|/|";
			}
			
			for (int x = 0; x < a.size(); ++x) {
				std::cout << lattice[x][y].tens << " /|";
			}
			std::cout << " |\n";
			std::cout << "| |";
			for (int x = 0; x < a.size(); ++x) {
				std::cout << " / |";
			}
			std::cout << b[y] <<"|\n";
			if (thisAnswer != -1) {
				std::cout << '|' << thisAnswer << '|';
			}
			else {
				std::cout << "| |";
			}
			for (int x = 0; x < a.size(); ++x) {
				std::cout << "/ " << lattice[x][y].ones << '|';
			}
			std::cout << " |\n";
			++ansIn;
			lastAnswer = thisAnswer;
			thisAnswer = answer[ansIn];
		}
		
		std::cout << "| +";
		for (int i = 0; i < a.size(); ++i) {
			std::cout << "---+";
		}
		std::cout << " |\n";
		std::cout << "|";
		if (lastAnswer != -1) {
			std::cout << "/ " << answer[ansIn++] << ' ';
		}
		else {
			std::cout << "  " << answer[ansIn++] << ' ';
		}
		for (int i = ansIn; i < answer.size(); ++i) {
			 std::cout << "/ " << answer[i] << ' ';
		}
		std::cout << "   |\n";
		std::cout << "+---";
		for (int i = 0; i < (a.size() - 1) * 3 + a.size(); ++i) {
			std::cout << '-';
		}
		std::cout << "---+\n";
	}
}