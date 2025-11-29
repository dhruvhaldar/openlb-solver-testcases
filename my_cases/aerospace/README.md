# ✈️ Aerospace: Airfoil 2D

[![OpenLB](https://img.shields.io/badge/Solved_with-OpenLB-blue.svg)](https://www.openlb.net/)
[![Domain](https://img.shields.io/badge/Domain-Aerospace-orange.svg)]()
[![Dimension](https://img.shields.io/badge/Dimension-2D-green.svg)]()

## 📝 Description

This test case simulates the **2D fluid flow past a NACA airfoil profile**. It serves as a fundamental benchmark for external aerodynamics, calculating key performance metrics such as **Lift** and **Drag** coefficients. The simulation is set in a channel with a defined inlet velocity and outlet pressure.

## 📚 Theoretical Background

### Fluid Dynamics
The simulation solves the **incompressible Navier-Stokes equations** for Newtonian fluids.

$$
\frac{\partial \mathbf{u}}{\partial t} + (\mathbf{u} \cdot \nabla) \mathbf{u} = -\frac{1}{\rho} \nabla p + \nu \nabla^2 \mathbf{u}
$$

$$ 
\nabla \cdot \mathbf{u} = 0
$$

### Lattice Boltzmann Method (LBM)
*   **Model**: **D2Q9** (2 Dimensions, 9 discrete velocities).
*   **Collision Operator**: BGK or Smagorinsky-LES (depending on configuration).
*   **Boundary Conditions**:
    *   **Inlet**: Velocity profile (Dirichlet for $\mathbf{u}$).
    *   **Outlet**: Pressure boundary (Dirichlet for $p$).
    *   **Airfoil Surface**: Curved boundary conditions (e.g., Bouzidi) to approximate the non-grid-aligned geometry.

### Aerodynamics
As the fluid flows over the airfoil, the curvature forces the flow to accelerate over the upper surface compared to the lower surface. According to **Bernoulli's Principle**, this velocity increase leads to a pressure drop:

$$
p + \frac{1}{2}\rho v^2 = \text{constant}
$$

The pressure difference between the lower and upper surfaces generates **Lift**. The resistance to the fluid motion generates **Drag**.

## 💻 How to Run

1.  **Navigate to the directory**:
    ```bash
    cd my_cases/aerospace
    ```
2.  **Compile**:
    ```bash
    make
    ```
3.  **Run**:
    ```bash
    ./airfoil2d
    ```

## 📊 Output
*   **VTK Files**: Velocity and Pressure fields (`airfoil2d.vtm`) for visualization in ParaView.
*   **Console**: Lift and Drag coefficients, MLUPs (Mega Lattice Updates per Second).

[🔙 Back to Main README](../../README.md)
