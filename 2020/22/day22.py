from collections import deque

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

print(player1)
print(player2)
playing = True
while playing:
    card1 = player1.popleft()
    card2 = player2.popleft()
    if card1 > card2:
        player1.append(card1)
        player1.append(card2)
    else:
        player2.append(card2)
        player2.append(card1)
    if len(player1) == 0 or len(player2) == 0:
        playing = False

numPlayer1 = len(player1)
numPlayer2 = len(player2)
player1Score = 0
for card1 in player1:
    player1Score += card1 * numPlayer1
    numPlayer1 -= 1
player2Score = 0
for card2 in player2:
    player2Score += card2 * numPlayer2
    numPlayer2 -= 1
print('Player 1 got {}'.format(player1Score))
print('Player 2 got {}'.format(player2Score))
