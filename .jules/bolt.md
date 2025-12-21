## 2024-05-23 - [Optimizing OpenLB Output Loop]
**Learning:** In simulation loops (like OpenLB), helper functions like `getResults` are often called every time step. If these functions unconditionally instantiate heavy objects (like VTK writers or complex functors), it creates significant overhead even when no output is generated.
**Action:** Always check loop conditions (e.g., `iT % vtkIter == 0`) *before* instantiating objects or performing lookups. Use early returns to exit the function immediately if no work is needed for the current iteration.
