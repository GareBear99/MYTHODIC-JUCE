# MYTHODIC

**MYTHODIC** is a JUCE-based audio plugin starter package built around one idea:

> when sounds collide, decide whether they should **separate**, **fuse**, or **crown**.

That makes MYTHODIC different from a standard EQ, saturator, widener, or reverb. It is an **overlap-intelligence** concept for shaping how layered sounds line up in **spectrum, phase, and stereo space** so stacked productions feel more premium, more intentional, and less smeared.

## What this repository is

This repository is a **public-facing, compile-oriented starter baseline** for MYTHODIC.

It includes:
- a CMake-based **JUCE plugin scaffold**
- a deterministic DSP split for **analysis, masking, overlap decisions, tone, space, room, and safety**
- a working editor shell with premium visual direction
- GitHub hygiene files for public release
- documentation for roadmap, testing, gaps, launch posture, and discovery positioning

It does **not** pretend to be a fully validated commercial release yet.

## What the plugin is trying to do

MYTHODIC is designed for moments where stacked material competes for the same perceptual space.

Examples:
- layered synths that sound wide but lose definition
- vocal + ambience combinations that feel expensive but still readable
- lead/support conflicts where one thing should dominate and the rest should become aura
- buses that need richness without blowing up mono compatibility
- “around the room” energy that stays intentional instead of turning into fog

The processor expresses that with three musical outcomes.

### Separate
Use when overlap is hiding clarity.

### Fuse
Use when overlap should become one richer composite tone.

### Crown
Use when one source must stay king and the support should move into halo, edge, or room.

## Repository contents

```text
MYTHODIC/
  Source/
    dsp/
    util/
  Docs/
  Assets/
  site/
  .github/
  CMakeLists.txt
  README.md
```

## Current architecture

Signal flow:

`Input → analysis → masking model → overlap decision → oversampled tone → spatial engine → room fusion → safety output`

### Included modules
- `AnalysisEngine`
- `MaskingModel`
- `OverlapDecisionCore`
- `OversampledToneCore`
- `SpatialEngine`
- `RoomFusionEngine`
- `SafetyOutput`

## Build targets

Current CMake target builds:
- **VST3**
- **AU**
- **Standalone**

JUCE can be provided either:
- as a `JUCE/` subdirectory, or
- via `-DJUCE_DIR=/path/to/JUCE`

## Quick start

### 1. Configure
```bash
cmake -S . -B build -DJUCE_DIR=/path/to/JUCE
```

### 2. Build
```bash
cmake --build build --config Release
```

## Current controls

### Main
- Myth
- Fuse
- Crown
- Orbit
- Halo
- Output

### Internals already wired in state
- mask sensitivity
- phase lock
- transient protect
- density
- tone mode
- drive
- tone mix
- oversampling mode
- air spread
- center sanctity
- sub mono threshold
- mono guard
- room amount
- room ducking
- early/late bias
- true-peak ceiling
- safe mode

## What is implemented now

- project structure
- public repo package
- parameter model
- DSP pipeline skeleton
- oversampled nonlinear tone stage
- stereo spatial shaping
- room fusion layer
- output ceiling stage
- editor shell
- preset manifest starter

## What still needs deeper work

- stronger psychoacoustic masking model
- true standards-grade loudness / true-peak metering
- production preset browser and state UX
- full spectral-domain overlap engine
- screenshots, audio demos, and benchmark results
- plugin validation and cross-DAW testing

## Documentation map

- [`Docs/dsp-design.md`](Docs/dsp-design.md)
- [`Docs/roadmap.md`](Docs/roadmap.md)
- [`Docs/testing.md`](Docs/testing.md)
- [`Docs/known-gaps.md`](Docs/known-gaps.md)
- [`Docs/release-checklist.md`](Docs/release-checklist.md)
- [`Docs/seo-keywords.md`](Docs/seo-keywords.md)
- [`Docs/media-kit.md`](Docs/media-kit.md)

## Public positioning

Suggested GitHub description:

**Overlap-intelligence audio plugin starter for shaping how sounds fuse, separate, and occupy space.**

Suggested topics:
- `juce`
- `audio-plugin`
- `vst3`
- `au-plugin`
- `audio-dsp`
- `stereo-imaging`
- `mixing`
- `mastering`
- `saturation`
- `spatial-audio`

## License

MIT.

## Maintainer

Created and packaged for the TizWildin ecosystem.
