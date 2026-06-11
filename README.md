# ME-507-Mecha16 Ice Cold Beer Project

## Table of Contents
- [Project Overview](#projectoverview)
- [Major Hardware](#major-hardware)
  - [Romi Chassis and Components](#romi-chassis-and-components)
  - [Microcontroller](#microcontroller)
  - [Sensors](#sensors)
  - [Additional Components](#additional-components)
  - [Wiring Diagram](#wiring-diagram)
- [Software](#software)
  - [Source Code](#source-code)
  - [Hardware Drivers](#hardware-drivers)
  - [Task Diagram and FSM](#task-diagram-and-fsm)
  - [Gain Detirmination](#gain-determination)
- [Control Therory](#control-theory)
- [Getting Started](#getting-started)
- [Reflections](#reflections)

## Project Overview
[Back to top](#Table-of-Contents)

This repository contains the ME-507 term project by Wyatt Eberhart and Max Soury. The goal of the project was to design, fabricate, and test a custom printed circuit board for an embedded control system based on the STM32F411CE6U microcontroller.

The project was inspired by the classic Ice Cold Beer arcade game, where the player controls a bar to guide a ball upward while avoiding holes. In this version, the system uses two stepper motors to control the motion of the bar, allowing the user to adjust each side independently. A distance sensor, two limit switches, two user switches, and an LCD display were integrated into the system to allow for a control system and a user controlled mode.

The custom PCB served as the central hardware interface for the project. It connected the STM32 microcontroller to the motors, sensors, switches, and display, creating a clean and viable control platform. The STM32 reads the user switches and sensor inputs, processes the game-control logic, and commands the stepper motors to move the bar accordingly.

Overall, this project demonstrates the development of a complete embedded mechatronic system, combining PCB design, microcontroller programming, stepper motor control, sensor integration, and a user-interface to recreate a game. 

<p align="center">
  <img width="545" height="726" alt="R" src="https://github.com/user-attachments/assets/c4f8bfcb-f1fc-443e-87b6-743634f9f17b" />
</p>
<p align="center">
  Figure 1. Ice Cold Beer Game
</p>

## Major Hardware
[Back to top](#Table-of-Contents)

### Romi Chassis and Components

The core components of Romi, sourced from Pololu, include the motors (Figure 5), encoders (Figure 5), power distribution board (Figure 3), and chassis (Figure 4). The motors are coupled with a 120:1 gearbox, providing high torque and precise control. Each encoder has a resolution of 12 ticks per motor shaft revolution, resulting in 1440 encoder ticks per full wheel rotation. Romi is powered by six AA batteries, which are regulated through the power distribution board. The motors receive power directly from the distribution board and are controlled through its integrated circuitry.


  <img height="240" alt="[Screenshot 2025-03-16 160153" src="https://github.com/user-attachments/assets/8af7760e-e74b-4c70-9e59-c029caaecfe0" />
  <img height="240" alt="[Screenshot 2025-03-16 160208" src="https://github.com/user-attachments/assets/0ec7f4de-23a0-4646-b721-331e287d3c96" />
  <img height="240" alt="[Screenshot 2025-03-16 160101" src="https://github.com/user-attachments/assets/f1b07fd9-ac19-4c26-b4b9-96e414122c30" />
