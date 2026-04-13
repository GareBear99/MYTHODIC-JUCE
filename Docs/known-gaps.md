# Known Gaps

This repository is intentionally honest about what is not finished yet.

## DSP gaps
- The masking model is a lightweight heuristic starter, not a production psychoacoustic model.
- Estimated true-peak is simplified and should not be marketed as standards-grade metering yet.
- Room fusion is a compact ambience layer, not a full diffusion/reverb architecture.
- The spectral overlap engine is represented by starter logic rather than a full STFT/WOLA implementation.

## Product gaps
- No preset browser yet.
- No A/B compare or undo history UI.
- No pluginval report or DAW compatibility matrix included yet.
- No performance benchmark numbers published yet.

## Public-release gate
Before calling this a finished public release, the project should add:
- pluginval / DAW validation reports
- macOS and Windows build confirmation
- stronger safety metering
- preset management
- screenshots / audio demos / release notes
