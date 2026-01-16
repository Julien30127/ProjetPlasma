import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

data = pd.read_csv('Positions.csv')
n = (data.shape[1] - 1) // 3

fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

# Scatter pour gérer tous les points d'un coup (plus performant)
graph = ax.scatter([], [], [], s=10, c='cyan', edgecolors='blue', alpha=0.6)

# On fixe les limites
ax.set_xlim(data.filter(like='x').min().min(), data.filter(like='x').max().max())
ax.set_ylim(data.filter(like='y').min().min(), data.filter(like='y').max().max())
ax.set_zlim(data.filter(like='z').min().min(), data.filter(like='z').max().max())

ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
ax.set_title(f'Simulation de {n} particules chargées')

def update(frame):
    # Extraction des positions x, y, z pour l'instant 'frame'
    x_coords = [data[f'x{i}'].iloc[frame] for i in range(n)]
    y_coords = [data[f'y{i}'].iloc[frame] for i in range(n)]
    z_coords = [data[f'z{i}'].iloc[frame] for i in range(n)]
    
    # Maj globale de l'objet scatter
    graph._offsets3d = (x_coords, y_coords, z_coords)
    return graph,

ani = FuncAnimation(fig, update, frames=len(data), interval=10, blit=False)
plt.show()