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
				length = 1
				while 0 <= row + i * length < nrows and 0 <= col + j * length < ncols:
					if seats[row + i * length][col + j * length] == '#':
						return 'L', False
						break
					elif seats[row + i * length][col + j * length] == 'L':
						break
					length += 1
		return '#', True
	elif seats[row][col] == '#':
		numOcc = 0
		for i in [-1, 0, 1]:
			for j in [-1, 0, 1]:
				if i == 0 and j == 0:
					continue
				length = 1
				while 0 <= row + i * length < nrows and 0 <= col + j * length < ncols:
					if seats[row + i * length][col + j * length] == '#':
						numOcc += 1
						break
					elif seats[row + i * length][col + j * length] == 'L':
						break
					length += 1
		if numOcc >= 5:
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

