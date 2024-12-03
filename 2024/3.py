# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    3.py                                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andorako <andorako@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 08:44:43 by andorako          #+#    #+#              #
#    Updated: 2024/12/03 10:24:42 by andorako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
import re
import functools

input_file = "input.txt"

def mul_matches(line):
	res = 0
	if line:
		all_matches = re.findall(r"mul\(\d{1,3},\d{1,3}\)", line)
		for match in all_matches:
			x, y = map(int, match[4:-1].split(','))
			res += x * y
	return res

def mandatory():
	with open(input_file, "r") as infile:
		res = 0
		for line in infile.readlines():
			line = line.rstrip('\n')
			res += mul_matches(line)
		print(res)

def bonus():
	def all_occurences(text, pattern):
		occ = re.finditer(pattern, text)
		return functools.reduce(lambda x, y: x + [y.start()], occ, [])
	with open(input_file, "r") as infile:
		res, i, j = 0, 0, 0
		line = "do()$" + "@".join(infile.readlines()) + "$don\'t()"
		dos = all_occurences(line, "do()")
		donts = all_occurences(line, "don\'t()")
		L = sorted([(i, 1) for i in dos] + [(j, 2) for j in donts])
		while i < len(L):
			while i < len(L) and L[i][1] == 1:
				i += 1
			res += mul_matches(line[L[j][0] : L[i][0]])
			while i < len(L) and L[i][1] == 2:
				i += 1
			j = i
		print(res)

bonus()