# ME-507-Mecha16 Ice Cold Beer Project

## Table of Contents
- [Project Overview](#projectoverview)
- [Major Hardware](#major-hardware)
  - [PCB](#pcb)
  - [Mechanical Design](#mechanical-design)
  - [Stepper Motors](#stepper-motors)
  - [Distance Sensor](#distance-sensor)
  - [LCD](#lcd)
  - [Switches](#switches)
  - [Limit Switches](#limit-switches)
- [Software](#software)
  - [Main](#main)
  - [LCD Driver](#lcd-driver)
- [Modeling](#modeling)
- [Improvements](#improvements)
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

### PCB

### Mechanical Design
[Back to top](#Table-of-Contents)

### Stepper Motors
[Back to top](#Table-of-Contents)

### Distance Sensor
[Back to top](#Table-of-Contents)

### LCD
[Back to top](#Table-of-Contents)

### Switches
[Back to top](#Table-of-Contents)

### Limit Switches
[Back to top](#Table-of-Contents)

## Software
[Back to top](#Table-of-Contents)

### Main

### LCD Driver
[Back to top](#Table-of-Contents)

## Modeling
[Back to top](#Table-of-Contents)

## Improvements
[Back to top](#Table-of-Contents)

## Reflection
[Back to top](#Table-of-Contents)
