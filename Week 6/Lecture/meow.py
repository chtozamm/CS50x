import sys

n = int(sys.argv[1])

def main():
    meow(n)

def meow(n):
    for i in range(n):
        print("meow")
main()