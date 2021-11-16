#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec 18 14:29:29 2019

@author: johanalenlov
"""
from queue import SimpleQueue

def makeMove(pos, explored, map):
	if pos not in explored:
		active = pos[5]
		collectedKeys = pos[4]
		currPos = pos[active]
		mapVal = map[currPos[0]][currPos[1]]
		if mapVal != '#':
			if mapVal in keys and mapVal not in collectedKeys:
				print('We have found key {}'.format(mapVal))
				return newPos(pos, (0,0), mapVal)
			elif mapVal in doors:
				if chr(ord(mapVal) + 32) in collectedKeys:
					print('We opened door {}'.format(mapVal))
					return [pos]
			else:
				return [pos]
	return []

def newPos(pos, diff, newKey):
	if not newKey:
		active = pos[5]
		parts = []
		for i in range(4):
			if i == active:
				newY = pos[i][0] + diff[0]
				newX = pos[i][1] + diff[1]
				parts.append((newY, newX))
			else:
				parts.append(pos[i])
		return (parts[0], parts[1], parts[2], parts[3], pos[4], pos[5])
	else:
		print('We had {} and we add {}'.format(pos[4], newKey))
		newPosKeys = ''.join(sorted(pos[4] + newKey))
		print('We now have {}'.format(newPosKeys))
		newPoses = []
		for i in range(4):
			newPoses.append((pos[0], pos[1], pos[2], pos[3], newPosKeys, i))
		return newPoses

def freeSpots(pos,map,explored):
	pos1 = newPos(pos, (1,0), '')
	pos2 = newPos(pos, (-1,0), '')
	pos3 = newPos(pos, (0,1), '')
	pos4 = newPos(pos, (0,-1), '')
	freeDir = []
	#print(pos3)
	#print(explored)
	freeDir.extend(makeMove(pos1, explored, map))
	freeDir.extend(makeMove(pos2, explored, map))
	freeDir.extend(makeMove(pos3, explored, map))
	freeDir.extend(makeMove(pos4, explored, map))
	return freeDir

def exploreCave(posList, map):
	heads = SimpleQueue()
	#SET ALL ROBOTS ACTIVE AT START
	explored = {}
	for pos in posList:
		heads.put(pos)
		explored[pos] = 0
	running = True
	while running:
		#print(len(explored))
		toMove = heads.get()
		newHeads = freeSpots(toMove, map, explored)
		for head in newHeads:
			heads.put(head)
			explored[head] = explored[toMove] + 1
			if len(head[4]) == len(keys):
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
startNotFound = True
for y in range(len(mapRaw)):
	for x in range(len(mapRaw[y])):
		char = mapRaw[y][x]
		value = ord(char)
		if 65 <= value <= 90:
			doors.append(char)
		if 97 <= value <= 122:
			keys.append(char)
		if value == start and startNotFound:
			mapRaw[y][x] = '#'
			mapRaw[y-1][x] = '#'
			mapRaw[y+1][x] = '#'
			mapRaw[y][x+1] = '#'
			mapRaw[y][x-1] = '#'
			mapRaw[y-1][x-1] = '@'
			mapRaw[y+1][x+1] = '@'
			mapRaw[y-1][x+1] = '@'
			mapRaw[y+1][x-1] = '@'
			startPos1 = ( (y-1,x-1), (y+1,x+1), (y-1,x+1), (y+1, x-1), '', 0) #POS robot 1, 2, 3, 4, keys, active
			startPos2 = ( (y-1,x-1), (y+1,x+1), (y-1,x+1), (y+1, x-1), '', 1) #POS robot 1, 2, 3, 4, keys, active
			startPos3 = ( (y-1,x-1), (y+1,x+1), (y-1,x+1), (y+1, x-1), '', 2) #POS robot 1, 2, 3, 4, keys, active
			startPos4 = ( (y-1,x-1), (y+1,x+1), (y-1,x+1), (y+1, x-1), '', 3) #POS robot 1, 2, 3, 4, keys, active
			startNotFound = False
			startPos = [startPos1, startPos2, startPos3, startPos4]

#keys.sort()
#print(keys)
explored = exploreCave(startPos, mapRaw)
# for y in range(len(mapRaw)):
# 	for x in range(len(mapRaw[y])):
# 		char = mapRaw[y][x]
# 		print(char,end='')
# 	print('')
