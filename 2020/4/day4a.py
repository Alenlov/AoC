with open("input.txt") as f:
	passports = f.read().split('\n\n')

valid = 0
for passport in passports:
	passport = passport.replace('\n', ' ').split(' ')
	numFields = 0
	for field in passport:
		
		[key, val] = field.split(':')
		if key != 'cid':
			numFields += 1
	if numFields == 7:
		valid += 1

print(valid)