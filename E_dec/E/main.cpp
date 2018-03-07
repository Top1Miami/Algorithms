#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
std::vector<std::vector<int> > graph;
std::vector<int> answer;

std::bitset<200000> usedInDec(0);
int dfs(int v, int par, int* cToRec, int size) {
	int sum = 0;
	for (int i = 0; i < graph[v].size(); i++) {
		if (graph[v][i] != par && !usedInDec[graph[v][i]]) {
			sum += dfs(graph[v][i], v, cToRec, size);
		}
	}
	sum++;
	if (sum * 2 >= size || par == -1) {
		//std::cout << v << std::endl;
		*cToRec = *cToRec == -1 ? v : *cToRec;
	}
	return sum;
}
/*
@(ЗАПУСКАЕМ)
░ГУСЯ░▄▀▀▀▄░РАБОТЯГИ░░
▄███▀░◐░░░▌░░░░░░░
░░░░▌░░░░░▐░░░░░░░
░░░░▐░░░░░▐░░░░░░░
░░░░▌░░░░░▐▄▄░░░░░
░░░░▌░░░░▄▀▒▒▀▀▀▀▄
░░░▐░░░░▐▒▒▒▒▒▒▒▒▀▀▄
░░░▐░░░░▐▄▒▒▒▒▒▒▒▒▒▒▀▄
░░░░▀▄░░░░▀▄▒▒▒▒▒▒▒▒▒▒▀▄
░░░░░░▀▄▄▄▄▄█▄▄▄▄▄▄▄▄▄▄▄▀▄
░░░░░░░░░░░▌▌░▌▌░░░░░
░░░░░░░░░░░▌▌░▌▌░░░░░
░░░░░░░░░▄▄▌▌▄▌▌░░░░░

*/
int recursive(int v, int prevC, int size) {
	int center = -1;
	int * p = &center;
	/*for (int i = 0; i < n; i++) {
		std::cout << answer[i] + 1 << " ";
	}*/
	dfs(v, -1, p, size);
	usedInDec[*p] = 1;
	answer[*p] = prevC;
	for (int i = 0; i < graph[*p].size(); i++) {
		if (!usedInDec[graph[*p][i]]) {
			recursive(graph[*p][i], *p, size/2);
		}
	}
	return 0;
}



int main() {
	int n;
	std::cin >> n;
	answer.assign(n, 0);
	graph.assign(n, std::vector<int>());
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		std::cin >> a >> b;
		graph[--a].push_back(--b);
		graph[b].push_back(a);
	}
	recursive(0, -1, n);
	for (int i = 0; i < n; i++) {
		std::cout << answer[i] + 1 << " ";
	}
	system("pause");
	return 0;
}