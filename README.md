# OpenLB Solver Test Cases

![OpenLB Logo](https://www.openlb.net/wp-content/uploads/2019/02/openlb_logo.png)

This repository contains a collection of **OpenLB** simulation cases covering various domains. These cases are adapted from OpenLB examples and configured for testing purposes.

## 🚀 Prerequisites

-   **OpenLB**: The `olb-release` directory contains the OpenLB library.
-   **Compiler**: A C++20 compliant compiler (e.g., `g++` 11+).
-   **Make**: GNU Make.

## 🛠️ Compilation and Execution

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

## 🧪 Test Cases & Theoretical Background

| Domain | Case Name | Description | Link |
| :--- | :--- | :--- | :--- |
| ✈️ **Aerospace** | **Airfoil 2D** | 2D flow past a NACA airfoil profile. | [Read More](my_cases/aerospace/README.md) |
| 🚗 **Automotive** | **Venturi 3D** | Steady flow through a Venturi tube. | [Read More](my_cases/automotive/README.md) |
| 🧪 **Chemical** | **Laminar Reactive T-Mixer** | Mixing and reaction in a T-shaped micromixer. | [Read More](my_cases/chemical/README.md) |
| 🌡️ **Multiphysics** | **Thermal Square Cavity** | Natural convection (Rayleigh-Bénard). | [Read More](my_cases/multiphysics/README.md) |
| 🫀 **Biomedical** | **Aneurysm 3D** | Blood flow in a patient-specific aneurysm. | [Read More](my_cases/biomedical/README.md) |
| 🌀 **Turbulence** | **Taylor-Green Vortex 3D** | Turbulence decay benchmark. | [Read More](my_cases/turbulence/README.md) |

---
*Powered by [OpenLB](https://www.openlb.net/)*
