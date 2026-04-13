# DSP Design Notes

## Overview
MYTHODIC treats overlap as a musical event rather than purely a problem.

Current v0.1 architecture:
1. analyze input
2. estimate masking and phase conflict
3. score Separate / Fuse / Crown
4. apply oversampled tone enhancement
5. shape stereo image
6. add room fusion
7. apply safety ceiling

## Module intent

### AnalysisEngine
Provides lightweight stereo-domain heuristics:
- transient density
- tonal stability proxy
- side energy
- mono risk
- center priority

### MaskingModel
Uses simple correlation and energy relationships to estimate:
- mask score
- phase conflict
- harmonic affinity proxy

### OverlapDecisionCore
Deterministic scoring layer that produces:
- `separate`
- `fuse`
- `crown`
- `density`

### OversampledToneCore
Current tone block is deliberately simple but correctly structured:
- drive
- oversampling
- nonlinear shaper
- wet/dry mix

### SpatialEngine
Focuses on:
- center preservation
- side bloom
- mono guard
- low-end anchoring

### RoomFusionEngine
Starter ambience layer based on crossed delays and dynamic blend.

### SafetyOutput
Applies a controlled ceiling stage and exposes peak / estimated true-peak style metrics.

## Audio-thread standards
- no GUI authority over DSP state outside parameters
- avoid allocations during process calls
- deterministic output for same input and settings
- keep modules separated by role

## Known limitations in v0.1
- masking model is heuristic, not perceptual-ground-truth
- no FFT-domain overlap reconstruction yet
- no advanced loudness meter implementation yet
- no preset serialization layer beyond APVTS state
