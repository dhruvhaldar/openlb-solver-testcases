## 2024-05-22 - Missing Input Validation in Airfoil Simulation
**Vulnerability:** The `airfoil2d` simulation accepted `RESOLUTION` and `REYNOLDS` parameters directly from CLI without validation, creating a risk of division-by-zero crashes or undefined behavior if users provided non-positive values.
**Learning:** Reusing simulation code patterns (like `myCaseParameters.fromCLI`) across different modules can propagate security gaps (missing validation) if the base pattern doesn't enforce them.
**Prevention:** Systematically review all entry points for user input (CLI, config files) in every new simulation case and enforce constraints (e.g., `> 0`) immediately after loading.
