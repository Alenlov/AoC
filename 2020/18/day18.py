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
        elif exprList[index] in isInt:
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
    #eqList = equation.split(' ')
    value = calculate(equation)
    sumVals += value
print(sumVals)
    