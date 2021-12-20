import re
snailNumbers = open('2021/18/input').read().splitlines()

startNum = '['
endNum = ']'
delim = ','
nums = '0123456789'
numRegex = re.compile("[0-9]")
def parseNum(snailNum):
    order = 0
    head = 0
    lastNumHead = None
    lastNumOrder = None
    firstSplitHead = None
    running = True
    while running:
        if snailNum[head] == startNum:
            order += 1
            head += 1
        elif snailNum[head] == endNum:
            order -= 1
            head += 1
        elif snailNum[head] in nums:
            lastNumHead = head
            lastNumOrder = order
            if snailNum[head+1] in nums:
                if not firstSplitHead:
                    firstSplitHead = head
            head += 1
        else:
            head += 1
        
        if order == 5:
            # Explode            
            if snailNum[head+1] in nums and snailNum[head+4] not in nums:
                lhs = int(snailNum[head:head+2])
                rhs = int(snailNum[head+3])
                numLen = 5
            elif snailNum[head+1] in nums and snailNum[head+4] in nums:
                lhs = int(snailNum[head:head+2])
                rhs = int(snailNum[head+3:head+5])
                numLen = 6
            elif snailNum[head+1] not in nums and snailNum[head+3] in nums:
                lhs = int(snailNum[head])
                rhs = int(snailNum[head+2:head+4])
                numLen = 5
            else:
                lhs = int(snailNum[head])
                rhs = int(snailNum[head+2])
                numLen = 4
            snailNum = snailNum[:head-1] + '0' + snailNum[head+numLen:]
            m = numRegex.search(snailNum, pos=head)
            if m:
                nextNumHead = m.start()
                if snailNum[nextNumHead+1] in nums:
                    val = int(snailNum[nextNumHead:nextNumHead+2])
                    numLen = 2
                else:
                    val = int(snailNum[nextNumHead])
                    numLen = 1
                val += rhs
                snailNum = snailNum[:nextNumHead] + str(val) + snailNum[nextNumHead+numLen:]
            
            if lastNumHead:
                if snailNum[lastNumHead-1] in nums:
                    val = int(snailNum[lastNumHead-1:lastNumHead+1])
                    lastNumHead -= 1
                    numLen = 2
                else:
                    val = int(snailNum[lastNumHead])
                    numLen = 1
                val += lhs
                snailNum = snailNum[:lastNumHead] + str(val) + snailNum[lastNumHead+numLen:]
            return snailNum, False
        
        if order == 0:
            running = False
    if firstSplitHead:
        head = firstSplitHead
        num = int(snailNum[head:head+2])
        lhs = num//2
        rhs = num//2 + (num%2)
        snailNum = snailNum[:head] + startNum + str(lhs) + delim + str(rhs) + endNum + snailNum[head+2:]
        return snailNum, False
    return snailNum, True

def magnitude(snailNum):
    totMag = 0

    if snailNum[0] in nums:
        return int(snailNum[0]), snailNum[1:]
    if snailNum[0] == startNum:
        mag, snailNum = magnitude(snailNum[1:])

        totMag += 3*mag
    if snailNum[0] == delim:
        mag, snailNum = magnitude(snailNum[1:])

        totMag += 2*mag
    if snailNum[0] == endNum:
        return totMag, snailNum[1:]
        

snailNum = None
for line in snailNumbers:
    if snailNum:
        snailNum = startNum + snailNum + delim + line + endNum
    else:
        snailNum = line
    snailNum, done = parseNum(snailNum)
    while not done:
        snailNum, done = parseNum(snailNum)
print(magnitude(snailNum))
maxMag = 0
for line1 in snailNumbers:
    for line2 in snailNumbers:
        if line1 != line2:
            snailNum = startNum + line1 + delim + line2 + endNum
            snailNum, done = parseNum(snailNum)
            while not done:
                snailNum, done = parseNum(snailNum)
            mag, _ = magnitude(snailNum)
            if mag > maxMag:
                maxMag = mag

print(maxMag)

