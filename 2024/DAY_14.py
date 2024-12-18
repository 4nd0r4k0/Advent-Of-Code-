# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    DAY_14.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andorako <andorako@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/14 08:19:23 by andorako          #+#    #+#              #
#    Updated: 2024/12/16 08:03:57 by andorako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
from collections import Counter

input_file = "input.txt"

def mandatory():
	with open(input_file, "r") as infile:
		M, N = 103, 101
		count = [[0] * N for _ in range(M)]
		for line in infile.readlines():
			pp, vv = line.split()
			px, py = [int(v) for v in pp[2:].split(',')]
			vx, vy = [int(v) for v in vv[2:].split(',')]
			for _ in range(100):
				px = (px + vx + N) % N
				py = (py + vy + M) % M
			count[py][px] += 1
		a, b, c, d = [0] * 4
		for i in range(M >> 1):
			for j in range(N >> 1):
				a += count[i][j]
		for i in range(M >> 1):
			for j in range((N >> 1) + 1, N):
				b += count[i][j]
		for i in range((M >> 1) + 1, M):
			for j in range(N >> 1):
				c += count[i][j]
		for i in range((M >> 1) + 1, M):
			for j in range((N >> 1) + 1, N):
				d += count[i][j]
		print(a * b * c * d)

def bonus():
	pass

mandatory()
