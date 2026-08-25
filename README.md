# OpenWorld - Unreal Engine 5 Sandbox Game

An original open-world action game built with Unreal Engine 5, inspired by sandbox-style gameplay mechanics.

## Features

### 🎮 Character System
- **Enhanced Movement**: Walk, Sprint, Crouch with smooth transitions
- **Stamina System**: Dynamic stamina drain when sprinting, automatic recovery when resting
  - Drain Rate: 15 points/second while sprinting
  - Recovery Rate: 8 points/second while walking/standing
  - Exhaustion State: Forces walking until stamina fully recovers
- **Third-Person Camera**: Over-the-shoulder camera system
- **Combat Ready**: Health system and damage mechanics
- **Input System**: Modern Enhanced Input System integration

### 🎨 Graphics
- **Multi-tier Graphics Settings**: High, Medium, Low presets
- **Advanced Rendering**:
  - Nanite Virtualized Geometry (High)
  - Lumen Global Illumination & Reflections (High)
  - Virtual Shadow Maps
  - Temporal AA with upsampling
  - Advanced post-processing (Motion Blur, Bloom)

### 🎯 Mission System
- **Dynamic Missions**: Create and manage custom missions
- **Objective Tracking**: Multi-objective mission structure
- **Rewards**: Money and reputation system
- **Mission Status**: Active, Completed, Failed, Abandoned states

### 🚨 Wanted System
- **5-Star Wanted Levels**: Escalating police response
- **Dynamic Decay**: Wanted level decreases over time when not committing crimes
- **Real-time Tracking**: Points-based wanted system

### 🚗 Vehicle System
- **Multiple Vehicle Types**: Cars, Bikes, Trucks, Helicopters
- **Realistic Physics**: Acceleration, braking, turning
- **Engine Management**: Start/Stop engine mechanics
- **Camera System**: Dynamic vehicle camera

### ⚔️ Combat System
- **Weapon Types**: Pistols, Rifles, Shotguns, Snipers, Melee
- **Weapon Stats**: Damage, Fire Rate, Accuracy, Range
- **Ammunition System**: Magazine-based ammo management
- **Combat Actions**: Fire, Melee, Reload

## Project Structure

```
Source/
├── OpenWorld/
│   ├── Public/
│   │   ├── OpenWorldCharacter.h       # Player character with stamina
│   │   ├── GraphicsSettings.h         # Graphics management
│   │   ├── MissionSystem.h            # Quest/mission framework
│   │   ├── WantedSystem.h             # Police/wanted level system
│   │   ├── VehicleBase.h              # Vehicle base class
│   │   └── CombatSystem.h             # Combat mechanics
│   └── Private/
│       ├── OpenWorldCharacter.cpp     # Character implementation with stamina
│       └── GraphicsSettings.cpp       # Graphics settings implementation
```

## Getting Started

### Requirements
- Unreal Engine 5.0+
- Visual Studio 2022 or later
- Windows/Mac/Linux

### Setup
1. Clone this repository
2. Right-click `.uproject` file → Generate Visual Studio project files
3. Open the `.sln` file in Visual Studio
4. Build the project
5. Open the project in Unreal Engine

### Building and Running
```bash
# Generate project files
./GenerateProjectFiles.bat

# Build
msbuild OpenWorld.sln /p:Configuration=Development /p:Platform=Win64

# Launch editor
UnrealEngine/Binaries/Win64/UE4Editor.exe
```

## Controls

| Action | Input |
|--------|-------|
| Move | WASD |
| Look Around | Mouse |
| Sprint | Left Shift |
| Crouch | Ctrl |
| Fire Weapon | Left Mouse Button |
| Melee Attack | Right Mouse Button |
| Reload | R |

## Stamina System Details

The stamina system provides realistic player fatigue mechanics:

- **Max Stamina**: 100 points
- **Sprint Drain**: -15 points/second
- **Recovery Rate**: +8 points/second
- **Exhaustion**: When stamina reaches 0, player is forced to walk until fully recovered

Example flow:
1. Player starts with 100 stamina
2. Hold sprint for ~6.6 seconds → stamina depleted
3. Player is exhausted and cannot sprint
4. Stamina recovers at 8 points/second (~12.5 seconds for full recovery)
5. Once at 100%, player can sprint again

## Roadmap

- [ ] NPC System with AI
- [ ] Dialogue System
- [ ] Stealth Mechanics
- [ ] Gang System
- [ ] Real Estate / Property System
- [ ] Customization (Characters, Vehicles)
- [ ] Multiplayer Support
- [ ] Mobile Optimization

## Credits

Built with Unreal Engine 5 and the Epic Games community.

## License

This project is provided as-is for educational and development purposes.
