# Sentinel Journal

## 2024-05-22 - Missing Input Validation in Simulation Parameters
**Vulnerability:** Simulation parameters like `RESOLUTION` and `REYNOLDS` were accepted from CLI without validation, leading to potential division-by-zero crashes (DoS) if set to 0 or negative values.
**Learning:** Even in scientific computing/simulation codes, input validation is crucial for availability and stability. Users might inadvertently (or maliciously) provide invalid inputs via CLI overrides.
**Prevention:** Always validate configuration parameters after loading them from all sources (defaults, config files, CLI) and before using them in calculations.
