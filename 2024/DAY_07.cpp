/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_07.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 08:46:26 by andorako          #+#    #+#             */
/*   Updated: 2024/12/12 07:57:52 by andorako         ###   ########.fr       */
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

/*
	Encoding: 0 mean addition and 1 mean multiplication
*/
bool check_equation(long long lhs, vector<int>& rhs)
{
	int n = rhs.size() - 1;
	for (int i = 0; i < (1 << n); i++)
	{
		long long val = rhs[0];
		for (int j = 0; j < n; j++)
		{
			if ((i >> j) & 1) val *= rhs[1 + j];
			else val += rhs[1 + j]; 
		}
		if (val == lhs)
			return (true);
	}
	return (false);
}

void mandatory(void)
{
	ifstream file("input.txt");
	string line;
	long long ans = 0;
	while (getline(file, line))
	{
		vector<string> strs = m_split(line, ":");
		long long lhs = stoll(strs[0]);
		vector<string> rest = m_split(strs[1], " ");
		vector<int> rhs;
		for (string& s : rest)
		{
			if (!s.empty())
				rhs.push_back(stoi(s));
		}
		if (check_equation(lhs, rhs))
			ans += lhs;
	}
	cout << ans << endl;
}

bool bcheck_equation(long long lhs, vector<long long>& rhs, long long val, int idx)
{
	if (idx == (int) rhs.size())
		return (lhs == val);
	else if (val > lhs)
		return (false);
	bool check = bcheck_equation(lhs, rhs, val + rhs[idx], idx + 1);
	check = check || bcheck_equation(lhs, rhs, val * rhs[idx], idx + 1);
	if (!check)
	{
		string concat = to_string(val) + to_string(rhs[idx]);
		check = bcheck_equation(lhs, rhs, stoll(concat), idx + 1);
	}
	return (check);
}

void bonus(void)
{
	ifstream file("input.txt");
	string line;
	long long ans = 0;
	while (getline(file, line))
	{
		vector<string> strs = m_split(line, ":");
		long long lhs = stoll(strs[0]);
		vector<string> rest = m_split(strs[1], " ");
		vector<long long> rhs;
		for (string& s : rest)
		{
			if (!s.empty())
				rhs.push_back(stoll(s));
		}
		if (bcheck_equation(lhs, rhs, rhs[0], 1))
			ans += lhs;
	}
	cout << ans << endl;
}

int main(void)
{
	mandatory();
	return (0);
}