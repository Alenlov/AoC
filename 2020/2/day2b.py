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
	if (pwd[int(rule[0])-1] == char) ^ (pwd[int(rule[1])-1] == char):
		valid += 1
	password = passwords.readline()


	

print(valid)
passwords.close()
