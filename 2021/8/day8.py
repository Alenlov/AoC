display = open('2021/8/input').read().splitlines()

all = set('abcdefg')
allS = set('ABCDEFG')
numLines = {0:set('ABCEFG'),1:set('CF'), 2:set('ACDEG'),3:set('ACDFG'),4:set('BCDF'),5:set('ABDFG'),6:set('ABDEFG'),7:set('ACF'),8:set('ABCDEFG'),9:set('ABCDFG')}
def startingSets():
    mapOfSets = {}
    for v in 'ABCDEFG':
        mapOfSets[v] = set('abcdefg')
    return mapOfSets

complexNum = {5:[2,3,5], 6:[0,6,9]}
simpleNum = {2:1,3:7,4:4,7:8}
numNumbersA = 0
totalSum = 0
for line in display:
    setOfNum = {}
    lhs, rhs = line.split(' | ')
    for l in lhs.split():
        setOfSegs = set(l)
        n = len(l)
        if n in simpleNum:
            v = simpleNum[n]
            setOfNum[v] = setOfSegs
            



    for l in lhs.split():
        setOfSegs = set(l)
        n = len(l)
        if n in complexNum:
            v = complexNum[n]
            if setOfNum[4].issubset(setOfSegs) and n == 6:
                setOfNum[9] = setOfSegs
            elif setOfNum[1].issubset(setOfSegs):
                if n == 6:
                    setOfNum[0] = setOfSegs
                elif n == 5:
                    setOfNum[3] = setOfSegs
            elif n == 6:
                setOfNum[6] = setOfSegs
            elif (setOfSegs | setOfNum[4]) == setOfNum[8]:
                setOfNum[2] = setOfSegs
            else:
                setOfNum[5] = setOfSegs

    value = ''
    for d in rhs.split():
        n = len(d)
        
        if n in simpleNum:
            numNumbersA += 1
            value += str(simpleNum[n])
        else:
            for v in complexNum[n]:
                if setOfNum[v] == set(d):
                    value += str(v)
    totalSum += int(value)


print("Answer part A: the number of 1,4,7,8 is {}".format(numNumbersA))
print("Answer part B: the sum of outputs is {}".format(totalSum))