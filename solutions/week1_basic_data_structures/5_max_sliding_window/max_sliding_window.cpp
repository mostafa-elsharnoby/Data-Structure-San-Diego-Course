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

	void clear() {
		stack.clear();
	}
	bool empty() {
		if (stack.empty())	return true;
		else return false;
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

void max_sliding_window_naive(vector<int> const & A, int w) {
	if (A.size() == 1) { cout << A[0] << endl; return; }
	if (w == 1) {
		for (int i = 0; i < A.size(); i++) {
			cout << A[i] << " ";
		}
		cout << endl;
		return;
	}
	StackWithMax front, back;
	for (int i = 0; i < w; ++i) {
		front.Push(A[i]);
		//cout << i << "	";
	}
	//cout << endl;
	cout << front.Max() << " ";
	for (int i = w - 1; i >= 0; i--) { //cout << i << "	";
		back.Push(A[i]);
	}
	//cout << endl;
	front.clear();
	for (int i = w; i < A.size(); ++i) {
		if (back.empty()) {
			for (int j = i; j > i - w; j--) {
				//cout << "A[i] is:" << A[i] << "	";
				back.Push(A[j]);
			}
			//cout << endl;
			front.clear();
			cout << back.Max() << " ";
		}
		else {
			front.Push(A[i]);
			back.Pop();
			if (!back.empty())cout << max(front.Max(), back.Max()) << " ";
			else cout << front.Max() << " ";
		}
	}
}

int main() {
	int n = 0;
	cin >> n;

	vector<int> A(n);
	for (size_t i = 0; i < n; ++i)
		cin >> A.at(i);

	int w = 0;
	cin >> w;

	max_sliding_window_naive(A, w);

	return 0;
}