# 🫀 Biomedical: Aneurysm 3D

[![OpenLB](https://img.shields.io/badge/Solved_with-OpenLB-blue.svg)](https://www.openlb.net/)
[![Domain](https://img.shields.io/badge/Domain-Biomedical-pink.svg)]()
[![Dimension](https://img.shields.io/badge/Dimension-3D-green.svg)]()

## 📝 Description

This case simulates **blood flow hemodynamics** within a patient-specific cerebral aneurysm geometry. The geometry is imported from an **STL file**, demonstrating OpenLB's capability to handle complex biological structures.

## 📚 Theoretical Background

### Hemodynamics
Understanding blood flow patterns in aneurysms is critical for assessing rupture risk.
*   **Wall Shear Stress (WSS)**: The tangential force exerted by flowing blood on the vessel wall. Low or oscillating WSS is associated with endothelial dysfunction and aneurysm growth.
*   **Flow Recirculation**: Complex vortices inside the aneurysm sac can lead to thrombus formation.

### Geometry Import
OpenLB voxelizes the triangular surface mesh (STL) into a structured Cartesian grid. This process ("voxelization") is essential for the Lattice Boltzmann Method.

### Physics
*   **Fluid**: Blood is often modeled as a Newtonian fluid (constant viscosity) in large vessels, though non-Newtonian models can also be implemented.
*   **Boundary Conditions**: Pulsatile velocity profiles are typically applied at the inlet to mimic the cardiac cycle.

## 💻 How to Run

1.  **Navigate to the directory**:
    ```bash
    cd my_cases/biomedical
    ```
2.  **Compile**:
    ```bash
    make
    ```
3.  **Run**:
    ```bash
    ./aneurysm3d
    ```

## 📊 Output
*   **VTK Files**: Velocity, Pressure, and WSS fields (`aneurysm.vtm`) on the complex geometry.

[🔙 Back to Main README](../../README.md)
