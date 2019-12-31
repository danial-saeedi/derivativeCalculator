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

struct Node* divideDerv(Node* subtree)
{
	
	stack<string> leftInfix;
	stack<string> rightInfix;
	infixConverter(subtree->left,leftInfix);
	infixConverter(subtree->right,rightInfix);

	polynomial(subtree->left);
	polynomial(subtree->right);

	subtree->data = 
	"((" + subtree->left->data + ")*(" + rightInfix.top() + ")-" +

	"(" + subtree->right->data + ")*(" + leftInfix.top() + "))" +

	"/(" + rightInfix.top() + ")^2"
	 ;
	return subtree;
}

struct Node* functionDerv(Node* subtree)
{
	string functionName;
	int chars = charCounter(subtree->data);
	functionName = (subtree->data).substr(0,chars);

	string u = (subtree->data).substr(chars+1,(subtree->data).length()-(chars+2));

	vector<string> tokens;
	stack<string> operators;
	queue<string> output;
	tokenReader(u,tokens);
	//And then we convert the infix form into postfix notation
	rpnConv(tokens,operators,output);

	stack<struct Node*> newTree;

	//And then we will convert postfix into expresion tree
	constructTree(output,newTree);

	polynomial(newTree.top());

	if(functionName == "sin"){
		subtree->data = "(" + newTree.top()->data + ")cos("+ u +")";

	}

	else if(functionName == "cos"){
		subtree->data = "(-1)*(" + newTree.top()->data + ")sin("+ u +")";
	}

	return 0;

}

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
	}
	else if(subtree->data == "/")
	{
		return divideDerv(subtree);
	}
	else if(!is_number(subtree->data) && (subtree->data).size() > 1)
	{
		functionDerv(subtree);
		return subtree;
	}
	else if(is_letter(subtree->data))
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