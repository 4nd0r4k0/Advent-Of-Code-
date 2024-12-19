/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_17.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:57:29 by andorako          #+#    #+#             */
/*   Updated: 2024/12/18 13:56:21 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>
#define A 0
#define B 1
#define C 2

using namespace std;
using ll = long long;

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

ll combo(int combo_id, vector<ll>& _register)
{
	if (combo_id < 4)
		return (combo_id);
	else if (combo_id == 4)
		return (_register[A]);
	else if (combo_id == 5)
		return (_register[B]);
	else if (combo_id == 6)
		return (_register[C]);
	else
		return (-1);
}

void	mandatory(vector<pair<int, int>>& program, vector<ll>& _register)
{
	for (int i = 0; i < (int) program.size();)
	{
		if (program[i].first == 3 && _register[A])
		{
			i = program[i].second;
			continue ;
		}
		else if (program[i].first == 0)
			_register[A] = _register[A] >> combo(program[i].second, _register);
		else if (program[i].first == 1)
			_register[B] = _register[B] ^ program[i].second;
		else if (program[i].first == 2)
			_register[B] = combo(program[i].second, _register) % 8;
		else if (program[i].first == 4)
			_register[B] = _register[B] ^ _register[C];
		else if (program[i].first == 5)
			cout << combo(program[i].second, _register) % 8;
		else if (program[i].first == 6)
			_register[B] = _register[A] >> combo(program[i].second, _register);
		else if (program[i].first == 7)
			_register[C] = _register[A] >> combo(program[i].second, _register);
		i++;
	}
}

int main(void)
{
	ifstream infile("input.txt");
	string lineP, lineA, lineB, lineC;
	vector<ll> _register(3);

	getline(infile, lineA);
	getline(infile, lineB);
	getline(infile, lineC);
	getline(infile, lineP);
	getline(infile, lineP);
	vector<string> spLineA = m_split(lineA, ":");
	vector<string> spLineB = m_split(lineB, ":");
	vector<string> spLineC = m_split(lineC, ":");
	vector<string> spLineP = m_split(lineP, ":");
	_register[A] = stoll(spLineA[1]);
	_register[B] = stoll(spLineB[1]);
	_register[C] = stoll(spLineC[1]);
	vector<string> cmds = m_split(spLineP[1], ",");
	vector<pair<int, int>> program;
	for (int i = 0; i < (int) cmds.size(); i += 2)
	{
		int	opcode = stoi(cmds[i]);
		int operand = stoi(cmds[i + 1]);
		program.push_back({opcode, operand});
	}
	mandatory(program, _register);
	cout << endl;
	return (0);
}
