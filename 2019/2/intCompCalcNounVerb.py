#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  4 09:50:38 2019

@author: johanalenlov
"""

for verb in range(100):
	for noun in range(100):
		intcode = open('2019/2/input','r')
		code = intcode.read()
		intcode.close()
		#code = '1,9,10,3,2,3,11,0,99,30,40,50'
		
		codeList = [ int(x) for x in code.split(',')]
		
		codeList[1] = noun
		codeList[2] = verb
		
		runing = True
		head = 0
		while runing:
			instruction = codeList[head]
			if instruction == 1:
				pos1 = codeList[head+1]
				pos2 = codeList[head+2]
				pos3 = codeList[head+3]
				codeList[pos3] = codeList[pos1] + codeList[pos2]
			elif instruction == 2:
				pos1 = codeList[head+1]
				pos2 = codeList[head+2]
				pos3 = codeList[head+3]
				codeList[pos3] = codeList[pos1] * codeList[pos2]
			elif instruction == 99:
				runing = False
				break
			else:
				print('Error!, head = {}'.format(head))
				
			
			head += 4
		if codeList[0] == 19690720:
			print(100 * noun + verb)