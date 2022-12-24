# Calculates the result of division

try:
    x = int(input("x: "))
except:
    print("Invalid number")
    exit()
try:
    y = int(input("y: "))
except:
    print("Invalid number")
    exit()
z = x / y
print(f"{z:.0f}")
