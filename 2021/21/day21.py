import time
pos = [6,2]
score = [0,0]

running = True
nextDie = 1
diceThrown = 0
while running:
    for player in range(len(pos)):
        dieSum = 3*(nextDie + nextDie+2)//2 % 10
        diceThrown += 3
        pos[player] = ((pos[player] - 1 + dieSum) % 10) + 1
        score[player] += pos[player]
        nextDie = (nextDie + 3) % 10
        if score[player] >= 1000:
            running = False
            ansA = score[1-player] * diceThrown
            break
print("Answer part A: the score of losing player multiplied with number of thrown dice is {}".format(ansA))
start = time.time()
threeThrows = {3:1,4:3,5:6,6:7,7:6,8:3,9:1}
gameStates = {(6,2,0,0):1}
wins = [0,0]
player = 0
while gameStates:
    newGameStates = {}
    for state in gameStates:
        for throw in threeThrows:
            newPos = ((state[player] - 1 + throw) % 10) + 1
            newScore = state[2+player] + newPos
            if newScore >= 21:
                wins[player] += gameStates[state] * threeThrows[throw]
            else:
                newState = list(state)
                newState[player] = newPos
                newState[2+player] = newScore
                newState = tuple(newState)
                if newState not in newGameStates:
                    newGameStates[newState] = 0
                newGameStates[newState] += gameStates[state] * threeThrows[throw]
                
    player = 1 - player
    gameStates = newGameStates
totTime = time.time() - start
print("Answer part B: the most wins is {} took {:.2f} s".format(max(wins),totTime))
