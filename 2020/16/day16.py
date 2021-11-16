with open("16/input.txt") as f:
	tickets = f.read().splitlines()

i = 0
scanningRules = True
ranges = set()
rangesDict = {}
uniqueDict = {}
while scanningRules:

    if tickets[i] == '':
        scanningRules = False

    else:

        name, vals = tickets[i].split(': ')
        val1, val2 = vals.split(' or ')
        start, end = val1.split('-')
        fieldRange = set(range(int(start), int(end)+1))
        start, end = val2.split('-')
        fieldRange = fieldRange.union(set(range(int(start), int(end)+1)))
        ranges = ranges.union(fieldRange)
        rangesDict[name] = fieldRange
        uniqueDict[name] = set(range(20))
    i = i+1

assert tickets[i] == 'your ticket:'
i += 1
yourTicket = tickets[i].split(',')

i += 2
assert tickets[i] == 'nearby tickets:'
i += 1

invalid = 0
while i < len(tickets):
    validTicket = True
    ticketFields = {}
    values = tickets[i].split(',')
    for j in range(len(values)):
        val = int(values[j])
        if val not in ranges:
            invalid += int(val)
            validTicket = False
        for field, validNum  in rangesDict.items():
            if val in validNum:
                if not field in ticketFields:
                    ticketFields[field] = set([j])
                else:
                    ticketFields[field] = ticketFields[field].union(set([j]))
    if validTicket:
        for field, values in uniqueDict.items():
            uniqueDict[field] = uniqueDict[field].intersection(ticketFields[field])

    i = i+1

foundNotAll = True
while foundNotAll:
    foundNotAll = False
    for field, posCol in uniqueDict.items():
        if len(posCol) == 1:
            for otherField, otherPosCol in uniqueDict.items():
                if field != otherField:
                    uniqueDict[otherField] = uniqueDict[otherField] - posCol
        else:
            foundNotAll = True

totalValue = 1

for field, col in uniqueDict.items():
    if 'departure ' in field:
        totalValue *= int(yourTicket[list(col)[0]])

print(totalValue)
print(invalid)