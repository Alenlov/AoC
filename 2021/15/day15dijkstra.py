from queue import PriorityQueue
import time
start = time.time()
file = open('2021/15/input').read().splitlines()

chitons = []

for line in file:
    chitons.append([int(x) for x in line])

def chitonsVal(x,y):
    N = len(chitons)
    inc = x//N + y//N
    x,y = (x%N, y%N)
    val = ((chitons[y][x] + inc - 1) % 9) + 1
    return val

initial = (0,0)
endA = (99,99)
endB = (499,499)

diff = {(-1,0),(1,0),(0,-1),(0,1)}

unvisited = PriorityQueue()

unvisited.put((0,initial))
visited = {}
nodes = {}
itr = 0
while unvisited:
    itr += 1
    (dist, head) = unvisited.get()
    if head in visited:
        continue
    visited[head] = dist
    if head == endA:
        print("Answer part A: the minimum risk is {} after {} iterations".format(dist,itr))
    elif head == endB:
        print("Answer part B: the minimum risk is {} after {} iterations".format(dist,itr))
        break
    x,y = head
    for (dx,dy) in diff:
        newX = x+dx
        newY = y+dy
        if -1<newX<5*len(chitons) and -1 < newY < 5*len(chitons):
            newVal =  dist + chitonsVal(newX,newY)
            if (newX,newY) not in visited:
                if (newX,newY) not in nodes:
                    nodes[(newX,newY)] = newVal
                    unvisited.put( (newVal, (newX,newY)) )
                elif nodes[(newX,newY)] > newVal:
                    nodes[(newX,newY)] = newVal
                    unvisited.put( (newVal, (newX,newY)) )
print("Completed in {} seconds".format(time.time() - start))

