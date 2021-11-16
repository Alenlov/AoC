#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  6 08:14:25 2019

@author: johanalenlov
"""

class OrbitNode():
	
	def __init__(self, name, numOrbits = 0):
		self.name = name
		self.numOrbits = numOrbits
		self.orbits = []
		self.parent = ''
	
	def addNewOrbit(self, star):
		newNode = OrbitNode(star, self.numOrbits+1)
		newNode.setParent(self)
		self.orbits.append(newNode)
		return newNode
	
	def addExistingOrbit(self, node):
		self.orbits.append(node)
		node.setParent(self)
		node.addOrbit(self.numOrbits + 1)
	
	def addOrbit(self, numOrbits):
		self.numOrbits += numOrbits
		for node in self.orbits:
			node.addOrbit(numOrbits)
	
	def setParent(self, parent):
		self.parent = parent
	
	def totalOrbits(self):
		totOrbits = self.numOrbits
		for node in self.orbits:
			totOrbits += node.totalOrbits()
		return totOrbits
	
	def lengthTo(self, nameToFind, originName = ''):
		if self.name == nameToFind:
			length = 1
		else:
			length = 0
			if self.parent:
				if not self.parent.name == originName:
					length += self.parent.lengthTo(nameToFind, self.name)
				for node in self.orbits:
					if not node.name == originName:
						length += node.lengthTo(nameToFind, self.name)
				if length > 0 and originName != '':
					length += 1
			
		#print('Name = {}, length = {}'.format(self.name,length))
		return length


orbitList = open('2019/6/input', 'r')
orbits = orbitList.read().splitlines()
orbitList.close()

orbitMap = {}

for orbit in orbits:
	stars = orbit.split(')')
	#print('{} moving around {}'.format(stars[1],stars[0]))
	if stars[0] not in orbitMap:
		fixed = OrbitNode(stars[0])
		orbitMap[stars[0]] = fixed
	else:
		fixed = orbitMap[stars[0]]
	
	if stars[1] not in orbitMap:
		moving = fixed.addNewOrbit(stars[1])
		orbitMap[stars[1]] = moving
	else:
		fixed.addExistingOrbit(orbitMap[stars[1]])


for star in orbitMap:
	print('{} has {} orbits'.format(star, orbitMap[star].numOrbits))
	

print(orbitMap['COM'].totalOrbits())
print(orbitMap[orbitMap['YOU'].parent.name].lengthTo(orbitMap['SAN'].parent.name))