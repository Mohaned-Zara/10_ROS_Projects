# ROS Simple Publisher & Subscriber

A simple ROS1 project demonstrating **Publisher and Subscriber communication** using a **custom ROS message**.

## 🎥 Demo

![ROS Simple Publisher Subscriber Demo](demo.gif)

## 📌 Project Overview

This project demonstrates how two ROS nodes communicate through a ROS topic:

- **Publisher (`talker.py`)**: publishes robot data.
- **Subscriber (`listener.py`)**: receives and displays the published data.
- **Custom Message (`RobotData.msg`)**: defines the data structure exchanged between the two nodes.

The publisher sends the following information:

```text
name
battery_level
serial_num
```

The data is published on:

```text
/chatter
```

## 🧩 Project Structure

```text
1_simple_pub_sub/
├── src/
│   ├── CMakeLists.txt
│   └── sps_pkg/
│       ├── CMakeLists.txt
│       ├── package.xml
│       ├── msg/
│       │   └── RobotData.msg
│       ├── scripts/
│       │   ├── talker.py
│       │   └── listener.py
│       └── src/
│           └── talker.cpp
└── README.md
```

## ⚙️ Requirements

- ROS1 Noetic
- Ubuntu 20.04
- Python 3
- Catkin

## 🚀 How to Run

Build the workspace:

```bash
catkin_make
```

Source the workspace:

```bash
source devel/setup.bash
```

Run the publisher:

```bash
rosrun sps_pkg talker.py
```

In another terminal, source the workspace again:

```bash
source devel/setup.bash
```

Then run the subscriber:

```bash
rosrun sps_pkg listener.py
```

## 📡 Communication

The communication flow is:

```text
talker.py
    ↓
/chatter
    ↓
listener.py
```

The `/chatter` topic uses the custom message:

```text
sps_pkg/RobotData
```

## 🎯 What I Learned

This project helped me practice:

- ROS Nodes
- ROS Topics
- Publishers and Subscribers
- Custom ROS Messages
- `message_generation`
- `message_runtime`
- Catkin workspace and package structure
- Running Python ROS nodes

## 🛠️ Technologies

- ROS1 Noetic
- Python
- C++
- CMake
- Catkin
- Ubuntu 20.04
