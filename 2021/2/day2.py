depth = 0
horiz = 0

commands = open('2021/2/input').read().splitlines()

for cmd in commands:
    (move, value) = cmd.split(' ')
    if move == "forward":
        horiz += int(value)
    elif move == "down":
        depth += int(value)
    elif move == "up":
        depth -= int(value)

print("Answer part A: We are at {}".format(depth*horiz))


depth = 0
horiz = 0
aim = 0

for cmd in commands:
    (move, value) = cmd.split(' ')
    if move == "forward":
        horiz += int(value)
        depth += aim*int(value)
    elif move == "down":
        aim += int(value)
    elif move == "up":
        aim -= int(value)

print("Answer part B: We are at {}".format(depth*horiz))