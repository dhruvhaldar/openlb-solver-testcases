## 2024-05-22 - Missing Input Validation in Airfoil Simulation
**Vulnerability:** The `airfoil2d` simulation accepted `RESOLUTION` and `REYNOLDS` parameters directly from CLI without validation, creating a risk of division-by-zero crashes or undefined behavior if users provided non-positive values.
**Learning:** Reusing simulation code patterns (like `myCaseParameters.fromCLI`) across different modules can propagate security gaps (missing validation) if the base pattern doesn't enforce them.
**Prevention:** Systematically review all entry points for user input (CLI, config files) in every new simulation case and enforce constraints (e.g., `> 0`) immediately after loading.

## 2024-05-23 - Logic Error / DoS in TGV3D
**Vulnerability:** The `getDNSValues` function in `tgv3d.cpp` modified a global flag (`plotDNS`) upon encountering unsupported parameters but continued execution instead of returning. This led to attempting to read an uninitialized filename and subsequently crashing due to out-of-bounds access on an empty data vector.
**Learning:** Modifying global state to signal error conditions (side-effects) is insufficient flow control. It creates a false sense of security that the "flag" will protect downstream code, while the local execution flow continues into the danger zone.
**Prevention:** Always combine error signaling (setting flags/throwing exceptions) with immediate control flow changes (returning early/breaking) to prevent execution from reaching invalid states.
