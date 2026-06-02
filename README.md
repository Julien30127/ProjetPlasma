# 3D MHD-SPH Plasma Simulator

This version of the project is couples the **Smoothed Particle Hydrodynamics** numerical method with **Magnetohydrodynamics** equations to simulate the behavior of a conducting fluid (plasma in our case) subjected to magnetic fields.

## Key Features

### SPH Hydrodynamics
* **Smoothing Kernel:** Uses a standard Cubic Spline implementation for optimal inter-particle influence distribution.
* **Equation of State :** Implements Tait's equation of state to simulate a weakly compressible fluid (dense plasma/water type).
* **Artificial Viscosity:** Features Monaghan's artificial viscosity term to handle shocks and prevent unphysical particle interpenetration.

### Magnetohydrodynamics
* **Maxwell Stress Tensor:** Computes both magnetic pressure (repulsion) and magnetic tension (restoring force of field lines).
* **Induction Equation:** The magnetic field is "frozen" into the fluid (Alfvén's theorem) and deforms according to local velocity gradients.

### Computational Optimization
* **Grid Spatial Hashing (Cell-Linked List):** Neighbor search optimized via a spatial grid (Hash Table). Complexity drops from O(N²) to O(N), drastically increasing the supported particle count.
* **Modular Architecture:** Code is split into modules (`grid`, `kernel`, `physics`, `sph`) for ease of maintenance and future extensions (e.g., GPU porting).

---

## Benchmarks and analysis 

This section is empty for now.

## Lauching the code

```bash
mkdir build && cd build
cmake .. && make
```
Lancer la visualisation :

```bash
python3 visualisation.py
```