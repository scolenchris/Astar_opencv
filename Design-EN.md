# I. Research Background

The A* (A-star) algorithm is a highly efficient algorithm widely used in the fields of graph search and path planning. Its primary advantage lies in its ability to find the shortest path across multiple domains, including artificial intelligence, game development, and robotic path planning. In these fields, the A* algorithm is not merely a theoretical construct but also a practical tool for solving real-world problems.

In game development, the A* algorithm provides a reliable solution for calculating the shortest path for characters or units within a game. The game map is abstracted as a graph, and the A* algorithm helps characters efficiently reach their target locations by avoiding obstacles and impassable areas. This not only enhances the gaming experience but also equips game developers with a powerful tool to create more interactive and realistic game worlds. In the field of robotics, the A* algorithm plays a similarly crucial role. Robots need to plan their movement paths in real-world environments, and the A* algorithm assists in this by considering obstacles in the environment and utilizing sensor data to plan paths that avoid obstacles and reach the target point via the shortest route. This makes robots more intelligent and efficient in executing tasks, thereby improving their adaptability and flexibility across various application scenarios.

Unlike the Dijkstra algorithm, the A* algorithm distinguishes itself by employing a heuristic function to evaluate the priority of each node, thereby finding the shortest path more efficiently. The heuristic function is typically based on an estimated distance from the current node to the goal, such as Euclidean distance or Manhattan distance. Additionally, the flexibility of the A* algorithm allows for the adjustment of the heuristic function according to specific problems, further enhancing search efficiency and adaptability. This makes the A\* algorithm one of the preferred choices for solving path planning problems in practical applications, providing reliable solutions for a wide range of scenarios.

## Content

- [I. Research Background](#i-research-background)
  - [Content](#content)
- [II. Design Rationale](#ii-design-rationale)
- [III. Process Discussion](#iii-process-discussion)
  - [1. Main Function Section](#1-main-function-section)
  - [2. onMouse Function](#2-onmouse-function)
  - [3. AStar4Way Function](#3-astar4way-function)
  - [4. FindAllNeighbors4Way Function](#4-findallneighbors4way-function)
  - [5. showRoute Function](#5-showroute-function)
  - [6. gridInit Function](#6-gridinit-function)
  - [7. generateObstacles Function](#7-generateobstacles-function)
  - [8. drawGrid Function](#8-drawgrid-function)
  - [9. GridCell::setCost4Way Function](#9-gridcellsetcost4way-function)
  - [10. AddAllRouteGridToVector Function](#10-addallroutegridtovector-function)
- [IV. Result Analysis](#iv-result-analysis)
  - [1. Phenomenon Description](#1-phenomenon-description)
  - [2. Algorithm Description](#2-algorithm-description)
  - [3. Functional Description](#3-functional-description)

# II. Design Rationale

There are numerous implementations of shortest path algorithms available, such as Dijkstra's algorithm, the Bellman-Ford algorithm, the Floyd-Warshall algorithm, and minimum spanning tree algorithms (Prim's and Kruskal's algorithms). However, the A* algorithm was ultimately chosen for implementation due to its combination of Dijkstra's algorithm and greedy search principles. By using a heuristic function to evaluate the priority of each node, the A* algorithm reduces the search space by selectively exploring the most promising nodes in the vicinity, thereby finding the shortest path more efficiently. The adaptability of the A* algorithm is another reason for selecting this approach. The heuristic function of the A* algorithm is adjustable, allowing it to be tailored to the specific characteristics of a given problem. This makes it highly suitable for different types of graphs and path planning problems, enabling it to flexibly address various application scenarios. Consequently, the A\* algorithm has found widespread use in fields such as artificial intelligence, game development, robotic path planning, and map navigation. Its successful application in numerous cases demonstrates the algorithm's versatility and effectiveness.

For the display framework, OpenCV was chosen. Initially, the first topic was selected, with the design idea being to process images using OpenCV, construct a graph model, and then apply the shortest path algorithm. However, due to limited proficiency in image processing code, extracting meaningful information from the images proved challenging. Subsequently, the second topic was chosen, and the OpenCV environment was configured. OpenCV's graphical rendering capabilities were used to build the display framework. The built-in mouse event handling in OpenCV is straightforward to set up, requiring only the configuration of callback function logic to accomplish basic tasks. The coordinate system of OpenCV's graphical window also facilitates the conversion of data structures and provides a foundation for future extensions. The IDE selected was Visual Studio 2022 Community Edition, which supports convenient breakpoint debugging, multi-source file linking and compilation, and powerful variable monitoring capabilities, enabling efficient problem identification and timely debugging and correction.

The overall solution is highly scalable, feature-complete, stable, and efficient in terms of algorithm performance. It has low maintenance costs, a clear and concise code structure, and achieves comprehensive functionality with relatively minimal code. Additionally, the solution offers a high degree of visualization, effectively showcasing the capabilities of the A\* algorithm.

The program's features include random map initialization (with obstacles), customizable start and end points via mouse clicks, pseudo-animation of the path generation process, customizable and switchable obstacles, a simple timing function, map size initialization, grid pixel settings (to accommodate screen resolution), and handling of pathfinding failures.

# III. Process Discussion

## 1. Main Function Section

The program begins by invoking the `gridInit` function, passing the `grids` and `grid_size` parameters to initialize the grid array. Subsequently, the `generateObstacles` function is called with the `grids` parameter to randomly generate obstacles. Following this, the `drawGrid` function is invoked with the `image`, `grid_size`, `cell_size`, and `grids` parameters to render the grid on the image, create a window, and bind the mouse event callback function.

The main loop continuously executes the following workflow:

- The `cv::waitKey` function is called to wait for user input, returning the ASCII code of the key pressed.
- If both `startGrid` and `endGrid` are defined and `isSuccess` is false, the `AStar4Way` function is called with the `startGrid`, `endGrid`, `grids`, and `grid_size` parameters to execute the A\* algorithm, and the result is assigned to the `isSuccess` variable.
- If `isSuccess` is true, the `AddAllRouteGridToVector` function is called with the `endGrid` and `route` parameters to store all grid points along the path in the `route` vector.
- Finally, the `showRoute` function is invoked with the `image`, `grid_size`, `cell_size`, `grids`, and `route` parameters to display the path.
- If the ESC key is pressed, the loop terminates.

The `cv::imshow` function is then called to display the image, followed by `cv::destroyAllWindows` to close all windows, concluding the program.

## 2. onMouse Function

This function is designed to customize the start point, end point, and obstacles, enabling the creation of custom maps and facilitating comparisons of algorithm performance under different scenarios.

A static variable `startPt` and `endPt` are defined to store the coordinates of the start and end points. The code determines whether the current operation is setting the start or end point by checking the value of `firstClick`. If `firstClick` is true, the program is in the start point setting phase; otherwise, it is in the end point setting phase.

On the first left mouse click, the program calculates the row and column of the grid corresponding to the mouse click position and toggles the grid's color. The `cv::rectangle` function is then used to fill the grid with the updated color on the image. The `firstClick` variable is set to false, indicating that the start point has been set, and the grid at the start point is marked as the starting grid.

On the second left mouse click, the program calculates the row and column of the grid corresponding to the mouse click position and toggles the grid's color. The `cv::rectangle` function is used again to update the grid's color on the image. The grid at the end point is marked as the destination grid, and the mouse click functionality is disabled by setting the callback function to `NULL` to prevent further mouse click operations.

If the right mouse button is clicked, the program calculates the row and column of the grid corresponding to the mouse click position and checks if the grid is already marked as an obstacle. If the grid is not an obstacle, the program fills the grid with a rectangle, marks it as an obstacle, and changes the rectangle's color. If the grid is already an obstacle, the program removes the obstacle status and reverts the rectangle's color to the default.

## 3. AStar4Way Function

Several variables are defined, including `openGrid` (representing the Open List, i.e., the set of nodes to be explored), `closeGrid` (representing the Close List, i.e., the set of nodes already explored), and `current` (representing the node currently being evaluated).

The starting node `startGrid` is added to the Open List.

The loop continues until the Open List is empty:

- The node with the smallest `FCost` in the Open List is selected as the `current` node. If multiple nodes have the same `FCost`, the node with the smallest `HCost` is chosen as `current`.
- The `current` node is removed from the Open List and added to the Close List.
- If `current` is the target node `endGrid`, the pathfinding is successful, and the function returns `true`.
- The neighbors of `current` are retrieved using the `FindAllNeighbors4Way` function. For each neighbor:
  - If the neighbor is a wall or already in the Close List or Open List, it is skipped.
  - Otherwise, the neighbor's parent node is set to `current`, and its cost is calculated using the `setCost4Way` function. The neighbor is then added to the Open List.
- If the Open List becomes empty, the pathfinding fails, and the function returns `false`.

## 4. FindAllNeighbors4Way Function

This function is used to find all four-connected neighbor nodes of the current node, i.e., the nodes that can be reached in the four cardinal directions, aiding the implementation of the A\* algorithm.

An empty neighbor node set `neighbors` is defined, which will be returned at the end.

The index of the current node `current` is obtained, representing its position in the 2D grid (`currentX` and `currentY`).

For each of the four directions:

- If the current node is not at the top edge (i.e., `currentY > 0`), the top neighbor node is added to the neighbor set. This is done by calculating the index of the top neighbor in the 1D array, retrieving the neighbor's pointer using the `getGridNum` function, and adding it to the neighbor set.
- If the current node is not at the bottom edge (i.e., `currentY < grid_size - 1`), the bottom neighbor node is added to the neighbor set using the same method.
- If the current node is not at the left edge (i.e., `currentX > 0`), the left neighbor node is added to the neighbor set using the same method.
- If the current node is not at the right edge (i.e., `currentX < grid_size - 1`), the right neighbor node is added to the neighbor set using the same method.

Finally, the neighbor set is returned.

## 5. showRoute Function

This function is designed to display the computed path. It requires the following parameters: a reference to a `cv::Mat` object `img`, which represents the image to be modified; `grid_size` and `cell_size`, which denote the size of the grid and the size of each cell, respectively; a vector of `GridCell` objects `grids`, which represents the entire grid map; and a vector of pointers to `GridCell` objects `route`, which represents the set of points along the path.

First, a range-based `for` loop is used to iterate through each element in the `route` vector. For grids that are neither the start nor the end point, the `setRoute()` method is called to mark them. The drawing process is similar to the `drawGrid` function, where the `cv::rectangle` method is employed. The position and size of the rectangles are calculated based on the grid coordinates and cell size. Finally, the image is displayed using `cv::imshow`, and `cv::waitKey` is used to maintain the display, simulating the dynamic generation of the path.

## 6. gridInit Function

This function initializes the entire grid map.

The `std::fill` function is first used to initialize each element in the `grids` vector with a `GridCell()` object. This creates `grid_size * grid_size` `GridCell` objects in the `grids` vector, all in the same initial state, facilitating subsequent operations.

A nested loop is then used to traverse the entire grid. For each grid cell, the `getGridNum` function is called to obtain its index in the one-dimensional vector, and the corresponding `GridCell` object is accessed using this index. The `setIndex` method is called on this `GridCell` object to set its index to the current grid's 2D coordinates `(i, j)`. Since the index values are related to the constructed vector, they need to be initialized separately, while other attributes are handled directly by the class constructor.

## 7. generateObstacles Function

This function is used to randomly generate obstacles, effectively creating a random map.

A nested loop is used to traverse the entire grid map. For each grid cell, a random number between 0 and 99 is generated using `rand() % 100`. If this random number is less than 25, there is approximately a 25% probability that the current grid cell will be marked as an obstacle. This is achieved by calling the `setBlock(true)` method.

## 8. drawGrid Function

This function renders the initialized grid and adds dividing lines for clarity.

A nested loop is used to traverse the entire grid. Depending on the type of each grid cell, the `cv::rectangle` function is used to draw rectangles filled with different colors:

- If the grid cell is an obstacle, it is filled with a deep purple-blue color.
- If the grid cell is the end point, it is filled with green.
- If the grid cell is the start point, it is filled with red.
- If the grid cell is part of the path, it is filled with brown.

Grid lines are then drawn on the image using a loop, with black color and a line width of 2. Vertical lines are defined by `cv::Point(i * cell_size, 0)` and `cv::Point(i * cell_size, image_size)`, while horizontal lines are defined by `cv::Point(0, i * cell_size)` and `cv::Point(image_size, i * cell_size)`.

## 9. GridCell::setCost4Way Function

This function, part of the `GridCell` class, is used to set the cost of a grid cell, employing the Manhattan distance for calculation.

If the current grid cell is the starting cell, its `GCost` is set to 0. Otherwise, its `GCost` is set to the `GCost` of its parent node plus 1. The `getIndex()` method is then used to obtain the coordinates of the target grid cell, and the Manhattan distance from the current grid cell to the target grid cell is calculated and assigned to `HCost`. Finally, the `FCost` is computed by summing the `GCost` and `HCost`.

## 10. AddAllRouteGridToVector Function

This function is responsible for storing the computed path points in a vector, which is later used to represent and display the path.

- If the current grid cell `grid` has a parent node (i.e., it is not the starting point), the following operations are performed:
  - The current grid cell `grid` is added to the result vector `result`.
  - A recursive call to `AddAllRouteGridToVector` is made to continue processing the parent node, effectively backtracking up the path until a node with no parent (i.e., the starting point) is reached.
- If the current grid cell has no parent node (i.e., it is the starting point), the function simply returns (exits).

# IV. Result Analysis

To make the timing function more noticeable, the grid size was set to 64x64, resulting in a pathfinding time of approximately 10 milliseconds. Smaller grid sizes might yield times less than 1 millisecond, making the phenomenon less observable.

## 1. Phenomenon Description

First, a simple loop maze was manually generated to test whether the pathfinding could succeed. The result is shown in the following figure:
![image](https://github.com/user-attachments/assets/fc9291ba-a59f-4c76-8ce7-8c94bf54070b)

![Loop Maze Test](image_link_placeholder)

As can be seen, the program successfully found the endpoint and displayed the path. The pseudo-code for the A\* algorithm implemented in this program is as follows:

- **Open Queue**: A queue of nodes to be evaluated.
- **Closed Queue**: A queue of nodes that have already been evaluated.
- Add the starting node to the Open Queue.

While the Open Queue is not empty, loop:

- **Current Node**: Select the node with the smallest F Cost in the Open Queue. If there are multiple nodes with the same F Cost, choose the one with the smallest H Cost. If they are still the same, select any.
- Remove the Current Node from the Open Queue.
- Add the Current Node to the Closed Queue.
- If the Current Node is the target node:
  - Return: Pathfinding successful.
- For each neighbor of the Current Node:
  - If the neighbor is impassable or already in the Closed Queue:
    - Skip this neighbor.
  - If the neighbor is not in the Open Queue or the new path to the neighbor has a lower G Cost:
    - Set the Cost of the neighbor.
    - Set the parent of the neighbor to the Current Node.
    - If the neighbor is not in the Open Queue:
      - Add the neighbor to the Open Queue.
- Return: Pathfinding failed.

The program calculates the `fCost`, `gCost`, and `hCost` for each node along the path. Although the program does not include a visual display for these costs, they can be observed in the debugging window, as shown below:

![image](https://github.com/user-attachments/assets/efacc9eb-16a5-4648-a042-d67e18110489)

## 2. Algorithm Description

- **fCost**: The estimated total cost from the start node to the goal node via node `n`.
- **gCost**: The actual cost from the start node to node `n`.
- **hCost**: The estimated cost from node `n` to the goal node.

First, the `gCost` is calculated. For example, if moving horizontally from node A to a neighboring cell, the single-step movement cost is 10, so `g = 10`.

Next, the heuristic cost `h` is estimated. This estimation ignores any obstacles in the remaining path and calculates the cumulative cost using the Manhattan distance. For instance, moving 3 steps to the right and 1 step upward results in `h = 40`. Therefore, the total movement cost from node A to node I is `f = g + h = 50`. This process is repeated for all nodes, and the node with the smallest `fCost` is added to the Closed List. Notably, the `hCost` and `gCost` vary depending on the direction of movement. For example, moving toward the goal generally results in a lower cost, making the `fCost` more unique.

The following diagram from [Red Blob Games](https://www.redblobgames.com/pathfinding/a-star/introduction.html) provides a visual explanation:

![image](https://github.com/user-attachments/assets/cc044a4d-bc49-472f-869c-590d24e68ccc)


The arrow direction indicates the movement direction. Although this diagram reflects a reverse path, the principle is similar. The following figure better illustrates this process:

![image](https://github.com/user-attachments/assets/04219e2d-c92a-44fb-8922-c69e9d540361)

## 3. Functional Description

**(1) Custom Map and Start/End Points**

The map can be customized by clicking the mouse to set the start and end points. For example, the top-left corner of the map can be modified as shown below:

![image](https://github.com/user-attachments/assets/d7c1bea4-7531-4ec8-a2db-c01db2cc9035)

![image](https://github.com/user-attachments/assets/3a4383c1-8c25-4343-8272-16214196cba6)

The start and end points can be determined by mouse clicks:

![image](https://github.com/user-attachments/assets/0defe416-0571-4057-8583-960953452555)

**(2) Map Size Definition**

The map size can be adjusted by modifying the following parameter:

![image](https://github.com/user-attachments/assets/77833504-1d8b-4e2e-8f62-c5215e6e968e)

This allows for changes in map size while maintaining normal functionality:

![image](https://github.com/user-attachments/assets/e9c223be-40cd-42c7-9da4-15f2c7856a7e)

**(3) Time Display**

The program includes a timing function to display the pathfinding duration:

![image](https://github.com/user-attachments/assets/9f3c35b0-32b2-4d0e-909c-a8c16a49141b)

**(4) Pathfinding Failure Handling**
![image](https://github.com/user-attachments/assets/f04c36d1-2fd9-4b7e-b746-c8eba0db8a24)

The program handles cases where pathfinding fails, ensuring robustness in various scenarios.
