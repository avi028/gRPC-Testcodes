import os
import sys
import subprocess


def dyanamicLoad(n, requests):

    f = open('data' + str(n), 'w')
    for i in range(n):

        childid = os.fork()

        if childid == 0:

            cmd = "./client",0 , str(requests)

            subprocess.call(cmd, stdout=f)
            f.close()
            sys.exit()


# Driver code
dyanamicLoad(int(sys.argv[1]), int(sys.argv[2]))
