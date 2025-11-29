# 🌀 Turbulence: Taylor-Green Vortex 3D

[![OpenLB](https://img.shields.io/badge/Solved_with-OpenLB-blue.svg)](https://www.openlb.net/)
[![Domain](https://img.shields.io/badge/Domain-Turbulence-black.svg)]()
[![Dimension](https://img.shields.io/badge/Dimension-3D-green.svg)]()

## 📝 Description

The **Taylor-Green Vortex (TGV)** is a fundamental benchmark case for studying the decay of isotropic turbulence. It allows for the validation of turbulence models and numerical schemes by comparing results against Direct Numerical Simulation (DNS) data.

## 📚 Theoretical Background

### Energy Cascade
The TGV demonstrates the mechanism of the turbulent energy cascade:
1.  **Large Eddies**: Contains most of the kinetic energy.
2.  **Inertial Subrange**: Energy is transferred to smaller scales.
3.  **Dissipation Range**: Viscosity dissipates energy into heat at the Kolmogorov scales.

### Initial Conditions
The flow is initialized in a periodic domain with a specific vortex structure:
$$ u = V_0 \sin(x)\cos(y)\cos(z) $$
$$ v = -V_0 \cos(x)\sin(y)\cos(z) $$
$$ w = 0 $$

### Metrics
*   **Kinetic Energy Decay**: The rate at which the total energy of the system decreases.
*   **Enstrophy**: The integral of the square of the vorticity ($\Omega = \nabla \times \mathbf{u}$). Enstrophy increases as vortices stretch and eventually peaks when the flow becomes fully turbulent before decaying.

## 💻 How to Run

1.  **Navigate to the directory**:
    ```bash
    cd my_cases/turbulence
    ```
2.  **Compile**:
    ```bash
    make
    ```
3.  **Run**:
    ```bash
    ./tgv3d
    ```

## 📊 Output
*   **VTK Files**: Instantaneous turbulent flow fields (`tgv3d.vtm`).
*   **Statistics**: Kinetic energy and dissipation rates over time.

[🔙 Back to Main README](../../README.md)
