"Program for plotting edge data from graph."
import matplotlib.pyplot as plt

x = []
y = []
N = int(raw_input())
while N > 0:
    d = input()
    a = input()
    x.append(d)
    y.append(a)

plt.plot(x, y, 'ro')
plt.show()
