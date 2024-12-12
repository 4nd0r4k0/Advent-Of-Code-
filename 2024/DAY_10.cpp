/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_10.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:43:39 by andorako          #+#    #+#             */
/*   Updated: 2024/12/12 07:57:27 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>

using namespace std;

void mandatory(vector<string>& M)
{
	int m = M.size(), n = M[0].size();
	vector<vector<bool>> visited(m, vector<bool>(n));
	vector<pair<int, int>> zeros, nines;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] == '0')
				zeros.push_back({i, j});
			else if (M[i][j] == '9')
				nines.push_back({i, j});
		}
	}
	
	function<void(int, int)> dfs = [&](int i, int j)
	{
		if (visited[i][j])
			return ;
		visited[i][j] = true;
		int dirs[] = {-1, 0, 1, 0, -1};
		for (int d = 0; d < 4; d++)
		{
			int nwi = i + dirs[d];
			int nwj = j + dirs[1 + d];
			if (nwi >= 0 && nwi < m && nwj >= 0 && nwj < n && M[nwi][nwj] != '.')
			{
				if (M[nwi][nwj] == M[i][j] + 1)
					dfs(nwi, nwj);
			}
		}
	};
	int count = 0;
	for (auto [i, j] : zeros)
	{
		for (vector<bool>& row : visited)
			fill(begin(row), end(row), false);
		dfs(i, j);
		for (auto [ii, jj] : nines)
			count += visited[ii][jj];
	}
	cout << count << endl;
}

void bonus(vector<string>& M)
{
	int m = M.size(), n = M[0].size();
	vector<vector<int>> dp(m, vector<int>(n));
	vector<pair<int, int>> zeros;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] == '0')
				zeros.push_back({i, j});
		}
	}
	function <int(int, int)> count_path = [&](int i, int j)
	{
		if (dp[i][j] != 0)
			return (dp[i][j]);
		if (M[i][j] == '9')
			return (dp[i][j] = 1);
		int count = 0;
		int dirs[] = {-1, 0, 1, 0, -1};
		for (int d = 0; d < 4; d++)
		{
			int nwi = i + dirs[d];
			int nwj = j + dirs[1 + d];
			if (nwi >= 0 && nwi < m && nwj >= 0 && nwj < n && M[nwi][nwj] != '.')
			{
				if (M[nwi][nwj] == M[i][j] + 1)
					count += count_path(nwi, nwj);
			}
		}
		return (dp[i][j] = count);
	};
	int ans = 0;
	for (auto [i, j] : zeros)
	{
		for (vector<int>& row : dp)
			fill(begin(row), end(row), 0);
		ans += count_path(i, j);
	}
	cout << ans << endl;
}

int main(void)
{
	ifstream file("input.txt");
	string line;
	vector<string> M;
	while (getline(file, line))
		M.push_back(line);
	bonus(M);
	return (0);
}
