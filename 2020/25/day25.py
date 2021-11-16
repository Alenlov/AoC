cardPublicKey = 11562782
doorPublicKey = 18108497

subjectNumber = 7
modulus = 20201227

foundBoth = False
cardLoopSize = None
doorLoopSize = None
loop = 0
value = 1
while not foundBoth:
    if loop % 1000 == 0:
        print(loop)
    loop += 1
    value = (value * subjectNumber) % modulus
    if value == cardPublicKey:
        cardLoopSize = loop
    if value == doorPublicKey:
        doorPublicKey = loop
    if cardLoopSize or doorLoopSize:
        foundBoth = True
print(cardLoopSize, doorLoopSize)

subjectNumber = doorPublicKey
value = 1
for i in range(cardLoopSize):
    value = (value * subjectNumber) % modulus
print(value)