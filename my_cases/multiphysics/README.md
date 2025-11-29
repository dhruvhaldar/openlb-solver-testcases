# 🌡️ Multiphysics: Thermal Square Cavity

[![OpenLB](https://img.shields.io/badge/Solved_with-OpenLB-blue.svg)](https://www.openlb.net/)
[![Domain](https://img.shields.io/badge/Domain-Multiphysics-purple.svg)]()
[![Dimension](https://img.shields.io/badge/Dimension-2D-green.svg)]()

## 📝 Description

This test case simulates **natural convection** in a differentially heated square cavity. It is a classic benchmark problem (Rayleigh-Bénard convection) for validating thermal fluid solvers.

## 📚 Theoretical Background

### Natural Convection
Fluid motion is driven by density differences due to temperature gradients (buoyancy).
*   **Hot Wall**: Fluid expands, density decreases, and fluid rises.
*   **Cold Wall**: Fluid contracts, density increases, and fluid sinks.

### Boussinesq Approximation
This model simplifies the coupling between heat and momentum. Variations in density are neglected everywhere except in the buoyancy term of the momentum equation:
$$
\rho \frac{D\mathbf{u}}{Dt} = -\nabla p + \mu \nabla^2 \mathbf{u} + \rho_0 \mathbf{g} [1 - \beta (T - T_0)]
$$
Where:
*   $\mathbf{g}$: Gravity vector.
*   $\beta$: Thermal expansion coefficient.
*   $T - T_0$: Temperature deviation.

### Dimensionless Numbers
The flow regime is governed by:
*   **Rayleigh Number (Ra)**: Ratio of buoyancy to viscous forces.
*   **Prandtl Number (Pr)**: Ratio of momentum diffusivity to thermal diffusivity.

## 💻 How to Run

1.  **Navigate to the directory**:
    ```bash
    cd my_cases/multiphysics
    ```
2.  **Compile**:
    ```bash
    make
    ```
3.  **Run**:
    ```bash
    ./squareCavity2dLaminar
    ```

## 📊 Output
*   **VTK Files**: Velocity and Temperature fields (`squareCavity2dLaminar.vtm`).
*   **Nusselt Number**: Heat transfer efficiency calculated at the walls.

[🔙 Back to Main README](../../README.md)
