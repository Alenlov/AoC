def updateSeat(row,col,seats):
	nrows = len(seats)
	ncols = len(seats[0])
	if seats[row][col] == '.':
		return '.', False
	elif seats[row][col] == 'L':

		for i in [-1, 0, 1]:
			for j in [-1, 0, 1]:
				if i == 0 and j == 0:
					continue
				elif row + i < 0 or col + j < 0 or row + i >= nrows or col + j >= ncols:
					continue
				else:
					if seats[row+i][col+j] == '#':
						return 'L', False
		return '#', True
	elif seats[row][col] == '#':
		numOcc = 0
		for i in [-1, 0, 1]:
			for j in [-1, 0, 1]:
				if i == 0 and j == 0:
					continue
				elif row + i < 0 or col + j < 0 or row + i >= nrows or col + j >= ncols:
					continue
				else:
					if seats[row+i][col+j] == '#':
						numOcc += 1
		if numOcc >= 4:
			return 'L', True
		else:
			return '#', False

with open("input.txt") as f:
	seats = f.read().splitlines()

change = True
while change:
	change = False
	newSeats = seats.copy()
	for i in range(len(seats)):
		for j in range(len(seats[0])):
			seatVal, seatChange = updateSeat(i,j,seats)
			if seatChange:
				newSeats[i] = newSeats[i][:j] + seatVal + newSeats[i][j+1:]
			change = change or seatChange
	seats = newSeats

numOcc = 0
for i in range(len(seats)):
	for j in range(len(seats[0])):
		if seats[i][j] == '#':
			numOcc += 1

print(numOcc)

