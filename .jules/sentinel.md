## 2024-05-23 - [Input Validation for Simulation Parameters]
**Vulnerability:** Missing input validation for `RESOLUTION` and `REYNOLDS` parameters in `aneurysm3d.cpp`. These parameters are used in division operations, leading to division by zero and application crash (DoS) if set to 0 via command line arguments.
**Learning:** Scientific simulation codes often assume "sane" inputs from researchers, but when exposed as tools (CLI), they are vulnerable to crashing on bad input. Always validate inputs that are used as denominators.
**Prevention:** Add explicit checks for positive values for all physical parameters used in division or critical logic immediately after parsing arguments.
