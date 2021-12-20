maxX = 0
maxY = 0
manualPage = open('2021/13/input')
points = set()
line = manualPage.readline().strip()
while line:
    x,y = line.split(',')
    x = int(x)
    y = int(y)
    if x > maxX:
        maxX = x
    if y > maxY:
        maxY = y
    points.add((x,y))
    line = manualPage.readline().strip()
folds = []
line = manualPage.readline().strip()
while line:
    lhs, rhs = line.split('=')

    folds.append((lhs[-1],rhs))
    line = manualPage.readline().strip()
first = False
for fold in folds:
    coord = fold[0]
    val = int(fold[1])
    newPoints = set()
    for point in points:
        px = point[0]
        py = point[1]
        if coord == 'x':
            if px > val:
                px = val - abs(px - val)
            newPoints.add((px,py))
        else:
            if py > val:
                py = val - abs(py - val)
            newPoints.add((px,py))
    points = newPoints
    if not first:
        print("Answer part A: The number of dots is {}".format(len(points)))
        first = True
minX = 0
minY = 0
maxY = 0
maxX = 0
for point in points:
    if point[0] > maxX:
        maxX = point[0]
    elif point[0] < minX:
        minX = point[0]
    if point[1] > maxY:
        maxY = point[1]
    elif point[1] < minY:
        minY = point[1]
for y in range(maxY+1):
    for x in range(maxX+1):
        if (x,y) in points:
            print('#',end='')
        else:
            print(' ',end='')
    print('')