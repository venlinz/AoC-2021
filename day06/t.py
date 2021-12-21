INPUT = "3,4,3,1,2"

with open("input.txt") as file:
    INPUT = file.read().strip()

fishes = [int(i) for i in INPUT.split(',')]
def incr(lst, i):
    return [x+i for x in lst]

#days_count = 80 for first problem
days_count = 256
for i in range(0, days_count):
    fish_count = len(fishes)
    for j in range(0, fish_count):
        if fishes[j] == 0:
            fishes[j] = 6
            fishes.append(8)
        else:
            fishes[j] -= 1

# print(INPUT)
print(len(fishes))
