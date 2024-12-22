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
print(gamelist)
points = 0
bob = (Counter(gamelist[0]))
if max(bob) == 1:
    points += 4
print(points)


    

    