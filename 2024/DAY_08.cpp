/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_08.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:32:31 by andorako          #+#    #+#             */
/*   Updated: 2024/12/12 07:57:43 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	for (string& v : M)
	{
		cout << v << "\n";
	}
	int ans = 0;
	for (string& v : M)
		for (char c : v)
			if (c == '#')
				ans++;
	cout << ans << endl;
}

void bonus(vector<string>&M)
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
				pair<int, int> p = vec[i], t = vec[j];
				if (p.second > t.second)
					swap(p, t);
				int pi = p.first, pj = p.second;
				int ti = t.first, tj = t.second;
				int ai, aj, bi, bj;
				while (1)
				{
					ai = 2 * pi - ti;
					aj = 2 * pj - tj;
					if (ai >= 0 && ai < m && aj >= 0 && aj < n)
					{
						M[ai][aj] = '$';
						ti = pi, tj = pj;
						pi = ai, pj = aj;
					}
					else
						break ;
				}
				pi = p.first, pj = p.second;
				ti = t.first, tj = t.second;
				while (1)
				{
					bi = 2 * ti - pi;
					bj = 2 * tj - pj;
					if (bi >= 0 && bi < m && bj >= 0 && bj < n)
					{
						M[bi][bj] = '$';
						pi = ti, pj = tj;
						ti = bi, tj = bj;
					}
					else
						break ;
				}
			}
		}
	}
	int ans = 0;
	for (string& v : M)
		for (char c : v)
			if (c != '.')
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
	bonus(M);
	return (0);
}
