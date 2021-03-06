/*
* Programmer : Danial Saeedi
* Date : 1/19/2020
* Description: This program calculates some basic derivatives.
* Github : https://github.com/danial-saeedi
*/
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <fstream>
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
#include "treeToInfix.h"
#include "derivativeFunction.h"

int main()
{
	//First we read the function in formula.txt 
	ifstream fin;
	fin.open("formula.txt");
	string expression;

	fin >> expression;

	fin.close();

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

	//printPostorder(tree.top());
	polynomial(tree.top());

	cout << tree.top()->data;

	//And Finally,save results in derivative.txt
	ofstream fout;
	fout.open("derivative.txt");
	fout << tree.top()->data;
	fout.close();
	return 0;
}