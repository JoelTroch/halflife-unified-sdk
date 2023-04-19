# Map Upgrades

This is a list of upgrades applied to maps when using the [ContentInstaller](../README.md#tools) or [MapUpgrader](../README.md#tools) to upgrade a map.

Some upgrades are applied to all maps, some only to maps made for a specific game.

Some upgrades are map-specific. Specific entity setups in custom maps may not be upgradeable automatically.

Updating custom maps is best done by making a copy of the original map source file and modifying it as needed. These upgrades can be used as a guideline to look for things that need changing.

Table of contents:
* [Applied to all maps](#applied-to-all-maps)
* [Half-Life-specific](#half-life-specific)

## Applied to all maps

### AdjustMaxRangeUpgrade

Adjusts the `MaxRange` keyvalue for specific maps to fix graphical issues
when geometry is further away than the original value.

### AdjustShotgunAnglesUpgrade

Opposing Force and Blue Shift's shotgun world model has a different alignment.
Since we're using the vanilla Half-Life model the angles need adjusting.
This adjusts the angles to match the original model.

### ChangeBell1SoundAndPitch

Find all buttons/bell1.wav sounds that have a pitch set to 80.
Change those to use an alternative sound and set their pitch to 100.

### ConvertAngleToAnglesUpgrade

Converts the obsolete `angle` keyvalue to `angles`.
This is normally done by the engine, but to avoid having to account for both keyvalues in other upgrades this is done here.

### ConvertBarneyModelUpgrade

Converts `monster_barney_dead` entities with custom body value to use the new `bodystate` keyvalue.

### ConvertBreakableItemUpgrade

Converts `func_breakable`'s spawn object keyvalue from an index to a classname.

### ConvertOtisModelUpgrade

Converts the `monster_otis` model and body value to the appropriate keyvalues.

### ConvertSoundIndicesToNamesUpgrade

Converts all entities that use sounds or sentences by index to use sound filenames or sentence names instead.

### ConvertWorldItemsToItemUpgrade

Converts `world_items` entities to their equivalent entity.

### ConvertWorldspawnGameTitleValueUpgrade

Converts the `gametitle` keyvalue to a string containing the game name.

### FixNonLoopingSoundsUpgrade

Fixes `ambient_generic` entities using non-looping sounds
to stop them from restarting when loading a save game.

### FixRenderColorFormatUpgrade

Fixes the use of invalid render color formats in some maps.

### PruneExcessMultiManagerKeysUpgrade

Prunes excess keyvalues specified for `multi_manager` entities.
In practice this only affects a handful of entities used in retinal scanner scripts.

### RemoveDMDelayFromChargersUpgrade

Removes the `dmdelay` keyvalue from charger entities. The original game ignores these.

### RenameEntityClassNamesUpgrade

Renames weapon and item classnames to their primary name.

### RenameMessagesUpgrade

Renames the messages used in `env_message` entities and `worldspawn` to use a game-specific prefix.

### ReworkGamePlayerEquipUpgrade

Changes all unnamed `game_player_equip` entities to be fired on player spawn.

### ReworkMusicPlaybackUpgrade

Reworks how music is played to use `ambient_music` instead.

### SetCustomHullForGenericMonstersUpgrade

Sets a custom hull size for `monster_generic` entities that use a model that was originally hard-coded to use one.

## Half-Life-specific

### C2a5FixBarrelPushTriggersUpgrade

Fixes the barrels in `c2a5` not flying as high as they're supposed to on modern systems due to high framerates.

### C2a5FixCrateGlobalNameUpgrade

Removes the `globalname` keyvalue from the `func_breakable` crates next to the dam in `c2a5`.
The globalname is left over from copy pasting the entity from the crates in the tunnel earlier in the map
and causes these crates to disappear.

### C3a2bFixWaterValvesUpgrade

Prevents players from soft-locking the game by turning both valves at the same time in
`c3a2b` (Lambda Core reactor water flow).

### C3a2FixLoadSavedUpgrade

Increases the reload delay after killing the scientist in `c3a2`
to allow the entire game over message to display.

### C4a2FixNihilanthDialogueUpgrade

Fixes Nihilanth's dialogue not playing at the start of `c4a2` (Gonarch's Lair).

### C4a3FixFlareSpritesUpgrade

Fixes the flare sprites shown during Nihilanth's death script using the wrong render mode.

