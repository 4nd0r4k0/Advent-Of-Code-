/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_18.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:29:01 by andorako          #+#    #+#             */
/*   Updated: 2024/12/18 10:46:54 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>
#define M 71
#define N 71

using namespace std;

vector<string> m_split(const string& s, const string delim)
{
	vector<string> splitted;
	size_t start = 0, end, dsize = delim.size();
	while ((end = s.find(delim, start)) != string::npos)
	{
		splitted.push_back(s.substr(start, end - start));
		start = end + dsize;
	}
	splitted.push_back(s.substr(start));
	return (splitted);
}

void mandatory(char mp[M][N])
{
	int dirs[] = {-1, 0, 1, 0, -1};
	queue<array<int, 3>> que;
	que.push({0, 0, 0});
	mp[0][0] = 'O';
	while (!que.empty())
	{
		auto [i, j, dist] = que.front();
		que.pop();
		if (i == M - 1 && j == N - 1)
		{
			cout << dist << endl;
			return ;
		}
		for (int d = 0; d < 4; d++)
		{
			int nwi = i + dirs[d];
			int nwj = j + dirs[d + 1];
			if (nwi >= 0 && nwi < M && nwj >= 0 && nwj < N && mp[nwi][nwj] == '.')
			{
				mp[nwi][nwj] = 'O';
				que.push({nwi, nwj, dist + 1});
			}
		}
	}
	cout << "-1\n";
}

bool	test(vector<pair<int, int>>& falls, int times)
{
	vector<vector<char>> mp(M, vector<char>(N, '.'));
	for (int i = 0; i < times; i++)
		mp[falls[i].second][falls[i].first] = '#';
	queue<array<int, 3>> que;
	int dirs[] = {-1, 0, 1, 0, -1};
	que.push({0, 0, 0});
	mp[0][0] = 'O';
	while (!que.empty())
	{
		auto [i, j, dist] = que.front();
		que.pop();
		if (i == M - 1 && j == N - 1)
			return (true);
		for (int d = 0; d < 4; d++)
		{
			int nwi = i + dirs[d];
			int nwj = j + dirs[d + 1];
			if (nwi >= 0 && nwi < M && nwj >= 0 && nwj < N && mp[nwi][nwj] == '.')
			{
				mp[nwi][nwj] = 'O';
				que.push({nwi, nwj, dist + 1});
			}
		}
	}
	return (false);
}

void bonus(vector<pair<int, int>>& falls)
{
	int left = 0, right = falls.size();
	while (left < right)
	{
		int mid = (left + right + 1) / 2;
		if (test(falls, mid))
			left = mid;
		else
			right = mid - 1;
	}
	cout << falls[left].first << "," << falls[left].second << endl;
}

int main(void)
{
	ifstream infile("input.txt");
	string line;
	vector<pair<int, int>> falls;
	int count = 0 ;
	char mp[M][N];
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			mp[i][j] = '.';
	while (getline(infile, line))
	{
		vector<string> coord = m_split(line, ",");
		int x = stoi(coord[0]);
		int y = stoi(coord[1]);
		if (++count <= 1024)
			mp[y][x] = '#';
	}
	mandatory(mp);
/*
	// [ BONUS ]
	vector<pair<int, int>> falls;
	while (getline(infile, line))
	{
		vector<string> coord = m_split(line, ",");
		int x = stoi(coord[0]);
		int y = stoi(coord[1]);
		falls.push_back({x, y});
	}
	bonus(falls); */
}
