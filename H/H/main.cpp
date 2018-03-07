#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

std::vector<int> d;
std::vector<int> p;
int depth_not_it(int main_v, int v) {
	if (d[v] == INT_MIN) {
		d[v] = (d[p[v]] == INT_MIN) ? depth_not_it(main_v, p[v]) : d[p[v]] + 1;
	}
	return d[v];
}

int main() {
	std::ifstream inFi("ancestor.in");
	std::ofstream outFi("ancestor.out");
	int n;
	int main_v;
	inFi >> n;
	std::vector<std::vector<int> > dp;
	dp.resize(n);
	p.resize(n);
	d.assign(n, INT_MIN);
	for (int i = 0; i < n; i++) {
		int a;
		inFi >> a;
		if (a == 0) {
			p[i] = i;
			main_v = p[i];
		} else {
			p[i] = a - 1;
		}
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < 19; i++) {
			dp[j].push_back(main_v);
		}
	}
	d[main_v] = 0;
	for (int i = 0; i < n; i++) {
		depth_not_it(main_v, i);
	}

	//std::cout << std::endl;
	for (int i = 0; i < n; i++) {
		dp[i][0] = p[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < 19; j++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}
	int m;
	inFi >> m;
	//std::cout << m << std::endl;
	for (int i = 0; i < m; i++) {
		int a, b;
		inFi >> a >> b;
		a--;
		b--;
		if (d[a] > d[b]) {
			outFi << 0 << std::endl;
			continue;
		}
		for (int j = log2(p.size()); j >= 0; j--) {
			if (d[dp[b][j]] >= d[a]) {
				b = dp[b][j];
			}
		}
		if (a == b) {
			outFi << 1 << std::endl;
			continue;
		}
		int st = a;
		for (int j = log2(p.size()); j >= 0; j--) {
			if (dp[a][j] != dp[b][j]) {
				a = dp[a][j];
				b = dp[b][j];
			}
		}
		if (st == p[b]) outFi << 1 << std::endl;
		else outFi << 0 << std::endl;
	}
	//system("pause");
	return 0;
}