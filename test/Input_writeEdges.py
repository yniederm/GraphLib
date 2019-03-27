from random import randint, random
import sys

def main():
    """
    Usage: $ python Input_writeEdges.py [nodes] [edges]
    """
    nodes = 10
    edges = 60
    if len(sys.argv) == 3:
        nodes = int(sys.argv[1])
        edges = int(sys.argv[2])

    with open("test/Input_edges","w") as wr:
        for i in range(edges):
            p1 = randint(0,    nodes-1)
            p2 = randint(0, nodes-1)
            wr.write("%s %s 1\n" % (p1, p2))


if __name__ == '__main__':
    main()