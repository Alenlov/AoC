#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Dec 15 10:12:51 2019

@author: johanalenlov
"""

import random


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
					if self.toPrint: print('Waiting for input')
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

def changeDirection(pos, shipMap):
	pos1 = (pos[0], pos[1] + 1)
	pos2 = (pos[0], pos[1] - 1)
	pos3 = (pos[0] - 1, pos[1])
	pos4 = (pos[0] + 1, pos[1])
	if pos1 not in shipMap:
		return [1]
	elif pos4 not in shipMap:
		return [4]
	elif pos2 not in shipMap:
		return [2]
	elif pos3 not in shipMap:
		return [3]
	else:
		return [random.randint(1,4)]


def movePos(direction, pos):
	if direction == 1:
		return (pos[0], pos[1] + 1)
	elif direction == 2:
		return (pos[0], pos[1] - 1)
	elif direction == 3:
		return (pos[0] - 1, pos[1])
	elif direction == 4:
		return (pos[0] + 1, pos[1])

def reverseDirection(direction):
	if direction == 1:
		return [2]
	elif direction == 2:
		return [1]
	elif direction == 3:
		return [4]
	elif direction == 4:
		return [3]

def notInMap(pos,shipMap):
	free = 0
	pos1 = (pos[0], pos[1] + 1)
	pos2 = (pos[0], pos[1] - 1)
	pos3 = (pos[0] - 1, pos[1])
	pos4 = (pos[0] + 1, pos[1])
	if pos1 not in shipMap:
		free += 1
	elif pos4 not in shipMap:
		free += 1
	elif pos2 not in shipMap:
		free += 1
	elif pos3 not in shipMap:
		free += 1
	return free

def freeSpots(pos,shipMap):
	pos1 = (pos[0], pos[1] + 1)
	pos2 = (pos[0], pos[1] - 1)
	pos3 = (pos[0] - 1, pos[1])
	pos4 = (pos[0] + 1, pos[1])
	freeDir = []
	if pos1 in shipMap:
		if shipMap[pos1] == '.':
			freeDir.append(pos1)
	if pos2 in shipMap:
		if shipMap[pos2] == '.':
			freeDir.append(pos2)
	if pos3 in shipMap:
		if shipMap[pos3] == '.':
			freeDir.append(pos3)
	if pos4 in shipMap:
		if shipMap[pos4] == '.':
			freeDir.append(pos4)
	return freeDir

def printMap(shipMan, miny, maxy, minx, maxx, pos = False):
	for y in range(miny,maxy+1):
		for x in range(minx,maxx+1):
			if (x,y) == pos:
				print('D',end='')
			elif (x,y) in shipMap:
				print(shipMap[(x,y)],end='')
			else:
				print(' ',end='')
		print('')

intcode = open('2019/15/input','r')
code = intcode.read()
intcode.close()
codeList = [ int(x) for x in code.split(',')]

intComp = IntComputer(codeList.copy(), toPrint = 0)


minx = 0
maxx = 0
miny = 0
maxy = 0
pos = (0,0)
oxyPos = False
shipMap = {pos : '.'}
lengthMap = {pos : 0}
freeMap = {pos : 4}
totFree = 4
runing = True
history = []
direction = [1]
while runing:
	#direction = [random.randint(1,4)]
	
	output = intComp.runProgram(direction)
	if output[0] == 0:
		newpos = movePos(direction[0], pos)
		shipMap[newpos] = '#'
	elif output[0] == 1:
		newpos = movePos(direction[0], pos)
		if newpos not in lengthMap:
			lengthMap[newpos] = lengthMap[pos] + 1
		pos = newpos
		if pos not in shipMap:
			shipMap[pos] = '.'
			history.append(direction)
	elif output[0] == 2:
		newpos = movePos(direction[0], pos)
		lengthMap[newpos] = lengthMap[pos] + 1
		pos = newpos
		if pos not in shipMap:
			shipMap[pos] = 'O'
			history.append(direction)
			oxyPos = newpos	
	if newpos[0] < minx:
		minx = newpos[0]
	elif newpos[0] > maxx:
		maxx = newpos[0]
	if newpos[1] < miny:
		miny = newpos[1]
	elif newpos[1] > maxy:
		maxy = newpos[1]

	numFree = notInMap(pos, shipMap)	
	if numFree == 0:
		if len(history) == 0:
			runing = False
		else:
			direction = reverseDirection(history.pop()[0])
	else:
		direction = changeDirection(pos, shipMap)




print('Steg till Syre = {}'.format(lengthMap[oxyPos]))

printMap(shipMap, miny, maxy, minx, maxx, pos)

	


minx, maxx, miny, maxy = (0,0,0,0)
o2pos = []
numFree = 0
for pos in shipMap:
	if pos[0] < minx:
		minx = pos[0]
	elif pos[0] > maxx:
		maxx = pos[0]
	if pos[1] < miny:
		miny = pos[1]
	elif pos[1] > maxy:
		maxy = pos[1]
	if shipMap[pos] == 'O':
		o2pos.append(pos)
	if shipMap[pos] == '.':
		numFree += 1
shipMapO2 = shipMap
minutes = 0
while numFree:
	newpos = []
	for pos in o2pos:
		newpos.extend(freeSpots(pos,shipMapO2))
	for pos in newpos:
		shipMapO2[pos] = 'O'
		numFree -= 1
	o2pos = newpos
	minutes += 1
printMap(shipMap, miny, maxy, minx, maxx)
print(minutes)