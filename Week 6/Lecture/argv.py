from sys import argv

# if len(argv) == 2:
#     print("Hello, " + argv[1])
# else:
#     print("hello, world")

for arg in argv[1:]:
    print(arg)