#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>


int main() {
	std::ifstream inFi("minonpath.in");
	std::ofstream outFi("minonpath.out");
	int n;
	inFi >> n;
	std::vector<int> p;
	std::vector<int> d;
	std::vector<int> wt;
	std::vector<std::vector<int> > dp, wtp;
	dp.resize(n);
	wtp.resize(n);
	p.push_back(0);
	d.push_back(0);
	wt.push_back(INT_MAX);
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < 19; i++) {
			dp[j].push_back(0);
			wtp[j].push_back(INT_MAX);
		}
	}
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		inFi >> a >> b;
		p.push_back(a - 1);
		wt.push_back(b);
	}

	for (int i = 1; i < n; i++) {
		d.push_back(d[p[i]] + 1);
	}

	for (int i = 1; i < n; i++) {
		dp[i][0] = p[i];
		wtp[i][0] = wt[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < 19; j++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
			wtp[i][j] = std::min(wtp[dp[i][j - 1]][j - 1],wtp[i][j - 1]);
		}
	}

	int m;
	inFi >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		inFi >> a >> b;
		a--;
		b--;
		if (d[a] > d[b]) {
			int t = a;
			a = b;
			b = t;
		}
		int min_s = INT_MAX;
		for (int j = log2(p.size()); j >= 0; j--) {
			if (d[dp[b][j]] >= d[a]) {
				//min_s = (wtp[b][j] < min_s) ? wtp[b][j] : min_s;
				if (wtp[b][j] < min_s) {
					min_s = wtp[b][j];
				}
				b = dp[b][j];
			}
		}
		if (a == b) {
			outFi << min_s << std::endl;
			continue;
		}
		for (int j = log2(p.size()); j >= 0; j--) {
			if (dp[a][j] != dp[b][j]) {
				//min_s = (wtp[a][j] < min_s) ? wtp[a][j] : min_s;
				if (wtp[a][j] < min_s) {
					min_s = wtp[a][j];
				}
				a = dp[a][j];
				//min_s = (wtp[b][j] < min_s) ? wtp[b][j] : min_s;
				if (wtp[b][j] < min_s) {
					min_s = wtp[b][j];
				}
				b = dp[b][j];
			}
		}
		outFi << std::min(min_s,std::min(wt[a],wt[b])) << std::endl;
	}
	//system("pause");

	return 0;
}