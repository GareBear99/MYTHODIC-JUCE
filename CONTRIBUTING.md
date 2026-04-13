# Contributing

Thanks for taking a serious look at MYTHODIC.

## Before you open a PR
- read `Docs/dsp-design.md`
- check `Docs/testing.md`
- keep changes small and reviewable
- avoid mixing GUI, DSP, and build changes in one PR unless necessary

## Technical expectations
- keep DSP deterministic for the same input and settings
- avoid heap allocation in the audio thread
- no hidden state changes inside GUI code
- explain audible intent and measurable effect in your PR description

## Commit guidance
Use clear, scoped commits. Example:
- `dsp: tighten mono guard side reduction`
- `gui: refine overlap orb meter labels`
- `build: simplify JUCE path resolution`

## Pull request checklist
- [ ] builds locally
- [ ] no new warnings introduced intentionally
- [ ] parameter state restores correctly
- [ ] audio thread stays allocation-safe
- [ ] documentation updated when behavior changes
