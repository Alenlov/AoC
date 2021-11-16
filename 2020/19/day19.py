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
pattern =  makeRule(0) + '$'
while line < len(rules):
    m = re.match(pattern, rules[line])
    if m:
        numMatch += 1
    line += 1
print(numMatch)
