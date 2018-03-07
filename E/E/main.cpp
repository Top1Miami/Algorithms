#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
/*struct dub{
int v;
int w;
};*/
//std::vector<int> w;
std::vector<int> p;
std::vector<int> d;
std::vector<std::vector<int> > dp;
std::vector<std::vector<int> > graph;
int main_v, timer = 0;
int n;
std::vector<int> tst, tfin;
void dfs(int v, int p) {
	timer++;
	d[v] = d[p] + 1;
	dp[v][0] = p;
	tst[v] = timer;
	for (int i = 1; i < log2(n) + 1; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
	for (int i = 0; i < graph[v].size(); i++) {
		if (graph[v][i] != p) {
			dfs(graph[v][i], v);
		}
	}
	timer++;
	tfin[v] = timer;
}

int lca(int a, int b) {
	if (tfin[a] >= tfin[b] && tst[a] <= tst[b]) {
		return a;
	}
	if (tfin[b] >= tfin[a] && tst[b] <= tst[a]) {
		return b;
	}
	for (int j = log2(n); j >= 0; j--) {
			if (!(tfin[dp[a][j]] >= tfin[b] && tst[dp[a][j]] <= tst[b])) {
				a = dp[a][j];
			}
		}
	return dp[a][0];
}

int main() {
	std::ifstream inFi("dynamic.in");
	std::ofstream outFi("dynamic.out");
	inFi >> n;
	while (n != 0) {
		//std::cin >> n;
		//std::cout << (int)log2(n);
		dp.assign(n,std::vector<int>());
		d.assign(n, -1);
		tst.assign(n, 0);
		tfin.assign(n, 0);
		graph.assign(n, std::vector<int>());
		for (int j = 0; j < n; j++) {
			dp[j].assign(17,0);
		}
		for (int i = 0; i < n - 1; i++) {
			int a, b, c;
			//std::cin >> a >> b;
			inFi >> a >> b;
			a--;
			b--;
			//p.push_back(a - 1);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		dfs(0, 0);
		/*for (int i = 0; i < n; i++) {
		std::cout << d[i] << std::endl;
		}*/

		main_v = 0;
		/*for (int i = 1; i < n; i++) {
		d.push_back(d[p[i]] + 1);
		}*/
		/*for (int i = 0; i < n; i++) {
		dp[i][0] = p[i];
		}
		for (int i = 1; i < n; i++) {
		for (int j = 1; j < 19; j++) {
		dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
		}*/
		int m;
		//std::cin >> m;
		inFi >> m;
		for (int i = 0; i < m; i++) {
			int a, b;
			char c;
			//inFi >> a >> b;
			//std::cin >> c;
			//inFi >> a >> b;
			inFi >> c;
			if (c == '?') {
				//std::cout << 1;
				int res1 = 0, res2 = 0, res3 = 0;
				inFi >> a >> b;
				a--;
				b--;
				res1 = lca(a, b);
				res2 = lca(a, main_v);
				res3 = lca(main_v, b);
				int res = res1;
				if (d[res2] > d[res]) res = res2;
				if (d[res3] > d[res]) res = res3;
				outFi << res + 1 << std::endl;
			}
			else if (c == '!') {
				inFi >> a;
				main_v = a - 1;
			}
			//std::cout << w[st] + w[b] - 2*w[res] << std::endl;
			//std::cout;
			//outFi << p[a] + 1 << std::endl;
		}
		inFi >> n;
		d.clear();
		dp.clear();
		tst.clear();
		tfin.clear();
		graph.clear();
		timer = 0;
	}
	
	//system("pause");

	return 0;
}
