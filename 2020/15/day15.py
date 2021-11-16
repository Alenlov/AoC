import time
with open("15/input.txt") as f:
	startNumbers = f.read().split(',')

turn = 0
numberDict = {}
lastNumber = 1
st = time.time()
while turn < 30000000:
    if turn < len(startNumbers):
        lastNumber = int(startNumbers[turn])
        numberDict[lastNumber] = turn
        newNumber = 0
    else:
        lastNumber = newNumber
        if newNumber in numberDict:
            lastTurn = numberDict[newNumber]
            newNumber = turn - lastTurn
        else:
            newNumber = 0
        numberDict[lastNumber] = turn
    if turn == 2019:
        print(lastNumber)
    turn += 1

print(lastNumber)
print(time.time() - st)
