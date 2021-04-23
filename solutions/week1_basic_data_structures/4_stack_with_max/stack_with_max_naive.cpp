#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include<map>
#include <iterator> 
using namespace std;
using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;
class StackWithMax {

	vector<int> stack, max;
public:

	void Push(int value) {
		if (stack.empty())	max.push_back(value);
		else {
			if (value > max[max.size() - 1])	max.push_back(value);
			else max.push_back(max[max.size() - 1]);
		}
		stack.push_back(value);
	}

	void Pop() {
		assert(stack.size());
		stack.pop_back();
		max.pop_back();
	}

	int Max() const {
		assert(stack.size());
		return max[max.size() - 1];
	}
};

int main() {
	int num_queries = 0;
	cin >> num_queries;

	string query;
	string value;

	StackWithMax stack;

	for (int i = 0; i < num_queries; ++i) {
		cin >> query;
		if (query == "push") {
			cin >> value;
			stack.Push(std::stoi(value));
		}
		else if (query == "pop") {
			stack.Pop();
		}
		else if (query == "max") {
			cout << stack.Max() << "\n";
		}
		else {
			assert(0);
		}
	}
	return 0;
}