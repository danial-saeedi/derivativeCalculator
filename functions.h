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

int charCounter(string s)
{
	int letters = 0;
	for(int i = 0; i < s.length();i++)
	{
		if(is_letter(s.substr(i,1)))
		{
			letters += 1;
		}
		else
		{
			break;
		}
	}

	return letters;
}