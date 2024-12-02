# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    1.py                                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andorako <andorako@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 09:01:23 by andorako          #+#    #+#              #
#    Updated: 2024/12/02 10:02:09 by andorako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
from collections import Counter

input_file = "input.txt"
output_file = "output.txt"

def mandatory():
	with open(input_file, "r") as infile:
		a, b = [], []
		for line in infile.readlines():
			x, y = list(map(int, line.split()))
			a.append(x)
			b.append(y)
		a.sort()
		b.sort()
		dist = sum(abs(x - y) for x, y in zip(a, b))
		print(dist)

def bonus():
	with open(input_file, "r") as infile:
		a, count = [], Counter()
		for line in infile.readlines():
			x, y = list(map(int, line.split()))
			a.append(x)
			count[y] += 1
		dist = sum(x * count[x] for x in a)
		print(dist)

mandatory()