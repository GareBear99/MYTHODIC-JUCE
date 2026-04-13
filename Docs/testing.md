# Testing Plan

## Build validation
- macOS + Xcode
- Windows + Visual Studio
- plugin formats: AU, VST3, Standalone

## Runtime validation
- open/close plugin repeatedly
- automate key parameters
- save/restore state
- verify no crashes at common sample rates
- verify silence-in / silence-out stability

## Audio checks
- mono compatibility at high Orbit/Halo settings
- no obvious clicks when changing tone mode
- oversampling mode switching should be reviewed carefully
- verify output ceiling behavior at hot input levels

## Performance checks
- compare Live / Mix / Render quality cost
- verify CPU behavior at 44.1k / 48k / 96k
- test low buffer sizes in at least one DAW per platform

## Future deeper QA
- pluginval
- null-ish comparisons on deterministic settings
- loudness / true-peak verification against trusted tooling
