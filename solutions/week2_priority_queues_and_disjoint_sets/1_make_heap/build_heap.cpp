#include<iostream>
#include<vector>
#include<algorithm>
using std::swap;
using namespace std;
class createHeap {
private:
	vector <long long int> vect;
	vector <pair <long long int, long long int> > swapPairs;
	long long int parentIndex(long long int i) { return i / 2; }
	long long int leftChildIndex(long long int i) { return 2 * i; }
	long long int rightChildIndex(long long int i) { return 2 * i + 1; }
	void readData();
	void generateSwaps();
	void downDirection(long long int i);
	void output();
public:
	void solve();
};

void createHeap::readData() {
	long long int size;
	cin >> size;
	vect.push_back(0);
	long long int count = 1;
	while (count <= size) {
		long long int value;
		cin >> value;
		vect.push_back(value);
		count++;
	}
}
void createHeap::downDirection(long long int i) {
	long long int vectSize = vect.size();
	long long int index = i;
	long long int leftChild = leftChildIndex(i);
	long long int rightChild = rightChildIndex(i);
	if (leftChild < vectSize && vect[leftChild] < vect[index]) index = leftChild;
	if (rightChild < vectSize && vect[rightChild] < vect[index]) index = rightChild;
	if (index != i) {
		long long int temp = vect[i];
		vect[i] = vect[index];
		vect[index] = temp;
		swapPairs.push_back(make_pair(i - 1, index - 1));
		downDirection(index);
	}
}
void createHeap::generateSwaps() {
	for (long long int i = vect.size() - 1; i >= 1; i--) {
		downDirection(i);
	}

}
void createHeap::output() {
	cout << swapPairs.size() << endl;
	for (long long int i = 0; i < swapPairs.size(); i++)
		cout << swapPairs[i].first << " " << swapPairs[i].second << endl;
}
void createHeap::solve() {
	readData();
	generateSwaps();
	output();
}
int main(void) {
	createHeap heap;
	heap.solve();
	return 0;
}