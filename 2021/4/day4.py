class Bingo:

    def __init__(self):
        self.found = []
        self.numbDict = {}

    def wonBrick(self):
        won = False
        cols = [0]*5
        for row in self.found:
            if sum(row) == 5:
                won = True
            for i,r in enumerate(row):
                if r == 1:
                    cols[i] += 1
                    if cols[i] == 5:
                        won = True
        print(won)
        if not won:
            return 0
        elif won:
            sumOfUnmarked = 0
            for val in self.numbDict:
                row, col = self.numbDict[val]
                if not self.found[row][col]:
                    sumOfUnmarked += val
            return sumOfUnmarked

        
            

inFile = open('2021/4/input')


line = inFile.readline().strip()

calledNumbers = [int(x) for x in line.split(',')]
id = 0
brickDict = {}
numberDict = {}
print(calledNumbers)
line = inFile.readline().strip()
line = inFile.readline().strip()
while line:
    print(line)
    if(len(line)>0):
        print('Hej hej')
        b = Bingo()
        for row in range(5):
            b.found.append([0]*5)
            numbers = [int(n) for n in line.split()]
            for col, num in enumerate(numbers):
                # print(row,col,num)
                b.numbDict[num] = (row, col)
                
                # print(b.numbDict)
                if num in numberDict:
                    numberDict[num].append(id)
                else:
                    numberDict[num] = [id]
            line = inFile.readline().strip()
        print(len(b.numbDict.keys()))
        brickDict[id] = b
        id += 1
        line = inFile.readline().strip()
    else:
        line = inFile.readline().strip()
doneA = False
doneB = False
answerA = 0
answerB = 0
doneBoards = set()
for number in calledNumbers:
    print(number)
    for brickId in numberDict[number]:
        print(brickId)
        row,col = brickDict[brickId].numbDict[number]
        print(row,col)
        brickDict[brickId].found[row][col] = 1
        sumOfUnmarked = brickDict[brickId].wonBrick()
        print(sumOfUnmarked)
        if sumOfUnmarked > 0:
            if not doneA:
                doneA = True
                answerA = sumOfUnmarked * number
            doneBoards.add(brickId)
            if len(doneBoards) == len(brickDict.keys()):
                if not doneB:
                    doneB = True
                    answerB = sumOfUnmarked * number

print("Answer part A: The value is {}".format(answerA))
print("Answer part B: The value is {}".format(answerB))