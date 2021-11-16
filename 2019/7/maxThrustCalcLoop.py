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

class Amplifier():
	def __init__(self, codeList, phase):
		self.phase = phase
		self.codeList = codeList
		self.inputs = [phase]
		self.head = 0
		self.done = False
		
	def runProgram(self, inputs):
		head = self.head
		codeList = self.codeList
		self.inputs.extend(inputs)
		inputs = self.inputs
		outputs = []
		runing = True
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
				if inputs:
					val1 = inputs.pop(0)
					print('Input : {}'.format(val1))
					pos1 = codeList[head+1]
					codeList[pos1] = val1
					head += 2
				else:
					#print('Waiting for input')
					runing = False
					runNew = 1
					break
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
				runNew = 0
				break
			else:
				print('Error!, head = {}'.format(head))
		self.head = head
		return (outputs, runNew)

def calcTotalThrust(codeList, sequence):
	inputVal = [0]
	amps = []
	for phase in sequence:
		amps.append(Amplifier(codeList.copy(), phase))
	runing = 1
	while runing:
		for amp in amps:
			(output, runNew) = amp.runProgram(inputVal)
			inputVal = output
			runing *= runNew
	return inputVal

intcode = open('2019/7/input','r')
code = intcode.read()
intcode.close()
#code = '3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5'
codeList = [ int(x) for x in code.split(',')]
seq = [5,6,7,8,9]
vals = []
print(seq)
for sequence in itertools.permutations(seq):
	print(list(sequence))
	vals.append(calcTotalThrust(codeList, list(sequence)))
print(max(vals))


