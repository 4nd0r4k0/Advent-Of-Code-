/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:19:37 by andorako          #+#    #+#             */
/*   Updated: 2024/12/06 09:27:41 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>

using namespace std;

pair<int, int> get_next_position(int i, int j, char direction)
{
	if (direction == 'U')
		return {i - 1, j};
	else if (direction == 'D')
		return {i + 1, j};
	else if (direction == 'L')
		return {i, j - 1};
	else if (direction == 'R')
		return {i, j + 1};
	else
		return {i, j};
}

char	get_next_direction(char previous_direction)
{
	if (previous_direction == 'U')
		return ('R');
	else if (previous_direction == 'R')
		return ('D');
	else if (previous_direction == 'D')
		return ('L');
	else if (previous_direction == 'L')
		return ('U');
	else
		return (previous_direction);
}

void mandatory(vector<string>& M)
{
	char dir = '$';
	int starti = 0, startj = 0;
	int m = M.size(), n = M[0].size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] != '.' && M[i][j] != '#')
			{
				starti = i;
				startj = j;
				switch (M[i][j])
				{
					case '^': dir = 'U'; break ;
					case 'v': dir = 'D'; break ;
					case '>': dir = 'R'; break ;
					case '<': dir = 'L'; break ;
				}
			}
		}
	}
	set<pair<int, int>> visited;
	set<pair<char, pair<int, int>>> S;
	queue<pair<char, pair<int, int>>> que;
	que.push({dir, {starti, startj}});
	while (!que.empty())
	{
		auto p = que.front();
		que.pop();
		if (S.find(p) != S.end())
			continue ;
		S.insert(p);
		char d = p.first;
		visited.insert(p.second);
		int i = p.second.first, j = p.second.second;
		auto [nwi, nwj] = get_next_position(i, j, d);
		if (nwi >= 0 && nwi < m && nwj >= 0 && nwj < n)
		{
			if (M[nwi][nwj] == '#')
			{
				char new_direction = get_next_direction(d);
				que.push({new_direction, {i, j}});
			}
			else
				que.push({d, {nwi, nwj}});
		}
	}
	cout << (visited.size()) << endl;
}

bool check_loop(vector<string>& M, int i, int j, char direction)
{
	int m = M.size(), n = M[0].size();
	set<pair<char, pair<int, int>>> S;
	queue<pair<char, pair<int, int>>> que;
	que.push({direction, {i, j}});
	while (!que.empty())
	{
		auto p = que.front();
		que.pop();
		if (S.find(p) != S.end())
			return (true);
		S.insert(p);
		char d = p.first;
		int ii = p.second.first, jj = p.second.second;
		auto [nwi, nwj] = get_next_position(ii, jj, d);
		if (nwi >= 0 && nwi < m && nwj >= 0 && nwj < n)
		{
			if (M[nwi][nwj] == '#')
			{
				char new_direction = get_next_direction(d);
				que.push({new_direction, {ii, jj}});
			}
			else
				que.push({d, {nwi, nwj}});
		}
	}
	return (false);
}

void bonus(vector<string>& M)
{
	char dir = '$';
	int starti = 0, startj = 0;
	int m = M.size(), n = M[0].size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] != '.' && M[i][j] != '#')
			{
				starti = i;
				startj = j;
				switch (M[i][j])
				{
					case '^': dir = 'U'; break ;
					case 'v': dir = 'D'; break ;
					case '>': dir = 'R'; break ;
					case '<': dir = 'L'; break ;
				}
			}
		}
	}
	set<pair<int, int>> candidates;
	set<pair<char, pair<int, int>>> S;
	queue<pair<char, pair<int, int>>> que;
	que.push({dir, {starti, startj}});
	while (!que.empty())
	{
		auto p = que.front();
		que.pop();
		if (S.find(p) != S.end())
			continue ;
		S.insert(p);
		char d = p.first;
		candidates.insert(p.second);
		int i = p.second.first, j = p.second.second;
		auto [nwi, nwj] = get_next_position(i, j, d);
		if (nwi >= 0 && nwi < m && nwj >= 0 && nwj < n)
		{
			if (M[nwi][nwj] == '#')
			{
				char new_direction = get_next_direction(d);
				que.push({new_direction, {i, j}});
			}
			else
				que.push({d, {nwi, nwj}});
		}
	}
	long long count = 0;
	candidates.erase({starti, startj});
	for (auto [i, j] : candidates)
	{
		if (M[i][j] == '.')
		{
			M[i][j] = '#';
			count += check_loop(M, starti, startj, dir);
			M[i][j] = '.';
		}
	}
	cout << count << endl;
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