/*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
	string type, s;
	size_t ind;
};

class QueryProcessor {
	int bucket_count;
	// store all strings in one vector
	vector<string> elems;
	size_t hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {}

	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}

	void writeSearchResult(bool was_found) const {
		std::cout << (was_found ? "yes\n" : "no\n");
	}

	void processQuery(const Query& query) {
		if (query.type == "check") {
			// use reverse order, because we append strings to the end
			for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
				if (hash_func(elems[i]) == query.ind)
					std::cout << elems[i] << " ";
			std::cout << "\n";
		}
		else {
			vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
			if (query.type == "find")
				writeSearchResult(it != elems.end());
			else if (query.type == "add") {
				if (it == elems.end())
					elems.push_back(query.s);
			}
			else if (query.type == "del") {
				if (it != elems.end())
					elems.erase(it);
			}
		}
	}

	void processQueries() {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQuery(readQuery());
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int bucket_count;
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();
	return 0;
}


*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list> 
#include <iterator> 

using std::string;
using std::vector;
using std::cin;
using namespace std;
struct Query {
	string type, s;
	long long int ind;
};

class QueryProcessor {
	long long int bucket_count;
	// store all strings in one vector
	vector<string> elems;
	vector <list<string>> myList;


	long long int hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (((hash * multiplier + s[i]) % prime) + prime) % prime;
		return ((hash % bucket_count) + bucket_count) % bucket_count;
	}

public:
	explicit QueryProcessor(long long int bucket_count) : bucket_count(bucket_count) {
		myList.resize(bucket_count);
	}

	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}

	void writeSearchResult(bool was_found) const {
		std::cout << (was_found ? "yes\n" : "no\n");
	}

	void processQuery(const Query& query) {
		if (query.type == "check") {
			for (auto it = myList[query.ind].rbegin(); it != myList[query.ind].rend(); ++it)
				cout << *it << " ";
			cout << endl;
		}
		else {
			//vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
			if (query.type == "find") {
				int flag = 0;
				for (auto it = myList[hash_func(query.s)].begin(); it != myList[hash_func(query.s)].end(); ++it) {
					if (*it == query.s) {
						writeSearchResult(true);
						flag = 1;
						break;
					}
				}
				if (flag != 1)	writeSearchResult(false);
			}
			else if (query.type == "add") {
				int flag = 0;
				for (auto it = myList[hash_func(query.s)].begin(); it != myList[hash_func(query.s)].end(); ++it) {
					if (*it == query.s) {
						flag = 1;
						break;
					}
				}
				if (flag != 1) {
					//cout << query.s << " added success" << endl;
					myList[hash_func(query.s)].push_back(query.s);
				}
			}
			else if (query.type == "del") {
				for (auto it = myList[hash_func(query.s)].begin(); it != myList[hash_func(query.s)].end(); ++it) {
					//cout << "Comparison:" << *it << " " << query.s << endl;
					if (*it == query.s) {
						myList[hash_func(query.s)].erase(it);
						//cout << "DONE" << endl;
						break;
					}
				}
			}
		}
	}

	void processQueries() {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQuery(readQuery());
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int bucket_count;
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();
	return 0;
}
