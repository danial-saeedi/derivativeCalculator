#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

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

//RPN: Reverse Polish Notation
void rnpCovn(vector<string> tokens,stack<string> &operators,queue<string> &output)
{
	//cout << tokens[0];
	for(int i = 0; i < tokens.size();i++)
	{
		if(is_number(tokens[i])){
			output.push(tokens[i]);
		}else{
			if(operators.empty() == true){
				operators.push(tokens[i]);
			}else{
				output.push(operators.top());
				operators.pop();
				operators.push(tokens[i]);
			}
		}
	}

	while (!operators.empty()) {
		output.push(operators.top());
		operators.pop();
	}
}


int main()
{
	string expression = "20-40+10+30+40-70";

	vector<string> tokens;

	tokenReader(expression,tokens);

	stack<string> operators;
	queue<string> output;

	rnpCovn(tokens,operators,output);

	while (!output.empty()) {
		cout << output.front() << " ";
		output.pop();
	}


	return 0;
}