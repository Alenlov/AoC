input = '158937462'
sample = '389125467'
# Ha en lista. Där index = siffran på koppen, värdet i listan är vilken siffra som kommer efter.
# Vilka index behöver jag ändra:
#   CurrentIndex
#   CurrentIndex + 3
#   Där jag ska lägga in den.

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
cupOrder = [0]*(len(startingorder)+1)
prevCup = None
for cup in startingorder:
    curCup = cup
    if prevCup:
        cupOrder[prevCup] = curCup
    prevCup = curCup
cupOrder[prevCup] = startingorder[0]
#print(cupOrder)
#print(startingorder)
MIN_VAL = min(startingorder)
MAX_VAL = max(startingorder)
num_turns = 100
startCup = startingorder[0]
for i in range(num_turns):
    #print('Turn {}'.format(i+1))
    cupOrder, startCup = oneMove(cupOrder, startCup)
    #print(cupOrder)
    #print(startCup)

atCup = cupOrder[1]
for i in range(len(startingorder)-1):
    print('{}'.format(atCup),end='')
    atCup = cupOrder[atCup]
print()