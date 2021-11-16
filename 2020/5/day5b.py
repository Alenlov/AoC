import numpy as np

def binToInt(s):
	n = len(s)-1
	val = 0
	for c in s:
		val += int(c)*(2**n)
		n -= 1
	return val

with open("input.txt") as f:
	seats = f.read().splitlines()

takenSeats = np.zeros(127*8+7)

maxSeatID = 0
minSeatID = 127*8+7
for seat in seats:
	row = seat[:7].replace("B", "1").replace("F", "0")
	column = seat[7:].replace("R", "1").replace("L", "0")
	seatID = binToInt(row)*8 + binToInt(column)
	takenSeats[seatID] = 1
	if seatID > maxSeatID:
		maxSeatID = seatID
	elif seatID < minSeatID:
		minSeatID = seatID

for id in range(minSeatID,maxSeatID+1):
	if takenSeats[id] == 0:
		if takenSeats[id - 1] == 1 and takenSeats[id + 1] == 1:
			print(id)
			break



'''
B = 1
F = 0
R = 1
L = 0
'''