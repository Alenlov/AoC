from collections import deque
import itertools

def score(player):
    numPlayer = len(player)
    playerScore = 0
    for card in player:
        playerScore += card * numPlayer
        numPlayer -= 1
    return playerScore

def playGame(player1, player2):
    configurations = set()
    playing = True
    while playing:
        currentConfig = str(player1) + str(player2)
        if currentConfig in configurations:
            return 1, 0
        else:
            configurations.add(currentConfig)
        card1 = player1.popleft()
        card2 = player2.popleft()
        if card1 <= len(player1) and card2 <= len(player2):
            newPlayer1 = deque()
            for i in range(card1):
                newPlayer1.append(player1[i])
            newPlayer2 = deque()
            for i in range(card2):
                newPlayer2.append(player2[i])
            score1, score2 = playGame(newPlayer1, newPlayer2)
            if score1 > score2:
                player1.append(card1)
                player1.append(card2)
            else:
                player2.append(card2)
                player2.append(card1)
        elif card1 > card2:
            player1.append(card1)
            player1.append(card2)
        else:
            player2.append(card2)
            player2.append(card1)
        if len(player1) == 0 or len(player2) == 0:
            playing = False
    return score(player1), score(player2)
with open("22/input.txt") as f:
	startingOrder = f.read().splitlines()

player1 = deque()
player2 = deque()
currPlayer = 0
for line in startingOrder:
    
    if line.startswith('Player'):
        currPlayer += 1
        continue
    elif line == '':
        currPlayer = 2
        continue
    if currPlayer == 1:
        player1.append(int(line))
    else:
        player2.append(int(line))

player1Score, player2Score = playGame(player1, player2)

print('Player 1 got {}'.format(player1Score))
print('Player 2 got {}'.format(player2Score))
