## 2024-05-23 - Console Output Clarity

**Learning:** Scientific simulation tools often lack clear start/stop indicators and file output locations, leaving users guessing if the process hung or where results went.
**Action:** Always wrap long-running CLI processes with explicit "Starting [process]... Output: [files]" and "Completed successfully" messages. Use `clout` or standard logging wrapper for consistency.
