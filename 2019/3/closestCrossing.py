#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec  5 13:56:40 2019

@author: johanalenlov
"""
import math

f = open('2019/3/input','r')

descrip1 = f.readline().split(',')

descrip2 = f.readline().split(',')

wire1 = []
#wire2 = []
wire1cur = [0,0]
wire2cur = [0,0]
wire1.append(wire1cur.copy())
#wire2.append(wire2cur.copy())


#descrip1 = 'R75,D30,R83,U83,L12,D49,R71,U7,L72'.split(',')
#descrip2 = 'U62,R66,U55,R34,D71,R55,D58,R83'.split(',')
maxDist = 0
for path in descrip1:
	direction = path[0]
	length = int(path[1:])
	for i in range(length):
		if direction == 'D':
			wire1cur[1] -= 1
		elif direction == 'U':
			wire1cur[1] += 1
		elif direction == 'R':
			wire1cur[0] += 1
		elif direction == 'L':
			wire1cur[0] -= 1
		wire1.append(wire1cur.copy())
	distance = abs(wire1cur[0]) + abs(wire1cur[1])
	if distance > maxDist:
		maxDist = distance
distList = []
minDist = maxDist
indx = 0
for path in descrip2:
	indx += 1
	print(indx)
	direction = path[0]
	length = int(path[1:])
	for i in range(length):
		if direction == 'D':
			wire2cur[1] -= 1
		elif direction == 'U':
			wire2cur[1] += 1
		elif direction == 'R':
			wire2cur[0] += 1
		elif direction == 'L':
			wire2cur[0] -= 1
		distance = abs(wire2cur[0]) + abs(wire2cur[1])
		if distance < minDist:
			if wire2cur in wire1:
				distList.append(distance)
				minDist = distance
				print(minDist)

print(minDist)