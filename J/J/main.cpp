#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#define alph 27
using namespace std;

pair<vector<int>, vector<int>> get_mass(string s) {
	s += '$';
	int sz = s.size();
	int tt = max(sz, alph);
	vector<int> cnt_pos(tt, 0);
	vector<int> sdv(sz, 0);
	sdv[0] = 1;
	for (int i = 1; i < sz; i++) {
		sdv[i] = sdv[i - 1] * 2;
	}
	//1st rad sort
	for (int i = 0; i < sz; i++) {
		if (s[i] != '$')
			cnt_pos[s[i]- 96]++;
		else cnt_pos[0]++;
	}
	int temp = cnt_pos[0];
	for (int i = 1; i < alph; i++) {
		cnt_pos[i] += temp;
		temp = cnt_pos[i];
	}
	vector<int> sup_pos(sz, 0);
	for (int i = 0; i < sz; i++) {
		if (s[i] != '$') {
			cnt_pos[s[i] - 96]--;
			sup_pos[cnt_pos[s[i] - 96]] = i;
		}
		else {
			cnt_pos[0]--;
			sup_pos[cnt_pos[0]] = i;
		}
	}
	vector<int> comp(sz, 0);
	comp[sup_pos[0]] = 0;
	int dif = 1;
	for (int i = 0; i < sz - 1; i++) {
		if (s[sup_pos[i]] != s[sup_pos[i + 1]]) {
			dif++;
		}
		comp[sup_pos[i + 1]] = dif - 1;
	}
	//1st rad sort
	//rad sort
	vector<int> sp_t(sz, 0), cm_t(sz, 0);
	for (int i = 0; sdv[i] < sz; i++) {
		vector<int> cnt_t(tt, 0);
		for (int j = 0; j < sz; j++) {
			sp_t[j] = (sup_pos[j] - sdv[i] < 0) ? sup_pos[j] - sdv[i] + sz : sup_pos[j] - sdv[i];
		}
		for (int j = 0; j < sz; j++) {
			cnt_t[comp[sp_t[j]]]++;
		}
		int temp1 = cnt_t[0];
		for (int j = 1; j < dif; j++) {
			cnt_t[j] += temp1;
			temp1 = cnt_t[j];
		}
		for (int j = sz - 1; j >= 0; j--) {
			int temp2 = --cnt_t[comp[sp_t[j]]];
			sup_pos[temp2] = sp_t[j];
		}
		cm_t[sup_pos[0]] = 0;
		dif = 1;
		for (int j = 1; j < sz; j++) {
			int predp_l = (sup_pos[j] + sdv[i]) % sz;
			int predp_r = (sup_pos[j - 1] + sdv[i]) % sz;
			//cout << sup_pos[j] << " " << sup_pos[j - 1] << endl;
			if (comp[predp_l] != comp[predp_r] || comp[j] != comp[j - 1]) {
				dif++;
			}
			cm_t[sup_pos[j]] = dif - 1;
		}
		for (int j = 0; j < cm_t.size(); j++) {
			comp[j] = cm_t[j];
		}
	}
	//rad sort
	return make_pair(sup_pos, comp);
}


int main() {
	string s;
	ifstream inFi("array.in");
	ofstream outFi("array.out");
	inFi >> s;
	pair<vector<int>, vector<int>> s_mass = get_mass(s);
	for (int i = 0; i < s_mass.first.size(); i++) {
		cout << s_mass.first[i] + 1<< " ";
	}
	pair<vector<int>, vector<int>> duplic = s_mass;
	
	
	system("pause");
	return 0;
}