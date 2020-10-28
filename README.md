# SwitchMachine #
The `SwitchMachine` class is used to control a single [KATO UNITRACK](https://www.unitrack-kato.com/ "KATO UNITRACK") solenoid-based switch machine through a motor-driver chip.

## Examples ##

The `SwitchMachine` library includes an example sketch, `SwitchMachine_Test`.  This example drives a single UNITRACK turnout, connected to three GPIO pins of an Arduino through a motor driver chip such as an L293D.  A YouTube of this sketch in action can be seen [here](https://www.youtube.com/watch?v=hdqmNSTQotc)

## Dependencies ##

The `SwitchMachine` library requires installation of the `StateMachine` library ([https://github.com/twrackers/StateMachine-library](https://github.com/twrackers/StateMachine-library)).

The `SwitchMachine_Test` sketch in the `examples` directory also requires the `Pulser` library ([https://github.com/twrackers/Pulser-library](https://github.com/twrackers/Pulser-library)).

## Installation ##

Instructions for installing the *SwitchMachine* class can be found in file `INSTALL.md` in this repository at [https://github.com/twrackers/SwitchMachine-library/blob/main/INSTALL.md](https://github.com/twrackers/SwitchMachine-library/blob/main/INSTALL.md)