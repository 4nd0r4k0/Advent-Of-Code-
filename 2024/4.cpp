/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:47:45 by andorako          #+#    #+#             */
/*   Updated: 2024/12/08 11:12:43 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>

using namespace std;

vector<string> transpose(vector<string>& M)
{
	int m = M.size(), n = M[0].size();
	vector<string> res(n, string(m, '$'));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			res[j][i] = M[i][j];
	return (res);
}

vector<string> mirror(vector<string>& M)
{
	int m = M.size();
	vector<string> res(m);
	for (int i = 0; i < m; i++)
	{
		res[i] = M[i];
		reverse(begin(res[i]), end(res[i]));
	}
	return (res);
}

int fcount(string& s, string t)
{
	if (s.size() < t.size())
		return (0);
	int count = 0;
	for (int i = 0, j = 0; i <= (int) (s.size() - t.size()); i++)
	{
		j = 0;
		for (j = 0; j < (int) t.size(); j++)
			if (s[i + j] != t[j])
				break ;
		if (j == (int) t.size())
			count++;
	}
	return (count);
}

void mandatory(vector<string>& M)
{
	long long count = 0;
	int m = M.size(), n = M[0].size();
	// Four directions
	for (string& s : M) count += fcount(s, "XMAS") + fcount(s, "SAMX");
	vector<string> T = transpose(M);
	for (string& t : T) count += fcount(t, "XMAS") + fcount(t, "SAMX");
	// All diagonals
	for (int j = 0; j < n; j++)
	{
		string diag;
		for (int x = 0; x < n - j; x++) diag += M[x][j + x];
		count += fcount(diag, "XMAS") + fcount(diag, "SAMX");
	}
	for (int i = 1; i < m; i++)
	{
		string diag;
		for (int x = 0; x < m - i; x++) diag += M[i + x][x];
		count += fcount(diag, "XMAS") + fcount(diag, "SAMX");
	}
	vector<string> MM = mirror(M);
	for (int j = 0; j < n; j++)
	{
		string diag;
		for (int x = 0; x < n - j; x++) diag += MM[x][j + x];
		count += fcount(diag, "XMAS") + fcount(diag, "SAMX");
	}
	for (int i = 1; i < m; i++)
	{
		string diag;
		for (int x = 0; x < m - i; x++) diag += MM[i + x][x];
		count += fcount(diag, "XMAS") + fcount(diag, "SAMX");
	}
	cout << count << endl;
}

void bonus(vector<string>& M)
{
	vector<vector<string>> CMP = {
		{"M@S", "@A@", "M@S"},
		{"S@S", "@A@", "M@M"},
		{"M@M", "@A@", "S@S"},
		{"S@M", "@A@", "S@M"}
	};
	function<int(int, int)> match = [&](int i, int j)
	{
		int ans = 0;
		for (vector<string>& xmas : CMP)
		{
			int c = 0;
			for (int ii = 0; ii < 3; ii++)
				for (int jj = 0; jj < 3; jj++)
					c += xmas[ii][jj] == '@'
						|| xmas[ii][jj] == M[i + ii - 1][j + jj - 1];
			ans += c == 9;
		}
		return (ans);
	};
	long long count = 0;
	int m = M.size(), n = M[0].size();
	for (int i = 1; i + 1 < m; i++)
		for (int j = 1; j + 1 < n; j++)
			count += match(i, j);
	cout << count << endl;
}

int main(void)
{
	ifstream file("input.txt");
	string str;
	vector<string> M;
	while (std::getline(file, str))
		M.push_back(str);		
	mandatory(M);
	return (0);
}

