#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 12 08:23:46 2019

@author: johanalenlov
"""

def lcm(a,b,c):
	lcm1 = int(a * b / gcd(a,b))
	lcm2 = int(lcm1 * c / gcd(lcm1,c))
	return lcm2
	
	
def gcd(a,b):
	if b == 0:
		return a
	else:
		return gcd(b, a % b)

	
class Universe():
	def __init__(self, pos):
		self.pos = pos
		self.vel = [0]*len(pos)
		self.history = {}
		self.history[self.totEnergy()] = []
		self.history[self.totEnergy()].append(self.pos + self.vel)

	def calcPotEnergy(self):
		pot = 0
		for pos in self.pos:
			pot += abs(pos)
		return pot
	
	def calcKinEnergy(self):
		kin = 0
		for vel in self.vel:
			kin += abs(vel)
		return kin
	
	def totEnergy(self):
		return self.calcPotEnergy() * self.calcKinEnergy()
	
	def updateVel(self):
		for dim1 in range(len(self.pos)):
			for dim2 in range(len(self.pos)):
				if dim1 != dim2:
					if self.pos[dim1] > self.pos[dim2]:
						self.vel[dim1] -= 1
					elif self.pos[dim1] < self.pos[dim2]:
						self.vel[dim1] += 1
	
	def move(self):
		for dim in range(len(self.pos)):
			self.pos[dim] += self.vel[dim]
	
	def simulate(self):
		self.updateVel()
		self.move()
		
		posSum = self.pos + self.vel
		totEnergy = self.totEnergy()

		if totEnergy in self.history:
			if posSum in self.history[totEnergy]:
				return True
			else:
				self.history[totEnergy].append(posSum)
				return False
		else:
			self.history[totEnergy] = []
			self.history[totEnergy].append(posSum)
			return False



moonMapFile = open('2019/12/input', 'r')
moonMapRaw = moonMapFile.read().splitlines()
moonMapFile.close()

numMoons = len(moonMapRaw)
xstart = []
ystart = []
zstart = []
for moon in moonMapRaw:
	startPos = [0,0,0]
	moonSplit = moon[1:-1].split(', ')
	
	xstart.append(int(moonSplit[0].split('=')[1]))
	ystart.append(int(moonSplit[1].split('=')[1]))
	zstart.append(int(moonSplit[2].split('=')[1]))

xUniv = Universe(xstart)
yUniv = Universe(ystart)
zUniv = Universe(zstart)

xRepeat = 0
repeated = 0
while not repeated:
	xRepeat += 1
	repeated = xUniv.simulate()

yRepeat = 0
repeated = 0
while not repeated:
	yRepeat += 1
	repeated = yUniv.simulate()

zRepeat = 0
repeated = 0
while not repeated:
	zRepeat += 1
	repeated = zUniv.simulate()
	
print(lcm(xRepeat,yRepeat,zRepeat))







