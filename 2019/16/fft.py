#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Dec 16 13:54:37 2019

@author: johanalenlov
"""

#startingNumber = "59708072843556858145230522180223745694544745622336045476506437914986923372260274801316091345126141549522285839402701823884690004497674132615520871839943084040979940198142892825326110513041581064388583488930891380942485307732666485384523705852790683809812073738758055115293090635233887206040961042759996972844810891420692117353333665907710709020698487019805669782598004799421226356372885464480818196786256472944761036204897548977647880837284232444863230958576095091824226426501119748518640709592225529707891969295441026284304137606735506294604060549102824977720776272463738349154440565501914642111802044575388635071779775767726626682303495430936326809"
#startingNumber = "80871224585914546619083218645595"

file = open('2019/16/input','r')
startingNumber = file.read().splitlines()[0]
file.close()

def createMultiplicationDict(lenOfNumber):
	multDict = {}
	for i in range(lenOfNumber):
		multList = []
		order = [0,1,0,-1]
		while len(multList) < lenOfNumber+2:
			operator = order.pop(0)
			multList.extend([operator]*(i+1))
			order.append(operator)
		multDict[i] = multList[1:lenOfNumber+1]
	return multDict


def onePhase(inList, multDict):
	outList = [0]*len(inList)
	for i in range(len(outList)):
		for j in range(len(inList)):
			outList[i] += inList[j]*multDict[i][j]
		outList[i] = abs(outList[i])%10
		
	return outList
		
startingList = [int(x) for x in startingNumber]
print(startingList)
theList = startingList.copy()
multDict = createMultiplicationDict(len(startingList))

numPhases = 100
for i in range(numPhases):
	theList = onePhase(theList,multDict)
	
print(theList[:8])


