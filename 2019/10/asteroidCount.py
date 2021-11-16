#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 10 08:29:47 2019

@author: johanalenlov
"""

import math

def gcd(a,b):
	if b == 0:
		return a
	else:
		return gcd(b, a % b)

def sign(x):
	if x > 0:
		return 1
	elif x < 0:
		return -1
	else:
		return 0

def calcTheta(x,y):
	if x == 0:
		return math.pi/2*sign(y) + math.pi/2
	elif x > 0:
		return math.atan(y/x) + math.pi/2
	elif x < 0:
		return math.atan(y/x) + math.pi*3/2

def asteroidDist(pos1, pos2):
	return abs(pos2[0] - pos1[0]) + abs(pos2[1] - pos1[1])

asteroidMapFile = open('2019/10/input', 'r')
asteroidMapRaw = asteroidMapFile.read().splitlines()
asteroidMapFile.close()
asteroidMap = {}
maxX = len(asteroidMapRaw[0]) - 1
maxY = len(asteroidMapRaw) - 1
y = 0
for row in asteroidMapRaw:
	x = 0
	for asteroid in row:
		if asteroid == '#':
			asteroidMap[(x,y)] = 0
		x += 1
	y += 1

maxSeen = 0

for pos in asteroidMap:
	asteroidVecs = {}
	(x_curr, y_curr) = pos
	for new_pos in asteroidMap:
		if new_pos != pos:
			(x_new, y_new) = new_pos
			vec_x = x_new - x_curr
			vec_y = y_new - y_curr
			divisor = abs(gcd(vec_x,vec_y))
			norm_vec_x = int(vec_x/divisor)
			norm_vec_y = int(vec_y/divisor)
			norm_vec = (norm_vec_x, norm_vec_y)
			if norm_vec not in asteroidVecs:
				asteroidVecs[norm_vec] = new_pos
			else:
				distance_old = asteroidDist(pos, asteroidVecs[norm_vec])
				distance_new = asteroidDist(pos, new_pos)
				if distance_new < distance_old:
					asteroidVecs[norm_vec] = new_pos

	asteroidMap[pos] = asteroidVecs
	if len(asteroidMap[pos]) > maxSeen:
		maxSeen = len(asteroidMap[pos])
		maxPos = pos

print('Best is {} with {} seen asteroids'.format(maxPos,maxSeen))
theta_vec = []
for obs_vec in asteroidMap[maxPos]:
	(vec_x, vec_y) = obs_vec
	theta = calcTheta(vec_x, vec_y)
	theta_vec.append((theta, obs_vec))
toRemove = 200
theta_vec_sorted = sorted(theta_vec, key = lambda theta: theta[0])
(theta, vec) = theta_vec_sorted[toRemove - 1]
pos = asteroidMap[maxPos][vec]
print('Asteroid {} to be removed is at pos {}'.format(toRemove, pos))
