import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

print("Chargement des données CSV...")
df = pd.read_csv('build/mhd_sph_output.csv')

print("Traitement des frames...")
grouped = df.groupby('t')
frames_data = []

x_min, x_max = df['x'].min(), df['x'].max()
y_min, y_max = df['y'].min(), df['y'].max()
z_min, z_max = df['z'].min(), df['z'].max()
rho_min, rho_max = df['rho'].min(), df['rho'].max()

for t, group in grouped:
    coords = group[['x', 'y', 'z']].values
    densities = group['rho'].values
    frames_data.append((t, coords, densities))

num_frames = len(frames_data)
num_particles = len(frames_data[0][1])
print(f"{num_frames} frames trouvées pour {num_particles} particules.")

fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

scat = ax.scatter([], [], [], s=20, c=[], cmap='plasma', vmin=rho_min, vmax=rho_max, alpha=0.9)

cbar = fig.colorbar(scat, ax=ax, pad=0.1)
cbar.set_label('Densité $\\rho$ (kg/m³)')

marge_x = (x_max - x_min) * 0.1
marge_y = (y_max - y_min) * 0.1
marge_z = (z_max - z_min) * 0.1
ax.set_xlim(x_min - marge_x, x_max + marge_x)
ax.set_ylim(y_min - marge_y, y_max + marge_y)
ax.set_zlim(z_min - marge_z, z_max + marge_z)

ax.set_xlabel('X (m)')
ax.set_ylabel('Y (m)')
ax.set_zlabel('Z (m)')
title = ax.set_title('Simulation MHD-SPH')

def update(frame_idx):
    t, coords, densities = frames_data[frame_idx]
    
    scat._offsets3d = (coords[:, 0], coords[:, 1], coords[:, 2])
    scat.set_array(densities)
    title.set_text(f'Simulation MHD-SPH | Temps: {t:.4f} s')
    
    return scat, title

print("Génération de l'animation...")
ani = FuncAnimation(fig, update, frames=num_frames, interval=50, blit=False)
plt.show()