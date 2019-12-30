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
}

void printPostorder(struct Node* node)
{
    if (node == NULL)
        return; 

    printPostorder(node->left); 
  
    printPostorder(node->right); 

    cout << node->data << " ";
}