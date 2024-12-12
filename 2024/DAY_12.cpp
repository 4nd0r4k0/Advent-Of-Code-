/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_12.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:03:45 by andorako          #+#    #+#             */
/*   Updated: 2024/12/12 09:15:29 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>

using namespace std;

long long calculate_score(vector<string>& M, vector<vector<bool>>& visited, int y, int x, char c)
{
	int dirs[] = {-1, 0, 1, 0, -1};
	long long perimeter = 0, area = 0;
	int m = M.size(), n = M[0].size();
	queue<pair<int, int>> que;
	visited[y][x] = true;
	que.push({y, x});
	while (!que.empty())
	{
		auto [i, j] = que.front();
		que.pop();
		area++;
		for (int d = 0; d < 4; d++)
		{
			int nwi = i + dirs[d];
			int nwj = j + dirs[1 + d];
			if (nwi >= 0 && nwi < m && nwj >= 0 && nwj < n && M[nwi][nwj] == c)
			{
				if (!visited[nwi][nwj])
				{
					visited[nwi][nwj] = true;
					que.push({nwi, nwj});
				}
			}
			else
				perimeter++;
		}
	}
	return (area * perimeter);
}

void mandatory(vector<string>& M)
{
	long long score = 0;
	int m = M.size(), n = M[0].size();
	vector<vector<bool>> visited(m, vector<bool>(n, false));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!visited[i][j])
			{
				score += calculate_score(M, visited, i, j, M[i][j]);
			}
		}
	}
	cout << score << endl;
}

long long b_calculate_score(vector<string>& M, vector<vector<bool>>& visited, int y, int x, char c)
{
	long long area = 0, sides = 0;
	int dirs[] = {-1, 0, 1, 0, -1};
	map<pair<int, int>, vector<int>> vertical;
	map<pair<int, int>, vector<int>> horizontal;
	int m = M.size(), n = M[0].size();
	queue<pair<int, int>> que;
	visited[y][x] = true;
	que.push({y, x});
	while (!que.empty())
	{
		auto [i, j] = que.front();
		que.pop();
		area++;
		for (int d = 0; d < 4; d++)
		{
			int nwi = i + dirs[d];
			int nwj = j + dirs[1 + d];
			if (nwi >= 0 && nwi < m && nwj >= 0 && nwj < n && M[nwi][nwj] == c)
			{
				if (!visited[nwi][nwj])
				{
					visited[nwi][nwj] = true;
					que.push({nwi, nwj});
				}
			}
			else
			{
				if (nwi == i - 1 || nwi == i + 1)
					horizontal[{i, nwi}].push_back(j);
				else
					vertical[{j, nwj}].push_back(i);
			}
		}
	}
	for (auto& p : horizontal)
	{
		vector<int>& coords = p.second;
		sort(begin(coords), end(coords));
		for (int i = 0, j; i < (int) coords.size();)
		{
			sides++;
			j = i + 1;
			while (j < (int) coords.size() && coords[j] == coords[j - 1] + 1)
				j++;
			i = j;
		}
	}
	for (auto& p : vertical)
	{
		vector<int>& coords = p.second;
		sort(begin(coords), end(coords));
		for (int i = 0, j; i < (int) coords.size();)
		{
			sides++;
			j = i + 1;
			while (j < (int) coords.size() && coords[j] == coords[j - 1] + 1)
				j++;
			i = j;
		}
	}
	return (area * sides);
}

void bonus(vector<string>& M)
{
	long long score = 0;
	int m = M.size(), n = M[0].size();
	vector<vector<bool>> visited(m, vector<bool>(n, false));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!visited[i][j])
			{
				score += b_calculate_score(M, visited, i, j, M[i][j]);
			}
		}
	}
	cout << score << endl;
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

