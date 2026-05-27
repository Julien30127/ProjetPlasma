import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

with open("build/metadonnees.txt", "r") as f:
    lignes = f.readlines()
    nb_protons = int(lignes[0])

data = pd.read_csv('build/Positions.csv')

fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

graph = ax.scatter([], [], [], s=10, c='cyan', edgecolors='blue', alpha=0.6)

ax.set_xlim(data.filter(like='x').min().min(), data.filter(like='x').max().max())
ax.set_ylim(data.filter(like='y').min().min(), data.filter(like='y').max().max())
ax.set_zlim(data.filter(like='z').min().min(), data.filter(like='z').max().max())

ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
ax.set_title(f'Simulation de {nb_protons} particules chargées')

def update(frame):
    x_coords = [data[f'x{i}'].iloc[frame] for i in range(nb_protons)]
    y_coords = [data[f'y{i}'].iloc[frame] for i in range(nb_protons)]
    z_coords = [data[f'z{i}'].iloc[frame] for i in range(nb_protons)]
    
    graph._offsets3d = (x_coords, y_coords, z_coords)
    return graph,

ani = FuncAnimation(fig, update, frames=len(data), interval=10, blit=False)
plt.show()