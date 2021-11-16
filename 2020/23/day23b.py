input = '158937462'
sample = '389125467'
# Ha en lista. Där index = siffran på koppen, värdet i listan är vilken siffra som kommer efter.
# Vilka index behöver jag ändra:
#   CurrentIndex
#   CurrentIndex + 3
#   Där jag ska lägga in den.

MIN_VAL = 1
MAX_VAL = 1000000

def oneMove(currentList, currentCup):
    #print('We have list {} starting with {}'.format(currentList[1:], currentCup))
    cupsToMove = [currentList[currentCup]]
    for i in range(2):
        cupsToMove.append(currentList[cupsToMove[i]])
    #print(cupsToMove)
    # Find index to move to. First index less than currentCup that is not in cupsToMove
    nextCup = currentCup - 1
    if nextCup < MIN_VAL:
        nextCup = MAX_VAL
    while nextCup in cupsToMove:
        nextCup -= 1
        if nextCup < MIN_VAL:
            nextCup = MAX_VAL
    currentList[currentCup] = currentList[cupsToMove[-1]]
    currentList[cupsToMove[-1]] = currentList[nextCup]
    currentList[nextCup] = cupsToMove[0]
    return currentList, currentList[currentCup]

    




startingorder = [int(a) for a in input]
cupOrder = list(range(1,MAX_VAL + 2))
prevCup = None
for cup in startingorder:
    curCup = cup
    if prevCup:
        cupOrder[prevCup] = curCup
    prevCup = curCup
cupOrder[prevCup] = len(startingorder) + 1
cupOrder[-1] = startingorder[0]
print(cupOrder[:15])
print(cupOrder[-10:])
print(startingorder)
num_turns = 10000000
startCup = startingorder[0]
for i in range(num_turns):
    #print('Turn {}'.format(i+1))
    cupOrder, startCup = oneMove(cupOrder, startCup)
    #print(cupOrder)
    #print(startCup)
cupA = cupOrder[1]
cupB = cupOrder[cupA]
print('The stars are in {} and {} their product is {}'.format(cupA, cupB, cupA*cupB))
