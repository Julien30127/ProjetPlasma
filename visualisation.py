import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

data = pd.read_csv('Positions.csv')
temps = data['temps']
n = (data.shape[1] - 1) // 2

fig, ax = plt.subplots()
ax.set_xlim(-10, 100)
ax.set_ylim(0, data.filter(like='y').max().max() + 10)

points = [ax.plot([], [], 'o')[0] for _ in range(n)]

def update(frame):
    for i in range(n):
        x = data[f'x{i}'].iloc[frame]
        y = data[f'y{i}'].iloc[frame]
        points[i].set_data([x], [y])
    return points

ani = FuncAnimation(fig, update, frames=len(data), interval=20, blit=True)
plt.show()