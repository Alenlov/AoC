infile = open('2021/14/input')

start = infile.readline().strip()

infile.readline().strip()
reaction = infile.readline().strip()

reactions = {}

while reaction:
    lhs,rhs = reaction.split(' -> ')
    reactions[lhs] = rhs
    reaction = infile.readline().strip()

print(start)
print(len(reactions))
polymer = start
for loop in range(10):
    newPolymer = polymer[0]
    for i in range(len(polymer)-1):
        pair = polymer[i:i+2]
        if pair in reactions:
            newPolymer += reactions[pair]
        else:
            print('No match {}'.format(pair))
        newPolymer += pair[1]
    polymer = newPolymer

countDict = {}
for c in polymer:
    if c not in countDict:
        countDict[c] = 0
    countDict[c] += 1

max = 0
min = len(polymer)
for c in countDict:
    if countDict[c] > max:
        max = countDict[c]
    if countDict[c] < min:
        min = countDict[c]

print("Answer part A: the quantity of most common {} minus least common {} is {}".format(max,min,max-min))

startPolyDict = {}
for react in reactions:
    startPolyDict[react] = 0
polyDict = startPolyDict.copy()
for i in range(len(start)-1):
    pair = start[i:i+2]
    polyDict[pair] += 1

for loop in range(40):
    newPolyDict = startPolyDict.copy()
    for pair in polyDict:
        front = pair[0] + reactions[pair]
        back = reactions[pair] + pair[1]
        newPolyDict[front] += polyDict[pair]
        newPolyDict[back] += polyDict[pair]
    polyDict = newPolyDict

countDict = {}
for pair in polyDict:
    for c in pair:
        if c not in countDict:
            countDict[c] = 0
        countDict[c] += polyDict[pair]
        min = countDict[c]
countDict[start[0]] += 1
countDict[start[-1]] += 1
max = 0
for c in countDict:
    if countDict[c] < min:
        min = countDict[c]
    if countDict[c] > max:
        max = countDict[c]

print("Answer part B: the diff is {}".format(max//2-min//2))