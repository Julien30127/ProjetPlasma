import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

data = pd.read_csv('Positions.csv')
n = (data.shape[1] - 1) // 3

# Figure 3D
fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

couleurs = ['red', 'blue', 'green', 'orange', 'purple', 'grey']

# Création des objets : un point (tête) et une ligne (trajectoire) par particule
points = [ax.plot([], [], [], 'o', color=couleurs[i], markersize=4)[0] for i in range(n)]
lignes = [ax.plot([], [], [], '-', color=couleurs[i], alpha=0.5, lw=1)[0] for i in range(n)]

# Ajustement des limites (automatique selon les données)
ax.set_xlim(data.filter(like='x').min().min(), data.filter(like='x').max().max())
ax.set_ylim(data.filter(like='y').min().min(), data.filter(like='y').max().max())
ax.set_zlim(data.filter(like='z').min().min(), data.filter(like='z').max().max())

ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
ax.set_title('Confinement magnétique de 5 protons')

def update(frame):
    # Effet de traînée
    start = max(0, frame - 50)
    for i in range(n):
        x = data[f'x{i}'].iloc[frame]
        y = data[f'y{i}'].iloc[frame]
        z = data[f'z{i}'].iloc[frame]
        
        points[i].set_data([x], [y])
        points[i].set_3d_properties([z])
        
        lignes[i].set_data(data[f'x{i}'].iloc[start:frame], data[f'y{i}'].iloc[start:frame])
        lignes[i].set_3d_properties(data[f'z{i}'].iloc[start:frame])
        
    return points + lignes

# Animation fluide
ani = FuncAnimation(fig, update, frames=len(data), interval=20, blit=False)
plt.show()