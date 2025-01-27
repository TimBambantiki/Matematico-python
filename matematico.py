# licensed under GNU GPL v3
import random
from collections import Counter
numberslist = [1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13 ]
gamelist = [
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None]
    ] 
    # 1 2 3 4 5     leftd rightd
    #A
    #B
    #C
    #D
    #E
positionlist = ["a1", "a2", "a3", "a4", "a5", "b1", "b2", "b3", "b4", "b5", "c1", "c2", "c3", "c4", "c5", "d1", "d2", "d3", "d4", "d5", "e1", "e2", "e3", "e4", "e5"]
equivalencelist = [(row, col) for row in range(5) for col in range(5)]
equivalence = {value: position for value, position in zip(positionlist, equivalencelist)}
# placement logic
i = 0
while i < 5:
    i += 1
    number = random.choice(numberslist)
    print(number)
    numberslist.remove(number)
    placement = input("Place number: " )
    if placement in equivalence:
        row, col = equivalence[placement]
        gamelist[row][col] = number
        positionlist.remove(placement)
# points calculation 
print(gamelist)
points = 0
pointsa = (Counter(gamelist[0]))
if any(x == 4 for x in pointsa.values()):
    points += 4
if any(x == 3 for x in pointsa.values()):
    trioa = True
else:
    trioa = False
if any(x == 2 for x in pointsa.values()):
    duoa = True
else:
    duoa = False
duos = [count for count in pointsa.values() if count == 2]
if len(duos) == 2: 
    doubleduoa = True
else:
    doubleduoa = False
if trioa is True and duoa is True:
    points += 5
if trioa is False and duoa is True and doubleduoa is False:
    points += 1
if trioa is False and duoa is True and doubleduoa is True:
    points += 3
if trioa is True and duoa is False:
    points += 2
print(pointsa)
print(points)
