import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

data = pd.read_csv('Positions.csv')
position = data.iloc[:, 1]

fig, ax = plt.subplots(figsize=(4, 8))
ax.set_xlim(-1, 1)
ax.set_ylim(0, max(position) + 10)
ax.set_xticks([])
ax.set_ylabel('Hauteur (m)')

point, = ax.plot([], [], 'ro', markersize=15)

def update(i):
    point.set_data([0], [position[i]])
    return point,

ani = FuncAnimation(fig, update, frames=len(position), interval=20, blit=True)
plt.show()