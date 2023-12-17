groups = [
    g.split("\n")
    for g in open("input", "r", encoding="utf-8").read().strip().split("\n\n")
]

transpose = lambda lines: ["".join([l[i] for l in lines]) for i in range(len(lines[0]))]
string_diff = lambda a, b: sum(i != j for (i, j) in zip(a, b))
score = lambda g, diff: 100 * get_refl(g, diff) + get_refl(transpose(g), diff)


def get_refl(group, allowed_diff):
    for line in range(1, len(group)):
        lines_to_check = min(line, len(group) - line)
        a = "".join(group[:line][::-1][:lines_to_check])
        b = "".join(group[line:][:lines_to_check])
        if string_diff(a, b) == allowed_diff:
            return line
    return 0


part1 = sum([score(g, 0) for g in groups])
part2 = sum([score(g, 1) for g in groups])
[print(score(g, 1)) for g in groups]

print(f"Part 1: {part1}")
print(f"Part 2: {part2}")