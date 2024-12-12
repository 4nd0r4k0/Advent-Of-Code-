# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    DAY_11.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andorako <andorako@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 08:21:48 by andorako          #+#    #+#              #
#    Updated: 2024/12/12 07:56:51 by andorako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import sys
from collections import defaultdict
from math import log10, ceil

input_file = "input.txt"

def mandatory():
	with open(input_file, "r") as infile:
		a = [int(x) for x in infile.readline().split()]
		OP = 25
		for op in range(1, OP + 1):
			new_shit = []
			for num in a:
				if num == 0:
					new_shit.append(1)
				else:
					dc = ceil(log10(num + 1))
					if dc & 1:
						new_shit.append(num * 2024)
					else:
						pow10 = 10 ** (dc >> 1)
						new_shit.append(num // pow10)
						new_shit.append(num % pow10)
			del a
			a = new_shit
		print (len(a))

def bonus():
	OP = 75
	dp = defaultdict(int)
	def find(n, op):
		if (n, op) in dp:
			return dp[n, op]
		if op >= OP:
			return 0
		ans = 0
		if n == 0:
			ans = find(1, op + 1)
		else:
			digit_length = ceil(log10(n + 1))
			if digit_length % 2 == 0:
				pw10 = 10 ** (digit_length // 2)
				ans += find(n // pw10, op + 1)
				ans += find(n % pw10, op + 1)
				ans += 1
			else:
				ans = find(n * 2024, op + 1)
		dp[n, op] = ans
		return ans

	with open(input_file, "r") as infile:
		a = [int(x) for x in infile.readline().split()]
		res = sum(find(x, 0) for x in a) + len(a)
		print(res)

bonus()
