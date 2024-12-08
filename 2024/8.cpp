#include <bits/stdc++.h>

using namespace std;

void mandatory(vector<string>& M)
{
	map<char, vector<pair<int, int>>> antennas;
	int m = M.size(), n = M[0].size();
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (M[i][j] != '.')
				antennas[M[i][j]].push_back({i, j});
	for (auto p : antennas)
	{
		vector<pair<int, int>>& vec = p.second;
		int A = vec.size();
		for (int i = 0; i < A; i++)
		{
			for (int j = i + 1; j < A; j++)
			{
				if (vec[i].first == vec[j].first)
				{
					int minx = min(vec[i].second, vec[j].second);
					int maxx = max(vec[i].second, vec[j].second);
					if (2 * minx >= maxx && 2 * minx - maxx < n)
						M[vec[i].first][2 * minx - maxx] = '#';
					if (2 * maxx >= minx && 2 * maxx - minx < n)
						M[vec[i].first][2 * maxx - minx] = '#';
				}
				else if (vec[i].second == vec[j].second)
				{
					int miny = min(vec[i].second, vec[j].second);
					int maxy = max(vec[i].second, vec[j].second);
					if (2 * miny >= maxy && 2 * miny - maxy < m)
						M[2 * miny - maxy][vec[i].second] = '#';
					if (2 * maxy >= miny && 2 * maxy - miny < m)
						M[2 * maxy - miny][vec[i].first] = '#';	
				}
				else
				{
					pair<int, int> p = vec[i], t = vec[j];
					if (p.second > t.second)
						swap(p, t);
					int ai = 2 * p.first - t.first;
					int bi = 2 * t.first - p.first;
					int aj = 2 * p.second - t.second;
					int bj = 2 * t.second - p.second;
					if (ai >= 0 && ai < m && aj >= 0 && aj < n)
						M[ai][aj] = '#';
					if (bi >= 0 && bi < m && bj >= 0 && bj < n)
						M[bi][bj] = '#';
				}
			}
		}
	}
	int ans = 0;
	for (string& v : M)
		for (char c : v)
			if (c == '#')
				ans++;
	cout << ans << endl;
}

int main(void)
{
	ifstream file("input.txt");
	string line;
	vector<string> M;
	while (getline(file, line))
		M.push_back(line);
	mandatory(M);
	return (0);
}
