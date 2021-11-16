#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  4 09:50:38 2019

@author: johanalenlov
"""

import itertools

def getVal(mode,pos,codeList):
	if mode == 1:
		return codeList[pos]
	else:
		return codeList[codeList[pos]]


def runProgram(codeList, inputs):
	outputs = []
	runing = True
	head = 0
	while runing:
		instruction = codeList[head]
		#print(instruction)
		opCode = instruction % 100
		instruction = int(instruction / 100)
		mode1 = instruction % 10
		instruction = int(instruction / 10)
		mode2 = instruction % 10
		instruction = int(instruction / 10)
		mode3 = instruction % 10
		if opCode == 1:
			val1 = getVal(mode1,head+1,codeList)
			val2 = getVal(mode2,head+2,codeList)
			pos3 = codeList[head+3]
			codeList[pos3] = val1 + val2
			head += 4
		elif opCode == 2:
			val1 = getVal(mode1,head+1,codeList)
			val2 = getVal(mode2,head+2,codeList)
			pos3 = codeList[head+3]
			codeList[pos3] = val1 * val2
			head += 4
		elif opCode == 3:
			val1 = inputs.pop(0)
			print('Input : {}'.format(val1))
			pos1 = codeList[head+1]
			codeList[pos1] = val1
			head += 2
		elif opCode == 4:
			val1 = getVal(mode1,head+1,codeList)
			print('Output : {}'.format(val1))
			outputs.append(val1)
			head += 2
		elif opCode == 5:
			val1 = getVal(mode1,head+1,codeList)
			val2 = getVal(mode2,head+2,codeList)
			if val1 == 0:
				head += 3
			else:
				head = val2
		elif opCode == 6:
			val1 = getVal(mode1,head+1,codeList)
			val2 = getVal(mode2,head+2,codeList)
			if val1 != 0:
				head += 3
			else:
				head = val2
		elif opCode == 7:
			val1 = getVal(mode1,head+1,codeList)
			val2 = getVal(mode2,head+2,codeList)
			pos3 = codeList[head+3]
			if val1 < val2:
				toStore = 1
			else:
				toStore = 0
			codeList[pos3] = toStore
			head += 4
		elif opCode == 8:
			val1 = getVal(mode1,head+1,codeList)
			val2 = getVal(mode2,head+2,codeList)
			pos3 = codeList[head+3]
			if val1 == val2:
				toStore = 1
			else:
				toStore = 0
			codeList[pos3] = toStore
			head += 4
		elif opCode == 99:
			runing = False
			break
		else:
			print('Error!, head = {}'.format(head))
	return outputs

def calcTotalThrust(codeList, sequence):
	inputVal = 0
	for phase in sequence:
		inputs = [phase, inputVal]
		outputs = runProgram(codeList, inputs)
		inputVal = outputs.pop()
	return inputVal

intcode = open('2019/7/input','r')
code = intcode.read()
intcode.close()
#code = '3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99'
codeList = [ int(x) for x in code.split(',')]
seq = [0,1,2,3,4]
vals = []
print(seq)
for sequence in itertools.permutations(seq):
	print(list(sequence))
	vals.append(calcTotalThrust(codeList, list(sequence)))
print(max(vals))



