# Palette's Journal

## 2024-05-22 - Silent Simulation Feedback
**Learning:** Hardcoded output intervals that exceed the default simulation time lead to "silent" execution where the user receives no feedback until completion, making the system appear frozen.
**Action:** Always define progress/output intervals as a fraction of the total simulation duration (e.g., `totalTime / 20`) rather than fixed time units, ensuring consistent feedback regardless of the simulation scale.

## 2024-05-23 - Explicit CLI Banners
**Learning:** Simulations starting without explicit parameter summaries and completion confirmations leave users unsure if the correct configuration was loaded or if the process finished successfully vs. crashed silently.
**Action:** Implement standardized start/end banners in CLI applications that echo critical parameters (Reynolds, Resolution) and explicitly confirm successful completion.
