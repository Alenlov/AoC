import re

with open("19/input.txt") as f:
	rules = f.read().splitlines()

def makeRule(index):
    expr = ruleDict[index]
    exprList = expr.split(' ')
    ruleString = '('
    for val in exprList:
        if val in ['"a"', '"b"', '|']:
            ruleString = ruleString + val.strip('"')
        else:
            ruleString = ruleString + makeRule(int(val))
    ruleString = ruleString + ')'
    return ruleString
ruleDict = {}
line = 0
for rule in rules:
    if rule == '':
        break
    ruleNum, expr = rule.split(': ')
    ruleDict[int(ruleNum)] = expr
    line += 1
line += 1
numMatch = 0
numA = 0
pattern42 = makeRule(42)
pattern31 = makeRule(31) 
while line < len(rules):
    msg = rules[line]
    m = re.match(pattern42, msg)
    num42matches = 0
    while m:
        end = m.span()[1]
        msg = msg[end:]
        num42matches += 1
        m = re.match(pattern42, msg)
    num31matches = 0
    m = re.match(pattern31, msg)
    while m:
        end = m.span()[1]
        msg = msg[end:]
        num31matches += 1
        m = re.match(pattern31, msg)
    if num42matches == 2 and num31matches == 1 and len(msg) == 0:
        numA += 1
    if num42matches > num31matches and len(msg) == 0 and num31matches > 0:
        numMatch += 1
    line += 1
print(numMatch)
print(numA)
