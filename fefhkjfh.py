from collections import Counter
gamelist = [
    [1, 1, 1, 2, 2],
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None],
    [None, None, None, None, None]
    ] 
points = 0
counta = sum(1 for x in my_list if x > 3)
pointsa = (Counter(gamelist[0]))
if any(x == 4 for x in pointsa.values()):
    points += 4
else:
    if any(x == 3 for x in pointsa.values()):
        triplea = True
    if any(x == 2 for x in pointsa.values()):
        bb = True
print(pointsa)
print(points)