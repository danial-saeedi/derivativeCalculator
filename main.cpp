#include <iostream>
#include <queue>
#include <stack>
#include<string>
#include<cstring>
#include <vector>
using namespace std;

//precedence of operators
#define PLUS 1
#define MINUS 1
#define MULTIPLY 2
#define DIVISION 2
#define PARENTHESES 3
#define POWER 4

//Headers
#include "functions.h"
#include "RPNConverter.h"
#include "binaryTree.h"

// struct Node* multiply(Node *subtree)
// {
	
// }

struct Node* polynomial(Node *subtree);

struct Node* powerDerv(Node* subtree)
{
	string base = subtree->left->data;

	//Remember to delete
	subtree->left = NULL;

	string power = subtree->right->data;

	string newPower;

	if(power == "/")
	{
		string numerator = subtree->right->left->data;
		string denominator = subtree->right->right->data;

		newPower = to_string(stoi(numerator)-stoi(denominator))  + "/" +  denominator;

		power = numerator+ "/" + denominator;
	}else{
		newPower = to_string(stoi(subtree->right->data) -1);
	}

	//Remember to delete
	subtree->right = NULL;

	subtree->data = "(" + power + ")" + base + "^" +"("+newPower+")";

	return subtree;
};

struct Node* multiplyDerv(Node* subtree)
{
	polynomial(subtree->right);
	subtree->data = subtree->left->data + "*" +subtree->right->data;

	//Remember to delete
	subtree->left = NULL;
	subtree->right = NULL;

	return subtree;
};

struct Node* polynomial(Node *subtree)
{
	if(subtree->data == "+" || subtree->data == "-")
	{
		subtree->left = polynomial(subtree->left);
		subtree->right = polynomial(subtree->right);

		subtree->data = subtree->left->data + subtree->data + subtree->right->data;

		return subtree;
	}
	else if(subtree->data == "^")
	{
		return powerDerv(subtree);
	}
	else if(subtree->data == "*")
	{
		return multiplyDerv(subtree);
	}else if(is_letter(subtree->data))
	{
		subtree->data = "1";

		return subtree;
	}else if(is_number(subtree->data))
	{
		subtree->data = "0";

		return subtree;
	}

	return 0;
};

int main()
{
	string expression = "5*(x)^(2/6)-(x)^(5/2)+(x)^(4)-(x)^(9)+2*x^8";

	vector<string> tokens;
	stack<string> operators;

	//This queue contains postfix notation of given expression
	queue<string> output;

	/*
	We split the expression into smaller parts(tokens)
	For example : (x)^(2)

	{"(","x", ")", "^","(", "2", ")"}
	*/
	tokenReader(expression,tokens);

	//And then we convert the infix form into postfix notation
	rpnConv(tokens,operators,output);

	stack<struct Node*> tree;

	//And then we will convert postfix into expresion tree
	constructTree(output,tree);


	Node *copyOfTree = tree.top();

	polynomial(copyOfTree);

	cout << copyOfTree->data;
	return 0;
}
