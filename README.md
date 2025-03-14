# A\* Algorithm Visualization Based on OpenCV Drawing Framework

![image](https://github.com/scolenchris/Astar_opencv/assets/128346155/acc6ae57-cbdb-48a8-b2f7-d3d20e0fba79)

- [中文版](./README_CN.md)

## Project Overview

This project implements the visualization of the A\* algorithm for maze pathfinding using the OpenCV graphics library. Users can randomly initialize a map (including obstacles), customize the start and end points, and observe the path generation process in real-time. The program also supports obstacle customization, map size initialization, grid pixel settings, and more, making it adaptable to different screen resolutions. The A\* algorithm combines the ideas of Dijkstra's algorithm and greedy search, using a heuristic function to evaluate the priority of each node, thereby efficiently finding the shortest path.

## Function Design and Result Analysis

- Due to space limitations，For more detail,please click following:

- [English Version](./Design-EN.md)

- [中文版](./Design-CN.md)

## Content

- [A\* Algorithm Visualization Based on OpenCV Drawing Framework](#a-algorithm-visualization-based-on-opencv-drawing-framework)
  - [Project Overview](#project-overview)
  - [Function Design and Result Analysis](#function-design-and-result-analysis)
  - [Content](#content)
  - [Features](#features)
  - [Environment Setup](#environment-setup)
  - [Usage](#usage)
  - [Algorithm Selection](#algorithm-selection)
  - [Technical Details](#technical-details)
  - [Project Advantages](#project-advantages)

## Features

1. **Random Map Initialization**: The program can randomly generate a map with obstacles.
2. **Custom Start and End Points**: Users can set the start and end points by left-clicking on the map.
3. **Obstacle Customization**: Users can add or remove obstacles by right-clicking on the map.
4. **Path Generation Animation**: The program displays the path generation process of the A\* algorithm in a pseudo-animation format.
5. **Timing Function**: The program provides a simple timing function to record the time taken for pathfinding.
6. **Map Size Initialization**: Users can initialize the map size according to their needs.
7. **Grid Pixel Settings**: Supports adjusting grid pixel size to fit different screen resolutions.
8. **Pathfinding Failure Handling**: The program handles cases where no path is found and notifies the user.

## Environment Setup

- **IDE**: Visual Studio 2022 Community Edition
- **Dependencies**: OpenCV
- **Programming Language**: C++

## Usage

1. **Set Start and End Points**: Use the left mouse button to click anywhere on the map to set the start point, and click again to set the end point.
2. **Add/Remove Obstacles**: Use the right mouse button to click on empty spaces to add obstacles, or click on existing obstacles to remove them.
3. **Run the Program**: After setting the start and end points, the program will automatically start pathfinding and display the path generation process in an animated format.

## Algorithm Selection

The A\* algorithm combines the ideas of Dijkstra's algorithm and greedy search, using a heuristic function to evaluate the priority of each node, thereby reducing the search space and efficiently finding the shortest path. The heuristic function of the A\* algorithm is adjustable, allowing it to be optimized for specific problem characteristics, making it suitable for various applications such as artificial intelligence, game development, and robot path planning.

## Technical Details

- **OpenCV Graphics Library**: Used for graphics rendering and mouse event handling. OpenCV provides simple mouse event callback functions for user interaction.
- **Visual Studio 2022**: Offers powerful debugging features such as breakpoint debugging and variable monitoring, enabling efficient problem identification and resolution.
- **Code Structure**: The code is clean and concise, with comprehensive and stable functionality, low maintenance costs, and high scalability.

## Project Advantages

- **High Visualization**: Provides an intuitive display of the A\* algorithm's pathfinding process.
- **High Extensibility**: The clear code structure makes it easy to add and modify features in the future.
- **Efficient and Stable**: The A\* algorithm ensures efficiency while stably finding the shortest path.
