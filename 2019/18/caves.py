#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 18 14:29:29 2019

@author: johanalenlov
"""
from queue import SimpleQueue

def makeMove(pos, explored, map):
	if pos not in explored:
		mapVal = map[pos[0]][pos[1]]
		if mapVal != '#':
			if mapVal in keys and mapVal not in pos[2]:
				newPosKeys = ''.join(sorted(pos[2] + mapVal))
				pos = (pos[0], pos[1], newPosKeys)
				return [pos]
			elif mapVal in doors:
				#print(mapVal)
				#print(chr(ord(mapVal) + 32))
				#print(pos[2])
				if chr(ord(mapVal) + 32) in pos[2]:
					return [pos]
			else:
				return [pos]
	return []

def freeSpots(pos,map,explored):
	pos1 = (pos[0], pos[1] + 1, pos[2])
	pos2 = (pos[0], pos[1] - 1, pos[2])
	pos3 = (pos[0] - 1, pos[1], pos[2])
	pos4 = (pos[0] + 1, pos[1], pos[2])
	freeDir = []
	#print(pos)
	#print(map[pos[0]][pos[1]])
	freeDir.extend(makeMove(pos1, explored, map))
	freeDir.extend(makeMove(pos2, explored, map))
	freeDir.extend(makeMove(pos3, explored, map))
	freeDir.extend(makeMove(pos4, explored, map))
	return freeDir

def exploreCave(pos, map):
	heads = SimpleQueue()
	heads.put(pos)
	explored = {pos : 0}
	running = True
	while running:
		toMove = heads.get()
		newHeads = freeSpots(toMove, map, explored)
		for head in newHeads:
			heads.put(head)
			explored[head] = explored[toMove] + 1
			if len(head[2]) == len(keys):
				print('ALLA NYCKLAR i {} steg'.format(explored[head]))
				running = False

		if heads.empty():
			running = False	
	return explored




mapFile = open('2019/18/input', 'r')
mapRaw = mapFile.read().splitlines()
mapFile.close()

numy = len(mapRaw)
numx = len(mapRaw[0])

mapAscii = []
wall = ord('#')
path = ord('.')
start = ord('@')
doors = []
keys = []
for y in range(len(mapRaw)):
	mapRaw[y] = [char for char in mapRaw[y]]

for y in range(len(mapRaw)):
	for x in range(len(mapRaw[y])):
		char = mapRaw[y][x]
		value = ord(char)
		if 65 <= value <= 90:
			doors.append(char)
		if 97 <= value <= 122:
			keys.append(char)
		if value == start:
			startPos = (y,x,'')
keys.sort()
print(keys)
explored = exploreCave(startPos, mapRaw)
print(len(explored))
# for y in range(len(mapRaw)):
# 	for x in range(len(mapRaw[y])):
# 		char = mapRaw[y][x]
# 		if (y,x) in explored:
# 			print(explored[(y,x)],end='')
# 		else:
# 			print(char,end='')
# 	print('')
