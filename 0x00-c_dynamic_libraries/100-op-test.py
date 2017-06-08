import ctypes

cops = ctypes.CDLL('./100-operations.so')

print(cops.apples("I love"))
print(cops.bananas("I adore"))
print(cops.oranges("I hate.. I'm sorry but I hate"))
print(cops.pineapples("There's nothing better than"))
print(cops.kiwis("except kiwis"))
