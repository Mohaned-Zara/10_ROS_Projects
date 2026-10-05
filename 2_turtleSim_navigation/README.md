# TurtleSim Navigation

A ROS1 project built with **C++** and **TurtleSim** to practice robot navigation, ROS topics, parameters, services, callbacks, and launch files.

## Project Overview

This project demonstrates a simple navigation system using two turtles in TurtleSim:

- **Turtle1** navigates to a predefined goal position `(x, y)`.
- **Turtle2** is spawned automatically at startup.
- Turtle2 uses Turtle1's current position as its moving target and follows it.
- Turtle2's pen is configured to draw in red.
- When Turtle2 reaches Turtle1, the simulation drawing is cleared.

The project focuses on understanding how different ROS concepts work together in a practical application.

## ROS Architecture

```text
                       /turtle1/pose
                             |
                             v
                    +-------------------+
                    | turtle_navigation |
                    +-------------------+
                       |             |
                       |             |
                       v             v
               /turtle1/cmd_vel  /turtle2/cmd_vel
                                     ^
                                     |
                                /turtle2/pose
```

The node also communicates with TurtleSim through several ROS services:

```text
turtle_navigation
       |
       +----> /spawn
       |
       +----> /turtle2/set_pen
       |
       +----> /clear
```

## Features

### Turtle1 Navigation

Turtle1 subscribes to:

```text
/turtle1/pose
```

and publishes velocity commands to:

```text
/turtle1/cmd_vel
```

The navigation algorithm calculates:

- Distance to the goal
- Target heading using `atan2()`
- Angular error
- Linear and angular velocity using simple proportional control

The goal position is provided through ROS parameters:

```text
/turtle_navigation/goal_x
/turtle_navigation/goal_y
```

### Automatic Turtle2 Spawn

Turtle2 is created automatically using the TurtleSim service:

```text
/spawn
```

Current starting position:

```text
x = 1
y = 1
theta = 0
```

### Turtle2 Tracking

Turtle2 subscribes to:

```text
/turtle2/pose
```

while using Turtle1's pose as its target.

Its movement is controlled through:

```text
/turtle2/cmd_vel
```

This creates a simple leader-follower behavior:

```text
Turtle1
   ↓
Current Position
   ↓
Navigation Node
   ↓
Turtle2
```

### Red Pen

Turtle2's drawing color is configured through:

```text
/turtle2/set_pen
```

The current pen configuration uses a red color and a defined pen width.

### Clear Service

When Turtle2 reaches its target, the node calls:

```text
/clear
```

to clear the TurtleSim drawing.

> **Note:** `/clear` clears the entire TurtleSim canvas, so it removes the trajectories of both turtles, not Turtle2's trajectory alone.

## Parameters

The navigation goal is configured in the launch file:

```xml
<param name="goal_x" value="10"/>
<param name="goal_y" value="10"/>
```

These are private parameters of the `turtle_navigation` node and are accessed in C++ using:

```cpp
ros::NodeHandle pnh("~");
```

## Launch File

The launch file starts both the TurtleSim node and the navigation node.

Example:

```xml
<launch>

    <node name="myturtle1"
          pkg="turtlesim"
          type="turtlesim_node"/>

    <node name="turtle_navigation"
          pkg="tn_pkg"
          type="turtle_navigation">

        <param name="goal_x" value="10"/>
        <param name="goal_y" value="10"/>

    </node>

</launch>
```

This allows the complete project to be started with one command instead of launching each node separately.

## Package

Package name:

```text
tn_pkg
```

Main executable:

```text
turtle_navigation
```

## Dependencies

The project uses the following ROS packages:

```text
roscpp
rospy
geometry_msgs
turtlesim
std_srvs
```

## Build

From the workspace directory:

```bash
cd ~/Desktop/10_ROS_PROJECT/2_turtleSim_navigation
catkin_make
source devel/setup.bash
```

## Run

Start the complete simulation using:

```bash
roslaunch tn_pkg navigation.launch
```

## Useful ROS Commands

Check running nodes:

```bash
rosnode list
```

Check active topics:

```bash
rostopic list
```

Inspect Turtle1 pose:

```bash
rostopic echo /turtle1/pose
```

Inspect Turtle2 pose:

```bash
rostopic echo /turtle2/pose
```

Check parameters:

```bash
rosparam get /turtle_navigation/goal_x
rosparam get /turtle_navigation/goal_y
```

Check available services:

```bash
rosservice list
```

Visualize the ROS communication graph:

```bash
rqt_graph
```

## Learning Objectives

This project was developed to practice the following ROS1 concepts:

- ROS Nodes
- Publishers and Subscribers
- Topics
- `geometry_msgs/Twist`
- `turtlesim/Pose`
- ROS Parameters
- Private Parameters
- Services and Service Clients
- `turtlesim/Spawn`
- `turtlesim/SetPen`
- `std_srvs/Empty`
- Callbacks
- Launch Files
- Basic proportional control
- Multi-topic robot interaction

## Project Status

**Completed**

Current implementation includes:

- Turtle1 goal navigation
- ROS parameters for the navigation goal
- Launch file
- Automatic Turtle2 spawning
- Turtle2 pose tracking
- Turtle2 following Turtle1
- Red pen configuration
- Clear service on Turtle2 arrival

Future improvements may include launch arguments, better service result checking, and more advanced navigation behavior.
