
def oneDay(fishDict):
    newFishDict = {}
    for f in fishDict:
        # print("we have {} fishes at clock {}".format(fishDict[f], f))
        if f > 0:
            if f-1 not in newFishDict:
                newFishDict[f-1] = 0
            newFishDict[f-1] += fishDict[f]
        elif f == 0:
            newFishDict[8] = fishDict[f]
            if 6 not in newFishDict:
                newFishDict[6] = 0
            newFishDict[6] += fishDict[f]
    # print(newFishDict)
    return newFishDict


startingString = open('2021/6/input').read().strip()

startingFish = [int(x) for x in startingString.split(',')]

fishDict = {}
for f in startingFish:
    if f not in fishDict:
        fishDict[f] = 0
    fishDict[f] += 1

# print(fishDict)

for d in range(256):
    if d == 80:
        totFishA = 0
        for f in fishDict:
            totFishA += fishDict[f]
    newFishDict = oneDay(fishDict)
    fishDict = newFishDict
    

totFishB = 0
for f in fishDict:
    totFishB += fishDict[f]

print("Answer part A: the total number of fishes is {}".format(totFishA))
print("Answer part B: the total number of fishes is {}".format(totFishB))