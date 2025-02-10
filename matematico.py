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
while i < 25:
    i += 1
    number = random.choice(numberslist)
    print(number)
    numberslist.remove(number)
    placement = input("Place number: " )
    if placement in equivalence:
        row, col = equivalence[placement]
        gamelist[row][col] = number
        positionlist.remove(placement)
for i in range(len(gamelist[0])):
    globals()[f'col{i+1}'] = [row[i] for row in gamelist]
maindiagonal = [gamelist[i][i] for i in range(5)]
antidiagonal = [gamelist[i][4 - i] for i in range(5)]
possible = [gamelist[0], gamelist[1] ,gamelist[2] ,gamelist[3] , gamelist[4], col1, col2, col3, col4, col5, maindiagonal, antidiagonal]
print(gamelist)
points = 0
for j in possible:
    pointsa = (Counter(j))
    if any(x == 4 for x in pointsa.values()):
        quada = True
    else:
        quada = False
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
    count = 0
    for i in range(1, 14):
        triple = [i, i+1, i+2]
        if set(triple) <= set(j):
            count += 1
    if count == 1:
        seq3 = True
    else:
        seq3 = False
    if count == 2:
        seq4 = True
    else:
        seq4 = False
    if count == 2:
        seq5 = True
    else:
        seq5 = False
    if all([duoa, not trioa, not quada, not doubleduoa, not seq3, not seq4, not seq5]): 
        points += 1 # duo
    elif all([not duoa, trioa, not quada, not doubleduoa, not seq3, not seq4, not seq5]):  
        points += 2 # trio
    elif all([not duoa, not trioa, quada, not doubleduoa, not seq3, not seq4, not seq5]): 
        points += 4 # quad
    elif all([duoa, trioa, not quada, doubleduoa, not seq3, not seq4, not seq5]): 
        points += 3 # double duo
    elif all([duoa, trioa, not quada, not doubleduoa, not seq3, not seq4, not seq5]): 
        points += 5 # duo and trio
    elif all([not duoa, not trioa, not quada, not doubleduoa, seq3, not seq4, not seq5]): 
        points += 1 # 3
    elif all([not duoa, not trioa, not quada, not doubleduoa, not seq3, seq4, not seq5]): 
        points += 3 # 4
    elif all([not duoa, not trioa, not quada, not doubleduoa, not seq3, seq4, not seq5]): 
        points += 6 # 5
    elif all([duoa, not trioa, not quada, not doubleduoa, seq3, not seq4, not seq5]): 
        points += 0 # 3 and duo
    else:
        points += 0
print(points)

