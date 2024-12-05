/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:37:58 by andorako          #+#    #+#             */
/*   Updated: 2024/12/05 11:37:58 by andorako         ###   ########.fr       */
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

void mandatory(void)
{
	string line;
	ifstream infile("input.txt");
	long long ans = 0;
	unordered_map<int, unordered_set<int>> graph;
	while (getline(infile, line))
	{
		if (line.find('|') != string::npos)
		{
			vector<string> sp = m_split(line, "|");
			int u = stoi(sp[0]), v = stoi(sp[1]);
			graph[u].insert(v);
		}
		else if (line.find(',') != string::npos)
		{
			vector<string> sp = m_split(line, ",");
			vector<int> vertex;
			int check = 1;
			for (string& s : sp)
				vertex.push_back(stoi(s));
			int N = sp.size();
			for (int i = N - 1; check && i >= 0; i--)
			{
				auto& S = graph[vertex[i]];
				for (int j = i - 1; check && j >= 0; j--)
					if (S.find(vertex[j]) != S.end())
						check &= 0;
			}
			if (check)
				ans += vertex[vertex.size() >> 1];
		}
	}
	cout << ans << endl;	
}

void bonus(void)
{
	string line;
	ifstream infile("input.txt");
	long long ans = 0;
	unordered_map<int, unordered_set<int>> graph;
	while (getline(infile, line))
	{
		if (line.find('|') != string::npos)
		{
			vector<string> sp = m_split(line, "|");
			int u = stoi(sp[0]), v = stoi(sp[1]);
			graph[u].insert(v);
		}
		else if (line.find(',') != string::npos)
		{
			vector<string> sp = m_split(line, ",");
			vector<int> vertex;
			bool check = true;
			for (string& s : sp)
				vertex.push_back(stoi(s));
			int N = sp.size();
			for (int i = N - 1; check && i >= 0; i--)
			{
				auto& S = graph[vertex[i]];
				for (int j = i - 1; j >= 0; j--)
				{
					if (S.find(vertex[j]) != S.end())
					{
						check = false;
						break ;
					}
				}
			}
			if (!check)
			{
				for (int i = N - 1; i > 0; i--)
				{
					check = 0;
					while (!check)
					{
						auto& S = graph[vertex[i]];
						for (int j = i - 1; j >= 0; j--)
						{
							if (S.find(vertex[j]) != S.end())
							{
								swap(vertex[i], vertex[j]);
								check &= 0;
								break ;
							}
							check |= 1;
						}
					}
				}
				ans += vertex[vertex.size() >> 1];
			}
		}
	}
	cout << ans << endl;	
}

int	 main(void)
{
	mandatory();
	return (0);
}
