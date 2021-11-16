#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 12 08:23:46 2019

@author: johanalenlov
"""

class Moon():
	def __init__(self, pos):
		self.pos = pos
		self.vel = [0,0,0]
	
	def changeVel(self, moon):
		for dim in range(3):
			if self.pos[dim] > moon.pos[dim]:
				self.vel[dim] -= 1
			elif self.pos[dim] < moon.pos[dim]:
				self.vel[dim] += 1
	
	def moveMoon(self):
		for dim in range(3):
			self.pos[dim] += self.vel[dim]
			
	def calcPotEnergy(self):
		pot = 0
		for dim in range(3):
			pot += abs(self.pos[dim])
		return pot
	
	def calcKinEnergy(self):
		kin = 0
		for dim in range(3):
			kin += abs(self.vel[dim])
		return kin
			
	def calcTotEnergy(self):
		return self.calcPotEnergy() * self.calcKinEnergy()
	
	def __str__(self):
		return 'pos=<x={}, y={}, z={}> vel=<x={}, y={}, z={}>'.format(self.pos[0],self.pos[1],self.pos[2],self.vel[0],self.vel[1],self.vel[2])

moonMapFile = open('2019/12/input', 'r')
moonMapRaw = moonMapFile.read().splitlines()
moonMapFile.close()

numMoons = len(moonMapRaw)
moons = []
for moon in moonMapRaw:
	startPos = [0,0,0]
	moonSplit = moon[1:-1].split(', ')
	for dim in range(3):
		startPos[dim] = int(moonSplit[dim].split('=')[1])
	moons.append(Moon(startPos))

maxSimul = 1000
for simul in range(maxSimul)	:
	if simul % 100 == 0:
		print('After {} steps'.format(simul))
		for moon in moons:
			print(moon)
	for moon1 in moons:
		for moon2 in moons:
			if moon1 != moon2:
				moon1.changeVel(moon2)
	
	for moon in moons:
		moon.moveMoon()

print('After {} steps'.format(maxSimul))
totalEnergy = 0
for moon in moons:
	moonEnergy = moon.calcTotEnergy()
	totalEnergy += moonEnergy
	print('{} with energy {}'.format(moon, moon.calcTotEnergy()))
print('Total energy = {}'.format(totalEnergy))
