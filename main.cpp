#include <iostream>
#include <queue>
#include <stack>
#include<string>
#include<cstring>
#include <vector>

//Headers
using namespace std;

//precedence of operators
#define PLUS 1
#define MINUS 1
#define MULTIPLY 2
#define DIVISION 2
#define PARENTHESES 3
#define POWER 4
  
bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_letter(string input)
{
	for (int i = 0; i < input.size(); i++)
	{
		int uppercaseChar = toupper(input[i]);
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') 
		{
			return false;
		}
	}
	return true;
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
	else if(operator_ == "^")
	{
		return POWER;
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
void rpnConv(vector<string> tokens,stack<string> &operators,queue<string> &output)
{
	for(int i = 0; i < tokens.size();i++)
	{
		if(is_number(tokens[i]) || is_letter(tokens[i])){
			output.push(tokens[i]);
		}else{
			if(operators.empty() == true){
				operators.push(tokens[i]);
			}
			else if(tokens[i] == "("){
				operators.push(tokens[i]);
			}

			else if(tokens[i] == ")")
			{
				while(true)
				{
					if(operators.top() != "(")
					{
						output.push(operators.top());
						operators.pop();
					}else{
						break;
					}

				}

				operators.pop();
			}
			else if(precedence(tokens[i]) > precedence(operators.top()) ){
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

struct Node {
   string data;   
   struct Node *left;
   struct Node *right;
};

struct Node* newNode(string data) 
{
    struct Node* temp = new Node; 
    temp->data = data; 
    temp->left = temp->right = NULL; 
    return temp;
}; 

void constructTree(queue<string> output,stack<struct Node*> &tree)
{
	while (!output.empty())
	{
		if(is_number(output.front()) || is_letter(output.front()))
		{
			Node *parent = newNode(output.front());

			tree.push(parent);
		}else if(output.front() == "^"){
			Node *parent = newNode(output.front());

			Node *right = tree.top();
			tree.pop();

			Node *left = tree.top();
			tree.pop();

			parent->left = left;
			parent->right = right;

			tree.push(parent);
		}
		else if(output.front() == "+" || output.front() == "-" || output.front() == "/" || output.front() == "*")
		{
			Node *parent = newNode(output.front());

			Node *right = tree.top();
			tree.pop();

			Node *left = tree.top();
			tree.pop();

			parent->left = left;
			parent->right = right;

			tree.push(parent);
		}

		output.pop();
	}

	// while (!temp.empty())
	// {
	// 	//cout << temp.top() << " ";
	// 	temp.pop();
	// }
}

void printPostorder(struct Node* node)
{
    if (node == NULL)
        return; 
  
    // first recur on left subtree 
    printPostorder(node->left); 
  
    // then recur on right subtree 
    printPostorder(node->right); 

    cout << node->data << " ";
}

int main()
{
	string expression = "2*(x)^(2)/((x))";
	vector<string> tokens;

	stack<string> operators;
	queue<string> output;

	tokenReader(expression,tokens);

	rpnConv(tokens,operators,output);

	stack<struct Node*> tree;

	constructTree(output,tree);

	printPostorder(tree.top());

	 // while (!output.empty())
	 // {
	 // 	cout << output.front() << " ";
	 // 	output.pop();
	 // }
	return 0;
}
