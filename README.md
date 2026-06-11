# ME-507-MECHA06

# ME-405-Mecha16 Term Project

## Table of Contents
- [Project Overview](#projectoverview)
- [Hardware](#hardware)
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

This repository contains the ME-405 term project by Ethan Gray and Wyatt Eberhart. The objective of this project was to develop and implement a control system for a differential-drive robot, Romi, using MicroPython. Romi was programmed to autonomously navigate a predefined course (depicted in Figure 1) by utilizing three primary sensors: an inertial measurement unit (IMU), line sensors, and bump sensors. These sensors were integrated with the Romi chassis kit and combined with Pololu motors and a Pololu power distribution board. Figure 2 shows the final build of Romi.

The system was controlled using an STM32 Nucleo-L476RG development board, which served as the main processing unit. Task execution was managed through a real-time scheduler, ensuring periodic execution with designated priorities. Within these scheduled tasks, a finite state machine (FSM) was implemented to enable Romi to know what section of the track it was on and react accordingly.


<img height="280" alt="Screenshot 2025-03-16 at 12 55 04 PM" src="https://github.com/user-attachments/assets/97ac74ea-d0b5-4674-859b-4bc7075b9cf2" />
<img height="280" alt="IMG_5718" src="https://github.com/user-attachments/assets/c376aa85-b766-441c-93ef-0afb0c2265a2" />

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
Figure 1. Course Layout
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
Figure 2. Final Build of Romi

[![Watch the video](https://img.youtube.com/vi/zJc4XDnnLkc/maxresdefault.jpg)](https://www.youtube.com/shorts/zJc4XDnnLkc)
<p align="center">
  Click Thumbnail above to view demonstration
</p>

## Hardware
[Back to top](#Table-of-Contents)

### Romi Chassis and Components

The core components of Romi, sourced from Pololu, include the motors (Figure 5), encoders (Figure 5), power distribution board (Figure 3), and chassis (Figure 4). The motors are coupled with a 120:1 gearbox, providing high torque and precise control. Each encoder has a resolution of 12 ticks per motor shaft revolution, resulting in 1440 encoder ticks per full wheel rotation. Romi is powered by six AA batteries, which are regulated through the power distribution board. The motors receive power directly from the distribution board and are controlled through its integrated circuitry.


  <img height="240" alt="[Screenshot 2025-03-16 160153" src="https://github.com/user-attachments/assets/8af7760e-e74b-4c70-9e59-c029caaecfe0" />
  <img height="240" alt="[Screenshot 2025-03-16 160208" src="https://github.com/user-attachments/assets/0ec7f4de-23a0-4646-b721-331e287d3c96" />
  <img height="240" alt="[Screenshot 2025-03-16 160101" src="https://github.com/user-attachments/assets/f1b07fd9-ac19-4c26-b4b9-96e414122c30" />

&nbsp;&nbsp;
Figure 3. Power Distribution Board
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
Figure 4. Romi Chassis
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
Figure 5. Motor and Encoder Pair



### Microcontroller
[Back to top](#Table-of-Contents)

The STM32 Nucleo-L476RG microcontroller served as the central processing unit for Romi and was provided by the professor. Acting as Romi’s "brain," it processed sensor data, interpreted the readings, and executed control algorithms to drive the motors. This allowed Romi to navigate the course effectively based on real-time feedback. Figure 6 provides a visual representation of the Nucleo board. Further documentation on the Nucleo-L476RG can be found [here](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf). Further documentation on the MicroPython can be found [here](https://docs.micropython.org/en/latest/library/pyb.html)

<p align="center">
  <img width="300" alt="[Screenshot 2025-03-16 142309" src="https://github.com/user-attachments/assets/ad4143ad-f2fc-4ce5-9881-01eb9068ed2d" />
</p>
<p align="center">
  Figure 6. Nucleo L476RG
</p>
