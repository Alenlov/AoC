#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  4 09:40:26 2019

@author: johanalenlov
"""
import math
totalFuel = 0

fuel = math.floor(100756/3) - 2
totalFuel += fuel
while fuel > 0:
	fuel = math.floor(fuel/3) - 2
	if fuel > 0:
		totalFuel += fuel
print(totalFuel)