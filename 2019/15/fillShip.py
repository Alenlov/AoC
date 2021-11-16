#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Dec 15 11:21:25 2019

@author: johanalenlov
"""

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
	