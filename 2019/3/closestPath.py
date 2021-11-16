#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec  5 13:56:40 2019

@author: johanalenlov
"""

f = open('2019/3/input','r')

descrip1 = f.readline().split(',')

descrip2 = f.readline().split(',')
f.close()
#wire1 = []
#wire2 = []
wire1curx = 0
wire1cury = 0
wire2curx = 0
wire2cury = 0
#wire1.append(wire1cur.copy())
#wire2.append(wire2cur.copy())
wire1dict = {}
wire2dict = {}
steps = 0
#wire2dict = {}

#descrip1 = 'R75,D30,R83,U83,L12,D49,R71,U7,L72'.split(',')
#descrip2 = 'U62,R66,U55,R34,D71,R55,D58,R83'.split(',')

#descrip1 = 'R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51'.split(',')
#descrip2 = 'U98,R91,D20,R16,D67,R40,U7,R15,U6,R7'.split(',')
for path in descrip1:
	direction = path[0]
	length = int(path[1:])
	for i in range(length):
		steps += 1
		if direction == 'D':
			wire1cury -= 1
		elif direction == 'U':
			wire1cury += 1
		elif direction == 'R':
			wire1curx += 1
		elif direction == 'L':
			wire1curx -= 1
		distance = abs(wire1curx) + abs(wire1cury)
		if distance not in wire1dict:
			wire1dict[distance] = {}
			wire1dict[distance][(wire1curx,wire1cury)] = steps
		else:
			if (wire1curx,wire1cury) not in wire1dict[distance]:
				wire1dict[distance][(wire1curx,wire1cury)] = steps


totalSteps = []
steps = 0
indx = 0
for path in descrip2:
	indx += 1
	print(indx)
	direction = path[0]
	length = int(path[1:])
	for i in range(length):
		steps += 1
		if direction == 'D':
			wire2cury -= 1
		elif direction == 'U':
			wire2cury += 1
		elif direction == 'R':
			wire2curx += 1
		elif direction == 'L':
			wire2curx -= 1
		distance = abs(wire2curx) + abs(wire2cury)
		if distance not in wire2dict:
			wire2dict[distance] = {}
			wire2dict[distance][(wire2curx,wire2cury)] = steps
		else:
			if (wire2curx,wire2cury) not in wire2dict[distance]:
				wire2dict[distance][(wire2curx,wire2cury)] = steps
		if distance in wire1dict:
			if (wire2curx, wire2cury) in wire1dict[distance]:
				totalSteps.append(steps + wire1dict[distance][(wire2curx, wire2cury)])

print(sorted(totalSteps))