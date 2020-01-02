
/*postorder traversal. */
void infixConverter(struct Node* subtree,stack<string> &infix)
{
    if (subtree == NULL)
        return;

    infixConverter(subtree->left,infix); 
  
    infixConverter(subtree->right,infix); 

    if(subtree->data == "^")
    {
		string left = subtree->left->data;
		string right = subtree->right->data;

		infix.push(left + subtree->data + right);
    }
    else if(subtree->data == "+" || subtree->data == "*" || subtree->data == "/")
    {
		string right = infix.top();
		infix.pop();
		string left = infix.top();
		infix.pop();

		if(subtree->data == "/")
		{
			left  = "("+left +")";
			right = "("+right+")";
		}

		infix.push(left + subtree->data + right);
    }else{
    	infix.push(subtree->data);	
    }
}
