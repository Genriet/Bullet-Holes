# Bullet Holes — Persistent Impact Decals for DayZ

Bullet Holes adds persistent bullet impact decals to DayZ, allowing players to see where shots hit instead of having to rely on particles.

Decals are aligned to the surface normal and can attach to animated parts of supported objects, allowing them to move and rotate with doors and other components.

The mod provides configurable decal behavior, surface support, object and surface filtering, and limits for managing decal lifetime and quantity.

## Features

- **Persistent bullet holes:** Spawn impact decals at bullet entry points.
- **Animated object support:** Attach decals to moving parts so they follow the object's position and rotation.
- **Surface-specific decals:** Support concrete, glass, metal, plaster, plastic, rubber, textile, and wood.
- **Configurable behavior:** Enable or disable decal types and control placement offsets, filtering, and debugging.
- **Decal limits:** Configure global and per-object limits, as well as decal lifetime.
- **Surface and object filtering:** Exclude selected surface types and object classes from decal generation.
- **Client-only mode:** Optionally spawn decals only on the client.

## Showcase

[![Watch Bullet Holes showcase](https://img.youtube.com/vi/8mb1BENnCgE/hqdefault.jpg)](https://youtu.be/8mb1BENnCgE)

## Supported Surfaces

Bullet Holes currently supports impact decals for:

- Concrete
- Glass
- Metal
- Plaster
- Plastic
- Rubber
- Textile
- Wood

Different decal variations can be configured for each surface type.

## Configuration

Bullet Holes uses JSON configuration to control decal generation and management.

Example configuration:

```json
{
  "Enabled": true,
  "ClientOnly": true,
  "PrintDebug": false,
  "NormalOffset": 0.015,
  "BulletEnterDecals": true,
  "BulletExitDecals": false,
  "BulletStopDecals": false,
  "BulletRicochetDecals": false,
  "MeleeDecals": false,
  "ExplosionDecals": false,
  "GlobalMaxLimit": -1,
  "GlobalMaxTime": -1,
  "LimitPerObject": -1,
  "IgnoreSurfaces": [
    "Hit_Grass",
    "Hit_Dirt",
    "Hit_Sand",
    "Hit_Gravel",
    "Hit_Snow",
    "Hit_Foliage",
    "Hit_Foliage_Green",
    "Hit_Foliage_Conifer",
    "Hit_MeatBones",
    "Hit_Undefined",
    "Hit_ErrorNoMaterial"
  ],
  "IgnoreObjects": [
    "CarScript",
    "CarDoor",
    "ItemBase"
  ],
  "VariantsPerSurface": 5
}
```

### Configuration options

| Option | Description |
|---|---|
| `Enabled` | Enables or disables the mod's decal system. |
| `ClientOnly` | Spawns decals only on the client when enabled. |
| `PrintDebug` | Prints diagnostic information to the script log. |
| `NormalOffset` | Offsets decals from the surface to help reduce Z-fighting. |
| `BulletEnterDecals` | Enables bullet entry decals. |
| `BulletExitDecals` | Enables bullet exit decals. |
| `BulletStopDecals` | Enables decals for stopped bullets. |
| `BulletRicochetDecals` | Enables ricochet decals. |
| `MeleeDecals` | Enables melee impact decals. |
| `ExplosionDecals` | Enables explosion impact decals. |
| `GlobalMaxLimit` | Maximum number of decals globally; `-1` means unlimited. |
| `GlobalMaxTime` | Time before decals are removed; `-1` means they do not expire. |
| `LimitPerObject` | Maximum number of decals per object; `-1` means unlimited. |
| `IgnoreSurfaces` | Surface material types excluded from decal generation. |
| `IgnoreObjects` | Object classes excluded from decal generation. |
| `VariantsPerSurface` | Number of decal variations available per surface type. |

## Known Issues and Limitations

- **Z-fighting:** Decals can visually conflict with the underlying geometry because of limitations in DayZ's decal support.
- **Placement accuracy:** Bullet impact positions may be imprecise due to limitations in the game's fire geometry.
- **Animated object performance:** Large numbers of decals attached to animated objects can cause FPS drops because their positions must be updated as the objects move.
- **Exit decal placement:** The game does not provide sufficiently accurate exit points, so exit decals may appear inside objects.
- **Limited decal types:** Currently, only bullet entry decals are supported. Exit, stopped-bullet, ricochet, melee, and explosion decals are not yet implemented.
- **Vehicle exclusions:** `CarScript` and `CarDoor` are excluded by default because broken or despawned vehicle components complicate decal management and attachment behavior.

## For Modders
- **Workshop:** [Bullet Holes](https://steamcommunity.com/sharedfiles/filedetails/?id=3693505149)

Bullet Holes uses configurable surface types, object filters, and decal variations to control where impact marks appear.
You can customize the configuration to exclude additional surfaces or objects, adjust decal limits, and integrate variations for supported surface types.
