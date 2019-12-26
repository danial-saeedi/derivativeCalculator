#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

//precedence of operators
#define PLUS 1
#define MINUS 1
#define MULTIPLY 2
#define DIVISION 2
#define PARENTHESES 3
#define POWER 4

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

int precedence(string operator_)
{
	if(operator_ == "+")
	{
		return PLUS;
	}
	else if(operator_ == "-")
	{
		return MINUS;	
	}
	else if(operator_ == "*")
	{
		return MULTIPLY;	
	}
	else if(operator_ == "/")
	{
		return DIVISION;	
	}
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
	for(int i = 0; i < tokens.size();i++)
	{
		if(is_number(tokens[i])){
			output.push(tokens[i]);
		}else{
			if(operators.empty() == true){
				operators.push(tokens[i]);
			}else if(precedence(tokens[i]) > precedence(operators.top()) ){
				operators.push(tokens[i]);
			}else{
				while(precedence(operators.top()) >= precedence(tokens[i]))
				{
					if(operators.size() == 1){
						break;
					}
					output.push(operators.top());
					operators.pop();
				}
				if(operators.size() == 1 && precedence(operators.top()) >= precedence(tokens[i]) ){
					output.push(operators.top());
					operators.pop();
				}

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
	string expression = "20*5*3/6+15";
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