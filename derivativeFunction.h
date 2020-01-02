struct Node* polynomial(Node *subtree);

//to_string and stoi functions are not available in g++ 4.8.1 so I created them my self!
string to_stringN(int number){
    string number_string = "";
    char ones_char;
    int ones = 0;
    while(true){
        ones = number % 10;
        switch(ones){
            case 0: ones_char = '0'; break;
            case 1: ones_char = '1'; break;
            case 2: ones_char = '2'; break;
            case 3: ones_char = '3'; break;
            case 4: ones_char = '4'; break;
            case 5: ones_char = '5'; break;
            case 6: ones_char = '6'; break;
            case 7: ones_char = '7'; break;
            case 8: ones_char = '8'; break;
            case 9: ones_char = '9'; break;
        }
        number -= ones;
        number_string = ones_char + number_string;
        if(number == 0){
            break;
        }
        number = number/10;
    }
    return number_string;
}

int stoiN(string number)
{
	int n = 0;
	int j = 1;
	for(int i = number.length() - 1;i >= 0;i--)
	{
		n += j*(number[i] - '0');
		j *= 10;
	}

	return n;
}

struct Node* powerDerv(Node* subtree)
{
	string base = subtree->left->data;

	//Remember to delete
	subtree->left = NULL;

	string power = subtree->right->data;

	string newPower = "";

	
	newPower = to_stringN(stoiN(subtree->right->data) -1);

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
