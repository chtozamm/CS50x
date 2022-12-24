while True:
    try:
        height = int(input("Height: "))
    except:
        print("Invalid number")
        continue

    if height > 0 and height < 9:
        break

for i in range(height):
    spaces = height - i
    print(" " * (spaces-1), end="")
    print("#" * (i+1), end="  ")
    print("#" * (i+1))
