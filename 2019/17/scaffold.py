#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 17 09:39:23 2019

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

def getPos(direction,pos):
	#print(pos)
	#print(direction)
	newPos = (0,0)
	if direction == 0:
		newPos = (pos[0]-1, pos[1])
	elif direction == 1:
		newPos = (pos[0], pos[1]+1)
	elif direction == 2:
		newPos = (pos[0]+1, pos[1])
	elif direction == 3:
		newPos = (pos[0], pos[1]-1)
	#print(newPos)
	return newPos
		
def findTurn(direction, outMap, pos):
	print(direction)
	print(pos)
	maxy = len(outMap) - 2
	maxx = len(outMap[0]) - 1
	leftDir = (direction-1)%4
	print(leftDir)
	rightDir = (direction+1)%4
	print(rightDir)
	leftPos = getPos(leftDir,pos)
	rightPos = getPos(rightDir,pos)
	if 0 <= leftPos[0] <= maxy and 0 <= leftPos[1] <= maxx:
		if outMap[leftPos[0]][leftPos[1]] == '#':
			return (leftDir, 'L')
	if 0 <= rightPos[0] <= maxy and 0 <= rightPos[1] <= maxx:
		if outMap[rightPos[0]][rightPos[1]] == '#':
			return (rightDir, 'R')
	return(0,'SLUT')

	

intcode = open('2019/17/input','r')
code = intcode.read()
intcode.close()
codeList = [ int(x) for x in code.split(',')]

intComp = IntComputer(codeList.copy(), toPrint = 0)
inputs = []
output = intComp.runProgram(inputs)
outMap = []
inList = []
for asci in output:
	if asci != 10:
		inList.append(chr(asci))
	else:
		outMap.append(inList)
		inList = []
"""
outMap = []
outMap.append('..#..........')
outMap.append('..#..........')
outMap.append('#######...###')
outMap.append('#.#...#...#.#')
outMap.append('#############')
outMap.append('..#...#...#..')
outMap.append('..#####...^..')
"""
startPos = (0,0)
alignment = 0
numScaffold = 0
for y in range(len(outMap)):
	if y > 0 and y < len(outMap) - 2:
		for x in range(len(outMap[y])):
			if x > 0 and x < len(outMap[y])-2:
				if outMap[y][x] == '#':
					numScaffold += 1
					if outMap[y-1][x] == '#' and outMap[y+1][x] == '#' and outMap[y][x-1] == '#' and outMap[y][x+1] == '#':
						alignment += (x)*(y)
				elif outMap[y][x] == '^':
					startPos = (y,x)


print(alignment)
print(numScaffold)

maxy = len(outMap) - 2
maxx = len(outMap[0]) - 1

direction = 0
commands = []
pos = startPos
moreToRemove = True
while moreToRemove:
	#print(numScaffold)
	direction, turn = findTurn(direction, outMap, pos)
	#print(direction)
	#print(turn)
	if turn == "SLUT":
		moreToRemove = False
		break
	moveForward = True
	stepsForward = 0
	while moveForward:
		newPos = getPos(direction,pos)
		if 0 <= newPos[0] <= maxy and 0 <= newPos[1] <= maxx:
			if outMap[newPos[0]][newPos[1]] == '#':
				numScaffold -= 1
				stepsForward += 1
				pos = newPos
			else:
				moveForward = False
		else:
			moveForward = False
	commands.append(turn + str(stepsForward))
	
foundCompression = False
lenA = 1
lenB = 1
lenC = 1
print(commands)
while not foundCompression:
	head = 0
	compressedVals = [0]*len(commands)
	partA = commands[:lenA]
	compressedVals[:lenA] = [1]*lenA
	head += lenA
	for i in range(head, len(commands)):
		if partA == commands[i:i+lenA] and not sum(compressedVals[i:i+lenA]):
			compressedVals[i:i+lenA] = [1]*lenA
	print(compressedVals)
	head = compressedVals.index(0)
	partB = commands[head:head+lenB]
	print(partB)
	if not sum(compressedVals[head:head+lenB]):
		compressedVals[head:head+lenB] = [1]*lenB
		head += lenB
		for i in range(head, len(commands)):
			if partB == commands[i:i+lenB] and not sum(compressedVals[i:i+lenB]):
				compressedVals[i:i+lenB] = [1]*lenB
	print(compressedVals)
	head = compressedVals.index(0)
	partC = commands[head:head+lenC]
	print(partC)
	if not sum(compressedVals[head:head+lenC]):
		compressedVals[head:head+lenC] = [1]*lenC
		head += lenC
		for i in range(head, len(commands)):
			if partC == commands[i:i+lenC] and not sum(compressedVals[i:i+lenC]):
				compressedVals[i:i+lenC] = [1]*lenC
	print(compressedVals)
	
	if sum(compressedVals) == len(compressedVals):
		print('DONE')
		foundCompression = True
	else:
		if lenC < 10:
			lenC += 1
		else:
			lenC = 1
			if lenB < 10:
				lenB += 1
			else:
				lenB = 1
				if lenA < 10:
					lenA += 1
				else:
					print('PROBLEM')
					foundCompression = True

instructionOrder = []
head = 0
while head < len(commands):

	if commands[head:head+lenA] == partA:
		instructionOrder.append('A')
		head += lenA
	elif commands[head:head+lenB] == partB:
		instructionOrder.append('B')
		head += lenB
	elif commands[head:head+lenC] == partC:
		instructionOrder.append('C')
		head += lenC
print(instructionOrder)
inputInstructions = []
for instruction in instructionOrder:
	inputInstructions.append(ord(instruction))
	inputInstructions.append(ord(','))
inputInstructions.pop()
inputInstructions.append(10)

programA = []
for part in partA:
	ch1 = part[0]
	programA.append(ord(ch1))
	programA.append(ord(','))
	ch2 = part[1:]
	for chr in ch2:
		programA.append(ord(chr))
	programA.append(ord(','))
programA.pop()
programA.append(ord('\n'))

programB = []
for part in partB:
	ch1 = part[0]
	programB.append(ord(ch1))
	programB.append(ord(','))
	ch2 = part[1:]
	for chr in ch2:
		programB.append(ord(chr))
	programB.append(ord(','))
programB.pop()
programB.append(ord('\n'))

programC = []
for part in partC:
	ch1 = part[0]
	programC.append(ord(ch1))
	programC.append(ord(','))
	ch2 = part[1:]
	for chr in ch2:
		programC.append(ord(chr))
	programC.append(ord(','))
programC.pop()
programC.append(ord('\n'))

inputs = []

inputs.extend(inputInstructions)
inputs.extend(programA)
inputs.extend(programB)
inputs.extend(programC)
inputs.extend([ord('n'),10])
codeList[0] = 2
intComp = IntComputer(codeList.copy(), toPrint = 0)
output = intComp.runProgram(inputs)
print(output)

print(inputInstructions)
print(programA)
print(programB)
print(programC)