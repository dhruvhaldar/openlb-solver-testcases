# 🚗 Automotive: Venturi 3D

[![OpenLB](https://img.shields.io/badge/Solved_with-OpenLB-blue.svg)](https://www.openlb.net/)
[![Domain](https://img.shields.io/badge/Domain-Automotive-red.svg)]()
[![Dimension](https://img.shields.io/badge/Dimension-3D-green.svg)]()

## 📝 Description

This test case examines the steady flow of fluid through a **Venturi tube**, a pipe with a converging-diverging cross-section. It is a classic example used in carburetors and flow measurement devices.

## 📚 Theoretical Background

### The Venturi Effect
The Venturi effect is a manifestation of **Bernoulli's Principle**.
*   **Continuity Equation**: For an incompressible fluid, the mass flow rate is constant.
    $$ A_1 V_1 = A_2 V_2 $$
    When the fluid enters the constricted section (throat) of area $A_2 < A_1$, its velocity $V_2$ must increase.
*   **Bernoulli's Equation**:
    $$ P_1 + \frac{1}{2}\rho V_1^2 = P_2 + \frac{1}{2}\rho V_2^2 $$
    The increase in kinetic energy ($\frac{1}{2}\rho V_2^2$) comes at the expense of pressure potential energy, causing a pressure drop ($P_2 < P_1$).

### Lattice Boltzmann Method (LBM)
*   **Model**: **D3Q19** (3 Dimensions, 19 discrete velocities).
*   **Geometry**: The complex 3D shape is voxelized from an XML definition or STL file.

## 💻 How to Run

1.  **Navigate to the directory**:
    ```bash
    cd my_cases/automotive
    ```
2.  **Compile**:
    ```bash
    make
    ```
3.  **Run**:
    ```bash
    ./venturi3d
    ```

## 📊 Output
*   **VTK Files**: 3D Velocity and Pressure fields (`venturi3d.vtm`).
*   **Images**: Slices of the flow field (if configured).

[🔙 Back to Main README](../../README.md)
