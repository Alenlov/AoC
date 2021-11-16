#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  4 09:14:07 2019

@author: johanalenlov
"""
import math

totalFuel = 0
masses = open('2019/1/input', 'r')
mass = masses.readline()
while mass:
	fuel = math.floor(int(mass)/3) - 2
	totalFuel += fuel
	while fuel > 0:
		fuel = math.floor(fuel/3) - 2
		if fuel > 0:
			totalFuel += fuel
	mass = masses.readline()
	

print(totalFuel)
masses.close()
