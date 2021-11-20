import sys, os, subprocess

requests = int(sys.argv[2])
n = int(sys.argv[1])

for i in range(1, n + 1):
    cmd = "python", "analysis.py", str(i), str(requests)
    f = open("data" + str(i), "w")
    subprocess.call(cmd, stdout=f)
    f.close()
