#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
class JobQueue {
private:
	priority_queue<int, vector<int>, greater<int> > gquiz;
	int num_workers_;
	vector<int> jobs_;

	vector<int> assigned_workers_;
	vector<long long> start_times_;

	void WriteResponse() const {
		for (int i = 0; i < jobs_.size(); ++i) {
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData() {
		int m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}
	typedef pair<long long, long long> pi;
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	void AssignJobsSharnoby() {
		for (int i = 0; i < num_workers_; i++) {
			pq.push(make_pair(0, i));
		}
		for (int i = 0; i < jobs_.size(); i++) {
			pair<long long, long long > top = pq.top();
			cout << top.second << " " << top.first << endl;
			top.first += jobs_[i];
			pq.pop();
			pq.push(top);
		}
	}
	void AssignJobs() {
		// TODO: replace this code with a faster algorithm.
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		vector<long long> next_free_time(num_workers_, 0);
		for (int i = 0; i < jobs_.size(); ++i) {
			int duration = jobs_[i];
			int next_worker = 0;
			for (int j = 0; j < num_workers_; ++j) {
				if (next_free_time[j] < next_free_time[next_worker])
					next_worker = j;
			}
			assigned_workers_[i] = next_worker;
			start_times_[i] = next_free_time[next_worker];
			next_free_time[next_worker] += duration;
		}
	}

public:
	void Solve() {
		ReadData();
		AssignJobsSharnoby();
		//WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	return 0;
}
