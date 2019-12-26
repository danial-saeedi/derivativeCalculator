#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int digitCounter(string s)
{
	int digits = 0;
	for(int i = 0; i < s.length();i++)
	{
		if(isdigit(s[i]))
		{
			digits += 1;
		}
		else
		{
			break;
		}
	}

	return digits;
}

void tokenReader(string formula,vector<string> &tokens)
{
	int length = formula.length();

	for(int i = 0; i < length;i++)
	{
		if(isdigit(formula[i]))
		{
			//cout << i << endl;
			string number = formula.substr(i,1);
			int digits = digitCounter(formula.substr(i+1));

			if(digits > 0){
				for(int j = i+1; j <= i+digits; j++)
				{
					number += formula.substr(j,1);
				}

				i = i + digits;
			}
			
			

			tokens.push_back(number);
		}
		else
		{
			tokens.push_back(formula.substr(i,1));
		}
	}
}

int main()
{
	string formula = "(20+20)*3+1";

	vector<string> tokens;

	tokenReader(formula,tokens);

	for(int i = 0;i < tokens.size();i++)
	{
		cout << tokens[i] << endl;
	}

	return 0;
}