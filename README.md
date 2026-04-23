## TizWildin FREE sample packs

| Pack | Description |
|------|-------------|
| [**TizWildin-Aurora**](https://github.com/GareBear99/TizWildin-Aurora) | 3-segment original synth melody pack with loops, stems, demo renders, and neon/cinematic phrasing |
| [**TizWildin-Obsidian**](https://github.com/GareBear99/TizWildin-Obsidian) | Dark cinematic sample pack with choir textures, menu loops, transitions, bass, atmosphere, drums, and electric-banjo extensions |
| [**TizWildin-Skyline**](https://github.com/GareBear99/TizWildin-Skyline) | 30 BPM-tagged synthwave and darkwave loops with generator snapshot and dark neon additions |
| [**TizWildin-Chroma**](https://github.com/GareBear99/TizWildin-Chroma) | Multi-segment game synthwave loop sample pack from TizWildin Entertainment |
| [**TizWildin-Chime**](https://github.com/GareBear99/TizWildin-Chime) | Multi-part 88 BPM chime collection spanning glass, void, halo, reed, and neon synthwave lanes |
| [**Free Violin Synth Sample Kit**](https://github.com/GareBear99/Free-Violin-Synth-Sample-Kit) | Physical-model violin sample kit rendered from the Instrudio violin instrument |
| [**Free Dark Piano Sound Kit**](https://github.com/GareBear99/Free-Dark-Piano-Sound-Kit) | 88 piano notes + dark/cinematic loops and MIDI |
| [**Free 808 Producer Kit**](https://github.com/GareBear99/Free-808-Producer-Kit) | 94 hand-crafted 808 bass samples tuned to every chromatic key |
| [**Free Riser Producer Kit**](https://github.com/GareBear99/Free-Riser-Producer-Kit) | 115+ risers and 63 downlifters - noise, synth, drum, FX, cinematic |
| [**Phonk Producer Toolkit**](https://github.com/GareBear99/Phonk_Producer_Toolkit) | Drift phonk starter kit - 808s, cowbells, drums, MIDI, templates |
| [**Free Future Bass Producer Kit**](https://github.com/GareBear99/Free-Future-Bass-Producer-Kit) | Loops, fills, drums, bass, synths, pads, and FX |

### Related audio projects
- [**VF-PlexLab**](https://github.com/GareBear99/VF-PlexLab) - VocalForge PersonaPlex Lab starter repo for a JUCE plugin + local backend + HTML tester around NVIDIA PersonaPlex.
- [**PAP-Forge-Audio**](https://github.com/GareBear99/PAP-Forge-Audio) - Procedural Autonomous Plugins runtime for generating, branching, validating, and restoring plugin projects from natural-language sound intent.

> 🎛️ Part of the [TizWildin Plugin Ecosystem](https://garebear99.github.io/TizWildinEntertainmentHUB/) — 16 free audio plugins with a live update dashboard.
>
> [FreeEQ8](https://github.com/GareBear99/FreeEQ8) · [XyloCore](https://github.com/GareBear99/XyloCore) · [Instrudio](https://github.com/GareBear99/Instrudio) · [Therum](https://github.com/GareBear99/Therum_JUCE-Plugin) · [BassMaid](https://github.com/GareBear99/BassMaid) · [SpaceMaid](https://github.com/GareBear99/SpaceMaid) · [GlueMaid](https://github.com/GareBear99/GlueMaid) · [MixMaid](https://github.com/GareBear99/MixMaid) · [ChainMaid](https://github.com/GareBear99/ChainMaid) · [PaintMask](https://github.com/GareBear99/PaintMask_Free-JUCE-Plugin) · [WURP](https://github.com/GareBear99/WURP_Toxic-Motion-Engine_JUCE) · [AETHER](https://github.com/GareBear99/AETHER_Choir-Atmosphere-Designer) · [WhisperGate](https://github.com/GareBear99/WhisperGate_Free-JUCE-Plugin) · [RiftWave](https://github.com/GareBear99/RiftWaveSuite_RiftSynth_WaveForm_Lite) · [FreeSampler](https://github.com/GareBear99/FreeSampler_v0.3) · [VF-PlexLab](https://github.com/GareBear99/VF-PlexLab) · [PAP-Forge-Audio](https://github.com/GareBear99/PAP-Forge-Audio)
>
> 🎵 [Awesome Audio](https://github.com/GareBear99/awesome-audio-plugins-dev) — (FREE) Awesome Audio Dev List

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
