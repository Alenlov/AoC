with open("13/input.txt") as f:
	timetable = f.read().splitlines()

arrivalTime = int(timetable[0])
busIds = timetable[1].split(',')
shortestWait = arrivalTime
bestId = 0
for id in busIds:
	if id == 'x':
		continue
	timeToWait = (int(arrivalTime/int(id))+1)*int(id) - arrivalTime
	if timeToWait < shortestWait:
		shortestWait = timeToWait
		bestId = int(id)

print(shortestWait)
print(bestId)
print(shortestWait*bestId)