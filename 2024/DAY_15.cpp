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
	for (char c : path)
	{
		if (c == '^')
		{
			int ii;
			for (ii = i; mp[ii - 1][j] == 'O'; ii--) ;
			if (mp[ii - 1][j] != '#')
			{
				swap(mp[ii - 1][j], mp[i - 1][j]);
				mp[i - 1][j] = '@';
				mp[i][j] = '.';
				i--;
			}
		}
		else if (c == 'v')
		{
			int ii;
			for (ii = i; mp[ii + 1][j] == 'O'; ii++) ;
			if (mp[ii + 1][j] != '#')
			{
				swap(mp[ii + 1][j], mp[i + 1][j]);
				mp[i + 1][j] = '@';
				mp[i][j] = '.';
				i++;
			}
		}
		else if (c == '<')
		{
			int jj;
			for (jj = j; mp[i][jj - 1] == 'O'; jj--) ;
			if (mp[i][jj - 1] != '#')
			{
				swap(mp[i][jj - 1], mp[i][j - 1]);
				mp[i][j - 1] = '@';
				mp[i][j] = '.';
				j--;
			}
		}
		else if (c == '>')
		{
			int jj;
			for (jj = j; mp[i][jj + 1] == 'O'; jj++) ;
			if (mp[i][jj + 1] != '#')
			{
				swap(mp[i][jj + 1], mp[i][j + 1]);
				mp[i][j + 1] = '@';
				mp[i][j] = '.';
				j++;
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

bool move_vertical(vector<string>& mp, int i, int j, int di)
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
		for (int _ = 0; _ < Q; _++)
		{
			auto p = que.front();
			que.pop();
			int ni = p.first, nj = p.second;
			if (mp[ni + di][nj] == '#')
				return (false);
			l.push_back({ni, nj});
			if (mp[ni + di][nj] != '.')
			{
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
	return (true);
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
	for (char c : path)
	{
		if (c == '^')
		{
			if (mp[i - 1][j] == '.') swap(mp[i - 1][j], mp[i][j]), i--;
			else if (mp[i - 1][j] != '#') i -= move_vertical(mp, i, j, -1);
		}
		else if (c == 'v')
		{
			if (mp[i + 1][j] == '.') swap(mp[i + 1][j], mp[i][j]), i++;
			else if (mp[i + 1][j] != '#') i += move_vertical(mp, i, j, 1);
		}
		else if (c == '<')
		{
			int jj;
			for (jj = j - 1; mp[i][jj] != '.' && mp[i][jj] != '#'; jj--) ;
			if (mp[i][jj] != '#')
			{
				while (jj + 1 <= j)
				{
					swap(mp[i][jj], mp[i][jj + 1]);
					jj++;
				}
				j--;
			}
		}
		else if (c == '>')
		{
			int jj;
			for (jj = j + 1; mp[i][jj] != '.' && mp[i][jj] != '#'; jj++) ;
			if (mp[i][jj] != '#')
			{
				while (jj - 1 >= j)
				{
					swap(mp[i][jj], mp[i][jj - 1]);
					jj--;
				}
				j++;
			}
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
	bonus(M, path);
	return (0);
}

