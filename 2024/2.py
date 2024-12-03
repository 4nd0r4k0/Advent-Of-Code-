# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    2.py                                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andorako <andorako@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 09:14:46 by andorako          #+#    #+#              #
#    Updated: 2024/12/02 09:59:21 by andorako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
from collections import Counter

input_file = "input.txt"

def in_range(delta):
	return (delta >= 1 and delta <= 3)

def test(L):
	sL = sorted(L)
	check = sL == L
	check = check or (sL[::-1] == L)
	if check:
		for i in range(len(L) - 1):
			delta = abs(L[i] - L[i + 1])
			check = check and in_range(delta)
			if not check:
				break
	return check

def mandatory():
	with open(input_file, "r") as infile:
		count = 0
		for line in infile.readlines():
			L = list(map(int, line.split()))
			if test(L):
				count += 1
		print(count)

def bonus():
	with open(input_file, "r") as infile:
		count = 0
		for line in infile.readlines():
			L = list(map(int, line.split()))
			if test(L):
				count += 1
			else:
				for i in range(len(L)):
					Lc = L[:i] + L[i+1:]
					if test(Lc):
						count += 1
						break
		print(count)

mandatory()
