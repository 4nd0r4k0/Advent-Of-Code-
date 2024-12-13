# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    DAY_13.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andorako <andorako@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 08:04:54 by andorako          #+#    #+#              #
#    Updated: 2024/12/13 19:11:35 by andorako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
from math import gcd

input_file = "input.txt"

def get_pairs(line, c):
	_, xy = line.split(':')
	px, py = xy.split(',')
	_, x = px.split(c)
	_, y = py.split(c)
	return [int(x), int(y)]

def count_tokens(A, B, P):
	if P[0] % gcd(A[0], B[0]) or P[1] % gcd(A[1], B[1]):
		return 0
	Ax, Ay = A
	Bx, By = B
	Px, Py = P
	num_alpha = By * Px - Bx * Py
	den_alpha = By * Ax - Bx * Ay
	if not den_alpha or num_alpha % den_alpha or num_alpha * den_alpha < 0:
		return 0
	alpha = num_alpha // den_alpha
	num_beta = Ay * Px - Ax * Py
	den_beta = Ay * Bx - Ax * By
	if not den_beta or num_beta % den_beta or num_beta * den_beta < 0:
		return 0
	beta = num_beta // den_beta
	return (3 * alpha + beta)

def mandatory():
	with open(input_file, "r") as infile:
		pair, ans = [], 0
		lines = infile.readlines()
		for i in range(0, len(lines), 4):
			A = get_pairs(lines[i], '+')
			B = get_pairs(lines[1 + i], '+')
			P = get_pairs(lines[2 + i], '=')
			ans += count_tokens(A, B, P)
		print(ans)

def bonus():
	with open(input_file, "r") as infile:
		pair, ans = [], 0
		lines = infile.readlines()
		for i in range(0, len(lines), 4):
			A = get_pairs(lines[i], '+')
			B = get_pairs(lines[1 + i], '+')
			P = get_pairs(lines[2 + i], '=')
			P[0] += 10000000000000
			P[1] += 10000000000000
			ans += count_tokens(A, B, P)
		print(ans)

bonus()
