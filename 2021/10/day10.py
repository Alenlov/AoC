lines = open('2021/10/input').read().splitlines()

pairs = { '()', '[]', '<>', '{}'}
totScoreA = 0
scoreVec = []
leftBrackets = {'(':')', '[':']', '<':'>', '{':'}'}
rightBrackets = {')', ']', '>', '}'}
scores = {')':3, ']':57, '}':1197, '>':25137}
scoresB = {')':1, ']':2, '}':3, '>':4}
for line in lines:
    pairsToFind = True
    while pairsToFind:
        pairsToFind = False
        for pair in pairs:
            newLine = line.replace(pair,'')
            if len(newLine) < len(line):
                pairsToFind = True
                line = newLine
    found = {}
    for rhs in rightBrackets:
        if line.find(rhs) != -1:
            found[rhs] =line.find(rhs)
    if found:
        minIndx = len(line)
        score = 0
        for f in found:
            if found[f] < minIndx:
                score = scores[f]
                minIndx = found[f]
        totScoreA += score
    else:
        score = 0
        for i in range(len(line)):
            indx = len(line) - i - 1
            score = score*5 + scoresB[leftBrackets[line[indx]]]
        scoreVec.append(score)
            

scoreVec.sort()
print("Answer part A: the total score is {}".format(totScoreA))
print("Answer part B: the middle score is {}".format(scoreVec[len(scoreVec)//2]))

