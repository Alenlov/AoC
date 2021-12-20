

numbers = open('2021/3/input').read().splitlines()

totNmbr = [0]*len(numbers[0])

for nbr in numbers:
    for i in range(len(nbr)):
        # print(nbr[i])
        if int(nbr[i]) == 1:
            totNmbr[i] += 1

gammaRate = ['0']*len(totNmbr)
epsilonRate = ['0']*len(totNmbr)

for i in range(len(totNmbr)):
    if totNmbr[i] > (len(numbers)/2):
        gammaRate[i] = '1'
    else:
        epsilonRate[i] = '1'

print(len(numbers))
print(totNmbr)
print(gammaRate)
print(epsilonRate)

powerConsumption = int(''.join(gammaRate),2)*int(''.join(epsilonRate),2)
print("Answer part A: The power consumption is {}.".format(powerConsumption))

oxygenList = numbers.copy()
carbonList = numbers.copy()
for bit in range(len(numbers[0])):
    oxygenCount = 0
    oxygenOne = []
    oxygenZero = []
    if (len(oxygenList) > 1):

        for nbr in oxygenList:
            if int(nbr[bit]) == 1:
                oxygenCount += 1
                oxygenOne.append(nbr)
            else:
                oxygenZero.append(nbr)
        
        if oxygenCount >= (len(oxygenList)/2):
            oxygenList = oxygenOne
        else:
            oxygenList = oxygenZero

    carbonCount = 0
    carbonOne = []
    carbonZero = []
    if (len(carbonList) > 1):
        for nbr in carbonList:
            if int(nbr[bit]) == 1:
                carbonCount += 1
                carbonOne.append(nbr)
            else:
                carbonZero.append(nbr)
        
        if carbonCount >= (len(carbonList)/2):
            carbonList = carbonZero
        else:
            carbonList = carbonOne

print("Answer part B: the life supper rating is {}".format(int(oxygenList[0],2)*int(carbonList[0],2)))