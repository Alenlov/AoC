import time as tme

sT = tme.time()
with open("13/input.txt") as f:
	timetable = f.read().splitlines()

arrivalTime = int(timetable[0])
busIds = timetable[1].split(',')
busPairs = []
timeCounter = 0
for id in busIds:
	if id != 'x':
		busPairs.append((int(id), -timeCounter))
	timeCounter+=1

startTime = 0
multiplier = 1
for (id, time) in busPairs:
	while True:
		if (startTime % id) == (time % id):
			multiplier *= id
			break
		else:
			startTime += multiplier


print(startTime)
print(tme.time() - sT)