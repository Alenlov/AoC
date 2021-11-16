#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Dec 14 09:46:36 2019

@author: johanalenlov
"""

import math

class Reaction():
	def __init__(self, inMats, outCount):
		self.inMats = inMats
		self.outCount = outCount
		self.extra = 0
	
	def produce(self, numToProduce):
		needed = numToProduce - self.extra
		productionRecipe = {}
		if needed <= 0:
			self.extra -= numToProduce
			return productionRecipe
		
		runs = math.ceil(needed/self.outCount)
		self.extra = runs*self.outCount - needed
		for inMat in self.inMats:
			productionRecipe[inMat] = self.inMats[inMat]*runs
		return productionRecipe


reactionsFile = open('2019/14/input', 'r')
reactionsRaw = reactionsFile.read().splitlines()
reactionsFile.close()

reactionDict = {}
neededDict = {'ORE' : 0}
for reaction in reactionsRaw:
	[inMats, outMats] = reaction.split(" => ")
	[outCount, outMat] = outMats.split(' ')
	outCount = int(outCount)
	inMats = inMats.split(', ')
	inDict = {}
	for inMatLine in inMats:
		[inCount, inMat] = inMatLine.split(' ')
		inCount = int(inCount)
		inDict[inMat] = inCount
	reactionDict[outMat] = Reaction(inDict,outCount)
	neededDict[outMat] = 0

orePerFuel = 0
toProduceDict = reactionDict['FUEL'].produce(1)
notDone = True
while notDone:
	newToProduceDict = {'ORE':0}
	for product in toProduceDict:
		number = toProduceDict[product]
		if product != 'ORE':
			newProductsToProduce = reactionDict[product].produce(number)
			for newProduct in newProductsToProduce:
				if newProduct in newToProduceDict:
					newToProduceDict[newProduct] += newProductsToProduce[newProduct]
				else:
					newToProduceDict[newProduct] = newProductsToProduce[newProduct]
		else:
			newToProduceDict[product] += number
	if len(newToProduceDict) == 1:
		notDone = False
	toProduceDict = newToProduceDict

print(newToProduceDict)
		


oreLeft = 1000000000000
orePerFuel = newToProduceDict['ORE']
neededDict['FUEL'] = oreLeft // orePerFuel
totalFuel = 0
while neededDict['FUEL']:
	runing = True
	fuelProduced = neededDict['FUEL']
	while runing:
		runing = False
		for product in neededDict:
			if neededDict[product] > 0 and product != 'ORE':
				runing = True
				produceDict = reactionDict[product].produce(neededDict[product])
				neededDict[product] = 0
				for material in produceDict:
					neededDict[material] += produceDict[material]

	oreLeft -= neededDict['ORE']
	neededDict['ORE'] = 0
	neededDict['FUEL'] = oreLeft // orePerFuel
	if oreLeft > 0:
		totalFuel += fuelProduced

print('Produced {} FUEL'.format(totalFuel))
		
		
		
		