/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DAY_09.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andorako <andorako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 07:54:42 by andorako          #+#    #+#             */
/*   Updated: 2024/12/12 07:57:34 by andorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/stdc++.h>

using namespace std;

void mandatory(string& input)
{
	vector<int> blocks;
	int file_id = 0;
	int n = input.size();

	for (int i = 0; i < n; i += 2)
	{
		int x = input[i] - '0';
		while (x-- > 0)
			blocks.push_back(file_id);
		if (i + 1 < n)
		{
			int y = input[i + 1] - '0';
			while (y-- > 0)
				blocks.push_back(-1);
		}
		file_id++;
	}
	int B = blocks.size();
	queue<int> free_space;
	for (int i = 0; i < B; i++)
		if (blocks[i] == -1)
			free_space.push(i);
	for (int i = B - 1; i >= 0; i--)
	{
		if (blocks[i] == -1)
			continue;
		if (!free_space.empty() && free_space.front() < i)
		{
			swap(blocks[i], blocks[free_space.front()]);
			free_space.pop();
		}
	}
	long long res = 0;
	for (int i = 0; i < B && blocks[i] != -1; i++)
		res += 1LL * i * blocks[i];
	cout << res << endl;
}

int	find_free_space(vector<int>& free_space, int width)
{
	int F = free_space.size();
	for (int f = 0; f <= (F - width); f++)
	{
		if (free_space[f] == -1)
			continue ;
		bool check = true;
		for (int shift = 0; shift + 1 < width; shift++)
			check &= (free_space[shift + f] + 1 == free_space[shift + 1 + f]);
		if (check)
			return (f);
	}
	return (-1);
}

void bonus(string& input)
{
	vector<int> blocks;
	map<int, int> block_size;
	int file_id = 0;
	int n = input.size();

	for (int i = 0; i < n; i += 2)
	{
		int x = input[i] - '0';
		block_size[file_id] = x;
		while (x-- > 0)
			blocks.push_back(file_id);
		if (i + 1 < n)
		{
			int y = input[i + 1] - '0';
			while (y-- > 0)
				blocks.push_back(-1);
		}
		file_id++;
	}
	int B = blocks.size();
	vector<int> free_space;
	for (int i = 0; i < B; i++)
		if (blocks[i] == -1)
			free_space.push_back(i);
	for (int i = B - 1; i >= 0;)
	{
		if (blocks[i] == -1)
			i--;
		else if (!free_space.empty())
		{
			int x = block_size[blocks[i]];
			int f = find_free_space(free_space, x);
			if (f != -1 && free_space[f] < i)
			{
				for (int j = f; x-- > 0; j++)
				{
					swap(blocks[free_space[j]], blocks[i--]);
					free_space[j] = -1;
				}
			}
			else
				i--;
		}
	}
	long long res = 0;
	for (int i = 0; i < B; i++)
	{
		if (blocks[i] != -1)
			res += 1LL * i * blocks[i];
	}
	cout << res << endl;
}

int main(void)
{
	ifstream file("input.txt");
	string line;
	getline(file, line);
	mandatory(line);
	return (0);
}
