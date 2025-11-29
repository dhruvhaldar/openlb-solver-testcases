# 🧪 Chemical: Laminar Reactive T-Mixer

[![OpenLB](https://img.shields.io/badge/Solved_with-OpenLB-blue.svg)](https://www.openlb.net/)
[![Domain](https://img.shields.io/badge/Domain-Chemical-yellow.svg)]()
[![Dimension](https://img.shields.io/badge/Dimension-3D-green.svg)]()

## 📝 Description

This case simulates the mixing and chemical reaction of two species in a **T-shaped micromixer**. It demonstrates the capability of OpenLB to handle **multi-component transport** coupled with **fluid dynamics**.

## 📚 Theoretical Background

### Advection-Diffusion-Reaction (ADR)
The simulation couples the momentum equation with mass transport equations.
1.  **Navier-Stokes**: Solves for the fluid velocity field $\mathbf{u}$.
2.  **Species Transport**: For each chemical species $i$, the concentration $C_i$ evolves as:
    $$ \frac{\partial C_i}{\partial t} + \nabla \cdot (\mathbf{u} C_i) = \nabla \cdot (D_i \nabla C_i) + R_i $$
    *   **Advection** ($\mathbf{u} C_i$): Transport by fluid flow.
    *   **Diffusion** ($D_i \nabla C_i$): Molecular mixing.
    *   **Reaction** ($R_i$): Chemical transformation (e.g., $A + B \rightarrow C$).

### Multi-Lattice Coupling
*   **Lattice 1**: **D3Q19** for fluid momentum (Navier-Stokes).
*   **Lattice 2+**: **D3Q7** (or similar) for scalar transport of each species.
*   **Coupling**: The velocity computed in Lattice 1 transports the scalars in Lattice 2+.

## 💻 How to Run

1.  **Navigate to the directory**:
    ```bash
    cd my_cases/chemical
    ```
2.  **Compile**:
    ```bash
    make
    ```
3.  **Run**:
    ```bash
    ./laminarReactiveTmixer
    ```

## 📊 Output
*   **VTK Files**: Velocity field and Concentration fields for species A, B, and Product (`mixer_wholeReaction.vtm`).
*   **Mixing Efficiency**: Concentration statistics at the outlet.

[🔙 Back to Main README](../../README.md)
