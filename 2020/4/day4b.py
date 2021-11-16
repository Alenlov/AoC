import re

with open("input.txt") as f:
	passports = f.read().split('\n\n')



valid = 0
for passport in passports:
	passport = passport.replace('\n', ' ').split(' ')
	numFields = 0

	for field in passport:
		
		[key, val] = field.split(':')
		if key == 'byr':
			if re.match(r"^[0-9]{4}$", val):
				if 1920 <= int(val) <= 2002:
					numFields += 1
				
				else:
					break
		elif key == 'iyr':
			if re.match(r"^[0-9]{4}$", val):
				if 2010 <= int(val) <= 2020:
					numFields += 1
				
				else:
					break
		elif key == 'eyr':
			if re.match(r"^[0-9]{4}$", val):
				if 2020 <= int(val) <= 2030:
					numFields += 1
				
				else:
					break
		elif key == 'hgt':
			if val[-2:] == 'cm':
				if re.match(r"^[0-9]{3}$", val[:3]):
					if 150 <= int(val[:3]) <= 193:
						numFields += 1
					
					else:
						break
			elif val[-2:] == 'in':
				if re.match(r"^[0-9]{2}$", val[:2]):
					if 59 <= int(val[:2]) <= 76:
						numFields += 1
					
					else:
						break
			else:
				break
		elif key == 'hcl':
			if re.match(r"^#[a-f,0-9]{6}$", val):
				numFields += 1
			
			else:
				break
		elif key == 'ecl':
			if re.match(r"^(amb|blu|brn|gry|grn|hzl|oth)$", val):
				numFields += 1
			
			else:
				break
		elif key == 'pid':
			if re.match(r"^[0-9]{9}$", val):
				numFields += 1
			
			else:
				break

	if numFields == 7:
		valid += 1

print(valid)


