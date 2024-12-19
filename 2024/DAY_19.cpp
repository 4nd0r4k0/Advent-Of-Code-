/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_19.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:18:27 by andorako          #+#    #+#             */
/*   Updated: 2024/12/19 09:40:09 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>

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

void	m_strim(string& s)
{
	while (!s.empty() && isspace(s.back()))
		s.pop_back();
	if (s.empty())
		return ;
	reverse(begin(s), end(s));
	while (!s.empty() && isspace(s.back()))
		s.pop_back();
	reverse(begin(s), end(s));
}

bool	solve(unordered_set<string>& patterns, vector<bool>& cache, string& design, int idx)
{
	if (cache[idx])
		return (cache[idx]);
	if (idx == (int) design.size())
		return (true);
	bool res = false;
	for (int i = idx; i < (int) design.size(); i++)
	{
		string sub = design.substr(idx, i - idx + 1);
		if (patterns.find(sub) != patterns.end())
			res = solve(patterns, cache, design, i + 1) || res;
	}
	return (cache[idx] = res);
}

void mandatory(void)
{
	ifstream file("input.txt");
	string	pattern;

	getline(file, pattern);
	unordered_set<string> patterns_set;
	vector<string> patterns = m_split(pattern, ",");
	for (string& s : patterns)
	{
		m_strim(s);
		if (!s.empty())
			patterns_set.insert(s);
	}
	string line;
	int possible = 0;
	getline(file, line);
	while (getline(file, line))
	{
		vector<bool> dp(line.size(), false);
		possible += solve(patterns_set, dp, line, 0);
	}
	cout << possible << endl;
}

long long	b_solve(unordered_set<string>& patterns, vector<vector<long long>>& cache, string& design, int j, int i)
{
	if (cache[j][i] != -1)
		return (cache[j][i]);
	if (i == (int) design.size())
		return (true);
	long long res = 0;
	for (int ii = i; ii < (int) design.size(); ii++)
	{
		string sub = design.substr(i, ii - i + 1);
		if (patterns.find(sub) != patterns.end())
			res += b_solve(patterns, cache, design, i, ii + 1);
	}
	return (cache[j][i] = res);
}

void bonus(void)
{
	ifstream file("input.txt");
	string	pattern;

	getline(file, pattern);
	unordered_set<string> patterns_set;
	vector<string> patterns = m_split(pattern, ",");
	for (string& s : patterns)
	{
		m_strim(s);
		if (!s.empty())
			patterns_set.insert(s);
	}
	string line;
	getline(file, line);
	long long possible = 0;
	while (getline(file, line))
	{
		const int N = line.size();
		vector<vector<long long>> dp(N + 1, vector<long long>(N + 1, -1));
		possible += b_solve(patterns_set, dp, line, 0, 0);
	}
	cout << possible << endl;
}

int main(void)
{
	bonus();
	return (0);
}
