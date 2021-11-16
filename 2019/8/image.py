#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Dec  8 11:32:16 2019

@author: johanalenlov
"""

image = open('2019/8/input', 'r')
imageData = image.read()
image.close()
#imageData = '0222112222120000'
imageData = [int(char) for char in imageData]

width = 25
height = 6
pixelsPerLayer = width*height
totalPixels = len(imageData)
totalLayers = int(totalPixels/pixelsPerLayer)
maxZeros = pixelsPerLayer
maxVal = 0
layer = 0
finalImage = [None]*pixelsPerLayer
for l in range(totalLayers):
	num = [0,0,0]
	for i in range(pixelsPerLayer):
		position = l*pixelsPerLayer + i
		valueAtPixel = imageData[position]
		if finalImage[i] == None:
			if valueAtPixel != 2:
				finalImage[i] = valueAtPixel
		if valueAtPixel in range(3):
			num[valueAtPixel] += 1
	print('Layer {}, num zeros {}, value {}'.format(l,num[0],num[1]*num[2]))
	if num[0] < maxZeros:
		layer = l
		maxZeros = num[0]
		maxVal = num[1]*num[2]

for h in range(height):
	for w in range(width):
		if finalImage[h*width + w]:
			print('1', end = '')
		else:
			print(' ', end = '')
		#print(finalImage[h*width + w], end = '')
	print('')