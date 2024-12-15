/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_15.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:44:34 by andorako          #+#    #+#             */
/*   Updated: 2024/12/15 11:44:34 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

pair<int, int> get_position(vector<string>& mp)
{
	int m = mp.size(), n = mp[0].size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (mp[i][j] == '@')
				return {i , j};
		}
	}
	return {-1, -1};
}

void mandatory(vector<string>& mp, string& path)
{
	auto p = get_position(mp);
	int i = p.first, j = p.second;
	int di, dj;
	for (char c : path)
	{
		if (c == '^' || c == 'v')
		{
			int ii = i;
			di = (c == '^') ? -1 : 1;
			while (mp[ii + di][j] == 'O')
				ii += di;
			if (mp[ii + di][j] != '#')
			{
				swap(mp[ii + di][j], mp[i + di][j]);
				mp[i + di][j] = '@';
				mp[i][j] = '.';
				i += di;
			}
		}
		else if (c == '<' || c == '>')
		{
			int jj = j;
			dj = (c == '<') ? -1 : 1;
			while (mp[i][jj + dj] == 'O')
				jj += dj;
			if (mp[i][jj + dj] != '#')
			{
				swap(mp[i][jj + dj], mp[i][j + dj]);
				mp[i][j + dj] = '@';
				mp[i][j] = '.';
				j += dj;
			}
		}
	}
	ll ans = 0;
	int m = mp.size(), n = mp[0].size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			if (mp[i][j] == 'O')
				ans += 100 * i + j;
	}
	cout << ans << endl;
}

int move_vertical(vector<string>& mp, int i, int j, int di)
{
	queue<pair<int, int>> que;
	set<pair<int, int>> marked;
	if (mp[i + di][j] == '[')
	{
		que.push({i + di, j});
		que.push({i + di, j + 1});
	}
	else if (mp[i + di][j] == ']')
	{
		que.push({i + di, j});
		que.push({i + di, j - 1});
	}
	vector<vector<pair<int, int>>> level;
	while (!que.empty())
	{
		int Q = que.size();
		vector<pair<int, int>> l;
		while (Q-- > 0)
		{
			auto p = que.front();
			que.pop();
			int ni = p.first, nj = p.second;
			if (mp[ni + di][nj] == '#')
				return (0);
			l.push_back({ni, nj});
			if (mp[ni + di][nj] == '.')
				continue ;
			if (mp[ni + di][nj] == '[')
			{
				if (marked.find({ni + di, nj}) == marked.end() && marked.find({ni + di, nj + 1}) == marked.end())
				{
					marked.insert({ni + di, nj});
					marked.insert({ni + di, nj + 1});
					que.push({ni + di, nj});
					que.push({ni + di, nj + 1});
				}
			}
			else if (mp[ni + di][nj] == ']')
			{
				if (marked.find({ni + di, nj}) == marked.end() && marked.find({ni + di, nj - 1}) == marked.end())
				{
					marked.insert({ni + di, nj});
					marked.insert({ni + di, nj - 1});
					que.push({ni + di, nj});
					que.push({ni + di, nj - 1});
				}		
			}
		}
		if (!l.empty())
			level.push_back(l);
	}
	reverse(begin(level), end(level));
	for (vector<pair<int, int>>& l : level)
	{
		sort(begin(l), end(l));
		for (int i = 0; i < (int) l.size(); i += 2)
		{
			mp[l[i].first][l[i].second] = '.';
			mp[l[i].first][l[i].second + 1] = '.';
			mp[l[i].first + di][l[i].second] = '[';
			mp[l[i].first + di][l[i].second + 1] = ']';
		}
	}
	swap(mp[i + di][j], mp[i][j]);
	return (di);
}

void bonus(vector<string>& mp, string& path)
{
	vector<string> rmp;
	for (string& s : mp)
	{
		string ss;
		for (char c : s)
		{
			if (c == '.') ss += "..";
			else if (c == 'O') ss += "[]";
			else if (c == '#') ss += "##";
			else if (c == '@') ss += "@.";
		}
		rmp.push_back(ss);
	}
	swap(rmp, mp);
	auto p = get_position(mp);
	int i = p.first, j = p.second;
	int di, dj;
	for (char c : path)
	{
		if (c == '^' || c == 'v')
		{
			di = (c == '^') ? -1 : 1;
			if (mp[i + di][j] == '.')
			{
				swap(mp[i + di][j], mp[i][j]);
				i += di;
			}
			else if (mp[i + di][j] != '#')
				i += move_vertical(mp, i, j, di);
		}
		else if (c == '<' || c == '>')
		{
			dj = (c == '<') ? -1 : 1;
			int jj = j + dj;
			while (mp[i][jj] != '.' && mp[i][jj] != '#')
				jj += dj;
			if (mp[i][jj] == '#')
				continue ;
			while (dj < 0 ? jj - dj <= j : jj - dj >= j)
			{
				swap(mp[i][jj], mp[i][jj - dj]);
				jj -= dj;
			}
			j += dj;
		}
	}
	ll ans = 0;
	int m = mp.size(), n = mp[0].size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			if (mp[i][j] == '[')
				ans += 100 * i + j;
	}
	cout << ans << endl;
}

int main(void)
{
	ifstream infile("input.txt");
	string line;
	vector<string> M;
	string path;
	bool is_map = true;
	while (getline(infile, line))
	{
		if (!line.empty())
		{
			if (is_map) M.push_back(line);
			else path += line;
		}
		else
			is_map = false;
	}
	while (getline(infile, line))
		path += line;
	mandatory(M, path);
	return (0);
}

