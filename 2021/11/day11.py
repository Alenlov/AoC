from typing import Deque


octopuses = open('2021/11/input').read().splitlines()

for i in range(len(octopuses)):
    octopuses[i] = [int(x) for x in octopuses[i]]

def oneStep(octopuses):
    flashedSet = set()
    flashed = Deque()
    for i in range(len(octopuses)):
        for j in range(len(octopuses[i])):
            octopuses[i][j] += 1
            if octopuses[i][j] > 9:
                flashed.append((i,j))
                flashedSet.add((i,j))
    delta = {-1,0,1}

    while flashed:
        i,j = flashed.pop()
        for di in delta:
            for dj in delta:
                if 0<= (i+di) and (i+di) < len(octopuses) and 0<= (j+dj) and (j+dj) < len(octopuses[i]):
                    octopuses[i+di][j+dj] += 1
                    if octopuses[i+di][j+dj] == 10:
                        flashed.append((i+di,j+dj))
                        flashedSet.add((i+di,j+dj))

    for (i,j) in flashedSet:
        octopuses[i][j] = 0

    return octopuses, len(flashedSet)
totFlashed = 0
runing = True
iterations = 0
while runing:
    octopuses, numFlashed = oneStep(octopuses)
    iterations += 1
    totFlashed += numFlashed
    if iterations == 100:
        ansA = totFlashed
    if numFlashed == 100:
        ansB = iterations
        runing = False

print("Answer part A: total number of flashes is {}".format(ansA))
print("Answer part B: the first iteration where all flashes is {}".format(ansB))