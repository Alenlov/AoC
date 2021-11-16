valid = 0
lines = 0
passwords = open('input.txt', 'r')
password = passwords.readline()
while password:
	password = password.split(' ')
	lines += 1
	rule = password[0].split('-')
	char = password[1][0]
	pwd = password[2]
	count = 0
	for c in pwd:
		if c == char:
			count += 1
	if count >= int(rule[0]) and count <= int(rule[1]):
		valid += 1
	password = passwords.readline()


	

print(valid)
passwords.close()
