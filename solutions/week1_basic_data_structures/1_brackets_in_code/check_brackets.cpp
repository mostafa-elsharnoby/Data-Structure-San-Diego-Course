#include <iostream>
#include <stack>
#include <string>
#include<algorithm>
using namespace std;
struct Bracket {
	Bracket(char type, int position) :
		type(type),
		position(position)
	{}

	bool Matchc(char c) {
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;
};

int main() {
	std::string text;
	getline(std::cin, text);

	stack <char> opening_brackets_stack;
	stack <int> pos;
	for (int position = 0; position < text.length(); ++position) {
		char next = text[position];

		if (next == '(' || next == '[' || next == '{') {
			pos.push(position + 1);
			opening_brackets_stack.push(next);
			// Process opening bracket, write your code here
		}

		if (next == ')' || next == ']' || next == '}') {
			if (!opening_brackets_stack.empty()) {
				if ((next == ']' && opening_brackets_stack.top() == '[') || (next == ')' && opening_brackets_stack.top() == '(') || (next == '}' && opening_brackets_stack.top() == '{'))
				{
					pos.pop();
					opening_brackets_stack.pop();
				}
				else {
					cout << position+1  << endl;
					return 0;
				}
			}
			else {
				cout << position + 1 << endl;
				return 0;
			}
			// Process closing bracket, write your code here
		}
	}
	if (!opening_brackets_stack.empty()) {
		opening_brackets_stack.pop();
		cout << pos.top() << endl;
		return 0;
	}
	// Printing answer, write your code here
	cout << "Success" << endl;
	return 0;
}