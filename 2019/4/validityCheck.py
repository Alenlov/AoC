#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec  5 17:04:26 2019

@author: johanalenlov
"""
def validCode1(code):
	equal = 0
	num = [int(x) for x in code]
	for i in range(5):
		if num[i] > num[i+1]:
			return 0
		elif num[i] == num[i+1]:
			equal = 1
				
	# if equal == 1:
	# 	print(code)
	return equal


def validCode2(code):
	equal = 0
	num = [int(x) for x in code]
	for i in range(5):
		if num[i] > num[i+1]:
			return 0
		elif num[i] == num[i+1]:
			if i == 0:
				if num[i] != num[i+2]:
					equal = 1
			elif i == 4:
				if num[i] != num[i-1]:
					equal = 1
			else:
				if num[i] != num[i-1] and num[i] != num[i+2]:
					equal = 1
				
	# if equal == 1:
	# 	print(code)
	return equal
	
totalValid = 0
#print(validCode(str(678889)))
for nums in range(123257,647016):
	totalValid += validCode2(str(nums))

print(totalValid)