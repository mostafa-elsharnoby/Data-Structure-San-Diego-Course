#include <iostream>
#include <string>
#include <vector>
using namespace std;
using std::string;
typedef unsigned long long ull;

struct Data {
	string pattern, text;
};

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

void print_occurrences(const std::vector<int>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		std::cout << output[i] << " ";
	std::cout << "\n";
}
void print_occurrences_special(const std::vector<long long>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		std::cout << output[i] << " ";
	std::cout << "\n";
	//std::cout << "Sharnobyy" << "\n";
}
std::vector<int> get_occurrences(const Data& input) {
	const string& s = input.pattern, t = input.text;
	std::vector<int> ans;
	for (size_t i = 0; i + s.size() <= t.size(); ++i)
		if (t.substr(i, s.size()) == s)
			ans.push_back(i);
	return ans;
}
long long polyHash(string s, long long p, long long x) {
	long long hash = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		hash = (hash*x + s[i]) % p;
	}
	return hash;
}

std::vector<long long> PreComputeHashes(string T, long long P, long long p, long long x) {
	std::vector<long long> H(T.length() - P + 1);
	string S = T.substr(T.length() - P, P);
	H[T.length() - P] = polyHash(S, p, x);
	long long y = 1;
	for (int i = 0; i < P; i++) {
		y = (y*x) % p;
	}
	for (int i = T.length() - P - 1; i >= 0; i--) {
		H[i] = (x * H[i + 1] + T[i] - y * T[i + P]) % p;
	}
	return H;
}


std::vector<long long> RabinKrap(Data input) {
	long long p = 1000000000000000017, x = 1;
	string T = input.text, P = input.pattern;
	std::vector<long long> result, H = PreComputeHashes(T, P.length(), p, x);
	//cout << "=================HHHHH===================" << endl;
	//for (int i = 0; i < H.size(); i++) {
	//	cout << H[i] << endl;
	//}
	long long PHash = polyHash(P, p, x);
	//cout << "PHAshh:	" << PHash << endl;
	for (long long i = 0; i <= T.length() - P.length(); i++) {
		if (PHash != H[i])	continue;
		if (P == T.substr(i, P.length())) {
			result.push_back(i);
		}
	}
	return result;
}
int main() {
	std::ios_base::sync_with_stdio(false);
	Data data = read_input();
	//print_occurrences(get_occurrences(data));
	print_occurrences_special(RabinKrap(data));
	/*
	Data data;
	for (int i = 0; i < 100000; i++)
		data.pattern += 'a';
	for (int i = 0; i < 100000000; i++)
		data.text += 'a';
	get_occurrences(data);
	RabinKrap(data);
	*/
	return 0;
}
