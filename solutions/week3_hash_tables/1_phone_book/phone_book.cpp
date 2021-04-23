#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Query {
	string type, name;
	int number;
};

vector<Query> read_queries() {
	int n;
	cin >> n;
	vector<Query> queries(n);
	for (int i = 0; i < n; ++i) {
		cin >> queries[i].type;
		if (queries[i].type == "add")
			cin >> queries[i].number >> queries[i].name;
		else
			cin >> queries[i].number;
	}
	return queries;
}

void write_responses(const vector<string>& result) {
	for (size_t i = 0; i < result.size(); ++i)
		std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
	vector<string> result;
	// Keep list of all existing (i.e. not deleted yet) contacts.
	vector<Query> contacts;
	map < int, string > mp;
	for (int i = 0; i < queries.size(); ++i) {
		if (queries[i].type == "add") {
			bool was_founded = false;
			// if we already have contact with such number,
			// we should rewrite contact's name
			auto it = mp.find(queries[i].number);
			// otherwise, just add it
			if (it == mp.end()) {
				contacts.push_back(queries[i]);
				//mp[queries[i].number]=contacts[i];
				mp.insert(pair<int, string>(queries[i].number, queries[i].name));
			}
			else {
				mp[queries[i].number] = queries[i].name;
			}
		}
		else if (queries[i].type == "del") {
			mp.erase(queries[i].number);
		}
		else {
			string response = "not found";
			auto it = mp.find(queries[i].number);
			// otherwise, just add it
			if (it == mp.end())
				result.push_back(response);
			else
				result.push_back(mp[queries[i].number]);
		}
	}
	/*
		for (auto itr = mp.begin(); itr != mp.end(); ++itr) {
			cout << itr->first
				<< '\t' << itr->second << '\n';
		}
		*/
	return result;
}

int main() {
	write_responses(process_queries(read_queries()));
	return 0;
}
