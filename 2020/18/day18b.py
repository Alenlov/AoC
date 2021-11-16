isInt = '0123456789'
isOp = '+*'
isPar = '()'

def calculate(exprList):
    value = None
    index = 0
    lastOperation = None
    while index < len(exprList):
        if exprList[index] == ' ':
            index += 1
            continue
        elif isinstance(exprList[index], int):
            value = useOp(value, int(exprList[index]), lastOperation)
        elif exprList[index] in isOp:
            lastOperation = exprList[index]
        elif exprList[index] == '(':
            newValue, newindex = calculate(exprList[index+1:])
            value = useOp(value, newValue, lastOperation)
            index = index + newindex + 2
            continue        
        elif exprList[index] == ')':
            return value, index
        index += 1

    return value

def newCalc(exprList):
    #print(exprList)
    endIndex = 0
    newIndex = 0
    # Parenthesis:
    indx = 0
    while indx < len(exprList):
        expr = exprList[indx]
        if expr == '(':
            value, newIndex2 = newCalc(exprList[indx+1:])
            newIndex += newIndex2 + 1
            newExprList = exprList[:indx].copy()
            newExprList.extend(value)
            newExprList.extend(exprList[indx+newIndex2+2:])
            exprList = newExprList
            #print(newExprList)
        elif expr == ')':
            #print(exprList)
            exprList = exprList[:indx]
            endIndex = len(exprList) + newIndex
        indx += 1
    
    indx = 0
    while indx < len(exprList):
        if exprList[indx] == '+':
            #print(exprList)
            leftVal = exprList[indx-1]
            rightVal = exprList[indx+1]
            newVal = leftVal + rightVal
            newExprList = exprList[:indx-1].copy()
            newExprList.append(newVal)
            newExprList.extend(exprList[indx+2:])
            exprList = newExprList
            #print(exprList)
        else:
            indx += 1

    indx = 0
    while indx < len(exprList):
        if exprList[indx] == '*':
            #print(exprList)
            leftVal = exprList[indx-1]
            rightVal = exprList[indx+1]
            newVal = leftVal * rightVal
            newExprList = exprList[:indx-1].copy()
            newExprList.append(newVal)
            newExprList.extend(exprList[indx+2:])
            exprList = newExprList
            #print(exprList)
        else:
            indx += 1
    #print(indx)
    #print(endIndex)
    return exprList, endIndex

def useOp(preVal, nexVal, op):
    if op == '+':
        return preVal + nexVal
    elif op == '*':
        return preVal * nexVal
    elif not preVal:
        return nexVal

with open("18/input.txt") as f:
	equations = f.read().splitlines()
sumVals = 0
for equation in equations:
    eqList = list(equation.replace(' ',''))
    for i,val in enumerate(eqList):
        if val in isInt:
            eqList[i] = int(val)
    newVal, _ = newCalc(eqList)
    sumVals += newVal[0]
print(sumVals)
    