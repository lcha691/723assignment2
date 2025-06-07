# Cruise Controller
COMPSYS 723 Assignment 2: Implementation of a basic cruise controller in Esterel\
***Authors: Connor Dunn (cdun954), Lachlan Chan (lcha691)***

*This project was created for an assignment at The University of Auckland*

## Project Overview
This Project is built in Esterel, a synchronous programming language.\
The Cruise Controller is split into three submodules, a state controller, a cruise speed controller, and a throttle controller. These are executed parallel in one parent module.

## Cruise State Controller
### Description
The Cruise State Controller manages what state the controller should be in depending on inputs and thresholds below. It will move between four states; Off (1), On (2), Standby (3), and Disabled (4). Depending on which state the cruise controller is in, the outputs of the Throttle Controller and Speed Controller will change how they retrieve their values.
### Inputs
| Type| Name | Description|
| --- | --- | --- |
| Pure | on | Enable the cruise control |
| Pure | off | Disable the cruise control |
| Pure | resume | Resume the cruise control |
| Float | brake | Senses if the brake is pressed |
| Float | speed | Speed of the car |
| Float | accel | Senses if the accelerator is on |
### Outputs 
| Type| Name | Description|
| --- | --- | --- |
| Int  | cruiseState | Cruise Control State |
### Thresholds
| Type| Name | Value |
| --- | --- | --- |
| Float | PedalsMin | 3.0 |
| Float | SpeedMin | 30.0 |
| Float | SpeedMax | 150.0 | 
### Transition Logic
![alt text](image.png)
<br/>

<br/>

## Cruise Speed Controller
### Description
Cruise Speed Control manages the "Cruise Speed" of the car, based on external inputs and state of the cruise control system. The current speed when the system is first turned on or the cruise speed is set, and can be modified incrementally. The Cruise Speed is kept between two determined thresholds (kmph).
### Thresholds
| Type| Name | Value |
| --- | --- | --- |
| Float | speedMin | 30.0 |
| Float | speedMax | 150.0 |
| Float | speedInc | 10.0 | 
### Inputs
| Type| Name | Description|
| --- | --- | --- |
| Pure | sSet | Button Sets Cruise Speed |
| Pure | sQuickAccel | Incrememnts Cruise Speed |
| Pure | sQuickDecel | Decrements Cruise Speed |
| Float | sSpeed | Current Car Speed |
| Int  | sCruiseState | Cruise Control State |
### Outputs 
| Type| Name | Description|
| --- | --- | --- |
| Float | sCruiseSpeed | Speed set by the Cruise Control |
### Control Logic
| Input| Output |
| --- | --- |
| Cruise Control is Off | `CruiseSpeed = 0` |
| Cruise Control is going on | `CruiseSpeed = Speed` |
| Cruise Control is set | `CruiseSpeed = Speed` |
| Quick Accel applied | `CruiseSpeed += SpeedInc` |
| Quick Decel applied | `CruiseSpeed -= SpeedInc` |
<br/>

## Throttle Controller
### Description
The Throttle Controller physically operates the speed of the car, either directly with the accelerator, or with the throttle command given by the implemented cruise regulation functions (PI Controller). The function needs to know whether the Cruise Control system is on, so it can choose how the car is controlled. It also needs to know the state of the accelerator pedal and both, the car's current speed and cruise speed.

### Inputs:
| Type| Name | Description|
| --- | --- | --- |
| Float | tAccel | Accelerator Pedal Sensor |
| Float | tCruiseSpeed | Cruise Speed Value |
| Float | tSpeed | Car Speed Sensor |
| Int  | tCruiseState | Cruise Control State |
### Outputs:
| Type| Name | Description|
| --- | --- | --- |
| Float | throttleCmd | Throttle Output |
### Control Logic:
| Input| Output |
| --- | --- |
| Cruise Control is Off | `Throttle = Accelerator Sensor` |
| Cruise Control is On | `Throttle Command = Regulated Output` |

## How To Run Code:
Must be on a Linux system!\
To run through the terminal, the code must be located locally, and the following commands must be run from the appropriate project directory:\
`make CruiseControl.xes`\
`./CruiseControl.xes`

***Credit to the original Authors of this README: Harrison Warahi, Cassandra D'Souza***