#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 11 07:34:47 2019

@author: johanalenlov
"""

class IntComputer():
	def __init__(self, codeList, toPrint = 1):
		self.codeList = codeList
		self.length = len(codeList)
		self.inputs = []
		self.head = 0
		self.relBase = 0
		self.done = False
		self.numInstructions = 0
		self.toPrint = toPrint
		
	def getVal(self, mode,pos):
		if pos < 0:
			print('Negative position, pos: {}'.format(pos))
		return self.codeList[self.getPos(mode,pos)]
	
	def getPos(self, mode, pos):
		if mode == 0:
			pos = self.codeList[pos]
		elif mode == 1:
			pos = pos
		elif mode == 2:
			 pos = self.relBase + self.codeList[pos]
		else:
			print('Wrong mode, encountered mode: {}, pos: {}'.format(mode,pos))
			self.runing = False
		
		if pos >= self.length:
			self.codeList.extend([0]*(pos - self.length + 1))
			self.length = len(self.codeList)
		
		return pos
	
	def getInstruction(self, head):
		instruction = self.codeList[head]
		opCode = instruction % 100
		instruction = int(instruction / 100)
		mode1 = instruction % 10
		instruction = int(instruction / 10)
		mode2 = instruction % 10
		instruction = int(instruction / 10)
		mode3 = instruction % 10
		return (opCode, mode1, mode2, mode3)
		
	def runProgram(self, inputs):
		head = self.head
		#codeList = self.codeList
		self.inputs.extend(inputs)
		inputs = self.inputs
		outputs = []
		self.runing = True
		while self.runing:
			(opCode, mode1, mode2, mode3) = self.getInstruction(head)
			self.numInstructions += 1
			if opCode == 1:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				pos3 = self.getPos(mode3,head+3)
				self.codeList[pos3] = val1 + val2
				head += 4
			elif opCode == 2:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				pos3 = self.getPos(mode3,head+3)
				self.codeList[pos3] = val1 * val2
				head += 4
			elif opCode == 3:
				if inputs:
					val1 = inputs.pop(0)
					if self.toPrint: print('Input : {}'.format(val1))
					pos1 = self.getPos(mode1,head+1)
					self.codeList[pos1] = val1
					head += 2
				else:
					#print('Waiting for input')
					self.runing = False
					break
			elif opCode == 4:
				val1 = self.getVal(mode1,head+1)
				if self.toPrint: print('Output : {}'.format(val1))
				outputs.append(val1)
				head += 2
			elif opCode == 5:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				if val1 == 0:
					head += 3
				else:
					head = val2
			elif opCode == 6:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				if val1 != 0:
					head += 3
				else:
					head = val2
			elif opCode == 7:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				pos3 = self.getPos(mode3,head+3)
				if val1 < val2:
					toStore = 1
				else:
					toStore = 0
				self.codeList[pos3] = toStore
				head += 4
			elif opCode == 8:
				val1 = self.getVal(mode1,head+1)
				val2 = self.getVal(mode2,head+2)
				pos3 = self.getPos(mode3,head+3)
				if val1 == val2:
					toStore = 1
				else:
					toStore = 0
				self.codeList[pos3] = toStore
				head += 4
			elif opCode == 9:
				val1 = self.getVal(mode1,head+1)
				self.relBase += val1
				head += 2
			elif opCode == 99:
				self.runing = False
				self.done = True
				break
			else:
				print('Error!, head = {}'.format(head))
		self.head = head
		return outputs

def changeDirection(direction, move):
	(right,up) = direction
	if right == 1:
		if move == 0:
			return ( 0, 1)
		else:
			return ( 0,-1)
	elif right == -1:
		if move == 1:
			return ( 0, 1)
		else:
			return ( 0,-1)
	elif up == 1:
		if move == 0:
			return (-1, 0)
		else:
			return ( 1, 0)
	elif up == -1:
		if move == 1:
			return (-1, 0)
		else:
			return ( 1, 0)
		

intcode = open('2019/11/input','r')
code = intcode.read()
intcode.close()
codeList = [ int(x) for x in code.split(',')]

intComp = IntComputer(codeList.copy(), toPrint = 0)



panels = {}
minX = 0
minY = 0
maxX = 0
maxY = 0
pos = (0,0)
direction = (0,1)
panels[pos] = 1
while not intComp.done:
	if pos not in panels:
		currentColor = 0
	else:
		currentColor = panels[pos]
	out = intComp.runProgram([currentColor])
	newCol = out[0]
	move = out[1]
	panels[pos] = newCol
	direction = changeDirection(direction, move)
	pos = (pos[0] + direction[0], pos[1] + direction[1])
	if pos[0] < minX:
		minX = pos[0]
	elif pos[0] > maxX:
		maxX = pos[0]
	if pos[1] < minY:
		minY = pos[1]
	elif pos[1] > maxY:
		maxY = pos[1]

for y in range(minY,maxY + 1):
	for x in range(minX,maxX + 1):
		pos = (x,y)
		if pos in panels:
			if panels[pos] == 1:
				print('1',end = '')
			else:
				print(' ', end = '')
		else:
			print(' ', end = '')
	print('')
	

print(len(panels))

