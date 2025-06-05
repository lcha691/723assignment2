# Cruise Controller – COMPSYS 723 Assignment 2
Authors: Connor Dunn (cdun954), Lachlan Chan (lcha691)

## Overview
This project implements a functional Cruise Control system in the synchronous language Esterel. The cruise controller is composed of three coordinated submodules that run in parallel:

1. **Cruise State Controller**
2. **Cruise Speed Controller**
3. **Throttle Controller**

The system manages vehicle throttle based on driver input (e.g. set, resume, brake, etc.) and vehicle speed conditions. A PID-based regulation strategy is used when the cruise controller is ON.

---

## Module Descriptions

### 1. Cruise State Controller (`cruiseFSM`)
Determines the cruise system’s state based on input conditions and driver actions.

**States:**
- `1`: Cruise Off  
- `2`: Cruise On  
- `3`: Cruise Standby  
- `4`: Cruise Disable

**Key Transitions:**
- ON button pressed → ON state
- Brake > `PedalsMin` → STANDBY
- Accel > `PedalsMin` or Speed out of `[SpeedMin, SpeedMax]` → DISABLE
- Resume pressed with valid speed and no accel → ON

**Thresholds:**
- `PedalsMin = 3.0`
- `SpeedMin = 30.0`, `SpeedMax = 150.0`

---

### 2. Cruise Speed Controller (`SpeedFSM`)
Manages the internal cruise speed using inputs such as `Set`, `QuickAccel`, and `QuickDecel`.

**Behavior:**
- On `Set` or initial ON → CruiseSpeed = Speed
- `QuickAccel` → increase by `SpeedInc` (set to increments of 5.0)
- `QuickDecel` → decrease by `SpeedInc`
- Speed limited between `SpeedMin` and `SpeedMax`

---

### 3. Throttle Controller (`throttleController`)
Computes the actual throttle output depending on system state.

**Modes:**
- If CruiseState ≠ 2 → Throttle = Accel
- If CruiseState = 2 → Uses `regulateThrottle(isGoingOn, cruiseSpeed, speed)`

**Throttle Regulation:**
Implements a PI controller with saturation to maintain the cruise speed:
```c
Throttle = KP * error + KI * integral(error)
