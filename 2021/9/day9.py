from typing import Deque


heatMap = open('2021/9/input').read().splitlines()

diffs = {(-1,0),(1,0),(0,-1),(0,1)}

def sizeOfBasin(x,y):
    basin = set()
    head = Deque()
    
    head.append((x,y))
    while head:
        curr = head.pop()
        basin.add(curr)
        for d in diffs:
            newHead = (curr[0] + d[0], curr[1] + d[1])
            if not ((newHead[0] < 0) or (newHead[0] >= len(heatMap[0])) or (newHead[1] < 0) or (newHead[1] >= len(heatMap))):
                if heatMap[newHead[1]][newHead[0]] != str(9) and newHead not in basin and newHead not in head:
                    head.append(newHead)
    return len(basin)


sumOfRisk = 0
basins = []
for y in range(len(heatMap)):
    for x in range(len(heatMap[y])):
        currVal = heatMap[y][x]
        smallest = True
        if (x-1) >= 0:
            if heatMap[y][x-1] <= currVal:
                smallest = False
        if (x+1) < len(heatMap[y]):
            if heatMap[y][x+1] <= currVal:
                smallest = False
        if (y-1) >= 0:
            if heatMap[y-1][x] <= currVal:
                smallest = False
        if (y+1) < len(heatMap):
            if heatMap[y+1][x] <= currVal:
                smallest = False
        if smallest:
            sumOfRisk += int(currVal) + 1
            basins.append(sizeOfBasin(x,y))
            print("out")

basins.sort(reverse=True)

prodOfLargest = basins[0] * basins[1] * basins[2]

print("Answer part A: The sum of risk levels is {}".format(sumOfRisk))
print("Answer part B: the product of three largest basins is {}".format(prodOfLargest))
