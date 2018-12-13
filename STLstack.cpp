//         Course: CS3420 Data Structures
//           Name: Ulikowski, David
//     Assignment: Programming 9.1
//  Date assigned: 3/28/18
//		 Date due: 4/3/18
// Date handed in: 4/3/18
//         Remark: Program that uses STL stack to check for palindrome

#include <iostream>
#include <string>
#include <stack>

using namespace std;

string inputString();
// prompts user to enter a phrase

void removeEmbeddedSpaces(string& str);
// removes all spaces in the input string
// Precondition: Must be a string
// Postcondition: All spaces are removed from string

void convertInfixToPostfix(string& str);
// converts an infix expression to its corresponding postfix expression
// Precondition: 
// Postcondition: expression is converted to postfix expression

string inputString()
{
	string str;

	cout << "Enter an arithmetic expression" << endl;
	getline(cin, str);

	return str;
}

void removeEmbeddedSpaces(string& str)
{
	// eliminates spaces in string
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
		{
			str.erase(i, 1);
			i--;
		}
	}

	cout << str << endl;
}

int priority(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

void convertInfixToPostfix(string& str)
{
	stack<char> stk;
	stk.push('N');
	string newStr;

	// iterate through expression
	for (int i = 0; i < str.length(); i++)
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		{
			newStr += str[i];	// copy expression chars ('a' - 'z' or 'A' - 'Z' to newStr)
		}

		// if come across '(' push onto stack
		else if (str[i] == '(')
		{
			stk.push('(');
		}
		else if (str[i] == ')')
		{
			while (stk.top() != 'N' && stk.top() != '(')
			{
				char c = stk.top();
				stk.pop();
				newStr += c;
			}
			if (stk.top() == '(')
			{
				char c = stk.top();
				stk.pop();
			}
		}
		else
		{
			while (stk.top() != 'N' && priority(str[i]) <= priority(stk.top()))
			{
				char c = stk.top();
				stk.pop();
				newStr += c;
			}
			stk.push(str[i]);
		}
	}

	while (stk.top() != 'N')
	{
		char c = stk.top();
		stk.pop();
		newStr += c;
	}

	cout << "The corresponding postix is: " << newStr << endl;
}

int main()
{
	string arithExpression;
	arithExpression = inputString();

	cout << "\nAfter removing embedded spaces, infix expression becomes: " << endl;
	removeEmbeddedSpaces(arithExpression);

	convertInfixToPostfix(arithExpression);

	return 0;
}


/*void convert2lower(string& userString);
// removes punctuation and blank characters in the string and converts
// all alphabets in the string to lowercase
// Precondition: User must input string of characters
// Postcondition: removes punctuation and blank characters and converts
//				  all alphabets to lower case

bool isPalindrome(const string& userString);
// checks converted string and returns true or false depending on if the
// string is a palindrome or is not
// Precondition: String must be converted to lower
// Postcondition: Returns true or false

string inputString()
{
	string userString;

	cout << "Enter a word, phrase, or a sentence to see if it's a palindrome." << endl;
	getline(cin, userString);

	return userString;
}
void convert2lower(string& userString)
{
	// eliminates spaces in string
	for (int i = 0; i < userString.length(); i++)
	{
		if (userString[i] == ' ' || userString[i] == '\n' || userString[i] == '\t')
		{
			userString.erase(i, 1);
			i--;
		}
	}

	// remove special characters
	for (int i = 0; i < userString.length(); i++)
	{
		if (!((userString[i] >= 'a' && userString[i] <= 'z') || (userString[i] >= 'A' && userString[i] <= 'Z')))
		{
			userString[i] = '\0';
		}
	
	// converts to all lower-case
		userString[i] = tolower(userString[i]);
	}


}

bool isPalindrome(const string& userString)
{
	int n = userString.size();
	stack<char> c;

	for (int i = 0; i < n / 2; i++)
	{
		c.push(userString[i]);
	}

	for (int i = (n + 1) / 2; i < n; i++)
	{
		if (c.top() != userString[i])
		{
			return false;
		}

		c.pop();

	}

	return true;
}

int main()
{
	string palindrome;
	palindrome = inputString();

	cout << "\nThe oringinal input string contains:" << endl;
	cout << palindrome << endl;

	convert2lower(palindrome);

	if (isPalindrome(palindrome) != true)
	{
		cout << "\nThe phrase '" << palindrome << "' is not a palindrome!" << endl << endl;
	}
	else
	{
		cout << "\nThe phrase '" << palindrome << "' is a palindrome!" << endl << endl;
	}

	return 0;
}*/
