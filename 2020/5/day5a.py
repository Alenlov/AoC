def binToInt(s):
	n = len(s)-1
	val = 0
	for c in s:
		val += int(c)*(2**n)
		n -= 1
	return val

with open("input.txt") as f:
	seats = f.read().splitlines()


maxSeatID = 0
for seat in seats:
	row = seat[:7].replace("B", "1").replace("F", "0")
	column = seat[7:].replace("R", "1").replace("L", "0")
	seatID = binToInt(row)*8 + binToInt(column)
	if seatID > maxSeatID:
		maxSeatID = seatID

print(maxSeatID)



'''
B = 1
F = 0
R = 1
L = 0
'''