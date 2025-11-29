# OpenLB Solver Test Cases

This repository contains a collection of OpenLB simulation cases covering various domains. These cases are adapted from OpenLB examples and configured for testing purposes.

## Prerequisites

-   **OpenLB**: The `olb-release` directory contains the OpenLB library.
-   **Compiler**: A C++20 compliant compiler (e.g., g++ 11+).
-   **Make**: GNU Make.

## Compilation and Execution

The OpenLB library must be compiled first:

```bash
cd olb-release
cp config/cpu_gcc_openmpi.mk config.mk  # Or appropriate config
# Edit config.mk to set PARALLEL_MODE := OFF if MPI is not available
make
```

To run a specific test case, navigate to its directory, compile, and run:

```bash
cd my_cases/<domain>
make
./<executable_name>
```

## Test Cases

### 1. Aerospace: Airfoil 2D
-   **Location**: `my_cases/aerospace`
-   **Description**: Simulation of a 2D flow past a NACA airfoil.
-   **Execution**:
    ```bash
    cd my_cases/aerospace
    make
    ./airfoil2d
    ```

### 2. Automotive: Venturi 3D
-   **Location**: `my_cases/automotive`
-   **Description**: Steady flow simulation in a 3D venturi tube.
-   **Execution**:
    ```bash
    cd my_cases/automotive
    make
    ./venturi3d
    ```

### 3. Chemical: Laminar Reactive T-Mixer
-   **Location**: `my_cases/chemical`
-   **Description**: Simulation of laminar reactive micromixing in a T-shaped mixer.
-   **Execution**:
    ```bash
    cd my_cases/chemical
    make
    ./laminarReactiveTmixer
    ```

### 4. Multiphysics: Thermal Square Cavity
-   **Location**: `my_cases/multiphysics`
-   **Description**: Natural convection in a square cavity with thermal coupling.
-   **Execution**:
    ```bash
    cd my_cases/multiphysics
    make
    ./squareCavity2dLaminar
    ```

### 5. Biomedical: Aneurysm 3D
-   **Location**: `my_cases/biomedical`
-   **Description**: Blood flow simulation in an aneurysm geometry (STL).
-   **Execution**:
    ```bash
    cd my_cases/biomedical
    make
    ./aneurysm3d
    ```

### 6. Turbulence: Taylor-Green Vortex 3D
-   **Location**: `my_cases/turbulence`
-   **Description**: Taylor-Green Vortex benchmark for turbulence models.
-   **Execution**:
    ```bash
    cd my_cases/turbulence
    make
    ./tgv3d
    ```
