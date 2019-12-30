//this function tells us the precedence of an operator
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

	return 0;
}

//this function split out expression into tokens
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

/*
* RPN stands for reverse polish notation
* This function will convert infix notation into postfix notation
*/
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