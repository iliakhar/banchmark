import numpy as np
import matplotlib.pyplot as plt

gistfile = open('forGist.txt','r')
line = gistfile.readline()
x = []
y = []
while(line!=""):
    x.append(line[0:line.index(' ')])
    y.append(float(line[line.index(' ')+1:len(line)-1]))
    line = gistfile.readline()
gistfile.close()
fig = plt.figure(figsize=(6,4))
ax = fig.add_subplot()
plt.xlabel('Functions')
plt.ylabel('Perf')
ax.bar(x,y)
ax.grid()
ax.grid(axis = 'x')
ax.set_title("Perfomance")

for i in range(len(x)):
    plt.text(i, y[i], y[i], ha = 'center')

plt.show()
