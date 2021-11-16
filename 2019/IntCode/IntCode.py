#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 11 07:30:27 2019

@author: johanalenlov
"""

class IntComputer():
	def __init__(self, codeList):
		self.codeList = codeList
		self.length = len(codeList)
		self.inputs = []
		self.head = 0
		self.relBase = 0
		self.done = False
		self.numInstructions = 0
		
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
		runNew = 0
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
					print('Input : {}'.format(val1))
					pos1 = self.getPos(mode1,head+1)
					self.codeList[pos1] = val1
					head += 2
				else:
					#print('Waiting for input')
					self.runing = False
					runNew = 1
					break
			elif opCode == 4:
				val1 = self.getVal(mode1,head+1)
				print('Output : {}'.format(val1))
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
				runNew = 0
				break
			else:
				print('Error!, head = {}'.format(head))
		self.head = head
		return (outputs, runNew)

