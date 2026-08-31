# AGENTS.md

## 1. Project Overview

Project name: `ros2-navigation-planning-control`

Repository:
- Local WSL path: `/home/chd/ros2-navigation-planning-control`
- GitHub: `songa1626-eng/ros2-navigation-planning-control`
- Main branch: `main`

Project goal:

Build a resume-quality **ROS2/Nav2 mobile robot planning and control system** in C++, starting from simulation and gradually adding self-implemented planning/control modules.

The project is not intended to be a simple ROS2 demo. The final result should be something that can be explained in an internship interview, reproduced from the repository, quantitatively evaluated, and extended later to more advanced planning/control methods.

## 2. User Background and Learning Goal

The user is learning modern C++ for robotics and has already:
- learned basic C++ syntax, classes, inheritance, references, pointers, smart pointers, STL, templates/generic programming;
- studied an A* implementation from an existing path-planning library;
- learned basic Linux/WSL workflow;
- learned basic CMake, multi-file C++ compilation, `add_library`, `add_executable`;
- learned basic GDB debugging;
- learned Linux permissions, processes, PATH, `find`, `grep`, pipes;
- created and connected this Git repository to GitHub.

The user is **not a C++ beginner from zero**, but still needs explanations of unfamiliar engineering concepts.

Main career direction:

**Robot Motion Planning / Planning & Control**

Long-term extensions may include:
- trajectory optimization;
- LQR / MPC;
- autonomous driving or UAV planning;
- Robot Learning;
- World Model / VLA integration.

The project should prioritize strong robotics engineering fundamentals before chasing frontier AI topics.

## 3. Current Project Status

Completed:
- Git installed and configured in WSL.
- GitHub repository created.
- Local Git repository initialized.
- Main branch renamed to `main`.
- `README.md` created.
- `.gitignore` created.
- Initial commit completed.
- GitHub remote `origin` configured.
- First push to GitHub completed successfully.
- Repository-specific Git HTTP setting uses:
  ```bash
  git config http.version HTTP/1.1
  ```
  This was set because GitHub HTTPS over HTTP/2 was unstable in the WSL network environment.

Current repository is still at the very beginning.

Next immediate task:

**Create the first clean C++/CMake project skeleton inside this repository.**

Do not jump directly into ROS2/Nav2 implementation before the basic project structure is clean and buildable.

## 4. Target System Architecture

The intended system is:

```text
Map / Costmap
      ↓
Global Planner
Dijkstra / A* / Theta*
(later Hybrid A*)
      ↓
nav_msgs/Path
      ↓
Controller
Pure Pursuit
(later LQR / MPC)
      ↓
cmd_vel
      ↓
TurtleBot3
      ↓
Gazebo / RViz
```

Final integration target:

```text
RViz Goal
   ↓
Nav2
   ↓
Custom Planner Plugin
   ↓
Self-written Planning Core
   ↓
Path
   ↓
Controller
   ↓
TurtleBot3 simulation
```

## 5. Planned Repository Architecture

The repository should gradually evolve toward:

```text
ros2-navigation-planning-control/
├── README.md
├── AGENTS.md
├── .gitignore
├── docs/
├── planning_core/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── planning_core/
│   ├── src/
│   └── tests/
├── ros2_ws/
│   └── src/
│       ├── my_nav2_planner/
│       └── my_controller/
├── maps/
├── config/
├── launch/
├── benchmark/
└── scripts/
```

Do not create empty complexity just for appearance. Add directories when they become necessary.

## 6. Eight-Week Development Mainline

### Week 1 — Development environment and ROS2 basics

Goals:
- verify C++ / CMake / Git / GDB / VS Code + WSL workflow;
- create clean C++ project structure;
- learn ROS2 Node, Topic, Publisher, Subscriber, Message;
- build first C++ ROS2 nodes;
- understand Service, Action, TF at a basic level.

### Week 2 — TurtleBot3 + Gazebo + Nav2

Goals:
- launch TurtleBot3 simulation;
- understand `cmd_vel`, `odom`, LaserScan and TF;
- use RViz;
- understand occupancy grid / costmap;
- run the complete Nav2 pipeline;
- understand Nav2 architecture rather than only launching commands.

### Week 3 — Self-written Planning Core

Implement in modern C++:
- `Planner` interface;
- `GridMap`;
- `Node`;
- Dijkstra;
- A*;
- test maps;
- basic benchmark metrics.

### Week 4 — Nav2 Planner Plugin

Goals:
- learn official Nav2 planner plugin interface;
- create custom planner package;
- convert Nav2 Costmap to internal GridMap;
- implement world-coordinate ↔ grid-coordinate conversion;
- call self-written A* from Nav2;
- output `nav_msgs/Path`;
- run complete Gazebo navigation.

### Week 5 — Multiple Planners + Benchmark

Goals:
- unify planner interface;
- implement Theta*;
- switch planner by configuration;
- compare Dijkstra / A* / Theta*.

Benchmark metrics should include:
- planning time;
- path length;
- expanded nodes;
- path turns / smoothness-related metric;
- success rate.

At the end of this week, the project should already be usable for early internship applications.

### Week 6 — Path Tracking Control

Goals:
- understand Planning vs Control;
- implement Pure Pursuit;
- subscribe to Path and Odometry;
- publish `cmd_vel`;
- complete self-planner + self-controller closed loop;
- measure tracking error.

### Week 7 — Engineering Quality

Focus:
- refactoring;
- CMake organization;
- logging;
- error handling;
- GDB / VS Code debugging;
- Git cleanup;
- reproducibility;
- README and documentation.

### Week 8 — Interview and Resume Packaging

Focus:
- algorithm explanations;
- ROS2/Nav2 architecture explanations;
- C++ engineering explanations;
- benchmark plots/results;
- final README;
- project demo;
- resume bullet points;
- internship applications.

## 7. First Internship-Ready Milestone

The minimum strong milestone is:

```text
Self-written Dijkstra / A* / Theta*
        +
Nav2 Planner Plugin
        +
TurtleBot3 Gazebo closed-loop navigation
        +
multi-map benchmark
        +
clear GitHub README and demo
```

Do **not** wait for MPC, World Model, VLA, or real robot deployment before applying for internships.

## 8. Future Extensions

After the main system works:

1. Hybrid A*
2. Pure Pursuit improvements
3. LQR
4. MPC
5. Dynamic obstacle handling
6. Nav2 Controller Plugin
7. Real robot deployment if a platform is available
8. Learning-based local planner/control
9. World Model / Robot Learning augmentation

Frontier AI is an extension layer, not a substitute for planning/control/system fundamentals.

## 9. Coding Principles

Use modern C++ where appropriate.

Preferred:
- C++17 or newer unless ROS2 package constraints require otherwise;
- RAII;
- smart pointers when ownership is dynamic;
- `const` correctness;
- references instead of unnecessary copies;
- STL containers and algorithms;
- clear interfaces between modules;
- small, testable components;
- meaningful names;
- avoid global state unless strongly justified.

Do not introduce advanced C++ syntax simply to look sophisticated.

Priority:

```text
correctness
→ readability
→ testability
→ engineering structure
→ performance optimization
```

Do not optimize prematurely.

## 10. CMake Principles

Prefer target-based CMake.

Example style:

```cmake
add_library(planning_core
    src/astar.cpp
)

target_include_directories(planning_core
    PUBLIC
    include
)

add_executable(planning_demo
    src/main.cpp
)

target_link_libraries(planning_demo
    PRIVATE
    planning_core
)
```

Prefer out-of-source builds:

```bash
cmake -S . -B build
cmake --build build
```

Generated artifacts must not be committed.

## 11. Git Workflow

Normal daily workflow:

```bash
git status
git diff
git add .
git commit -m "Describe the actual change"
git push
```

Commits should represent meaningful progress.

Good examples:

```text
Add initial planning core structure
Implement Dijkstra planner
Implement AStar planner
Add grid map coordinate conversion
Integrate custom planner with Nav2
Add ThetaStar benchmark
Implement Pure Pursuit controller
```

Avoid meaningless messages such as:

```text
update
fix
test
123
```

Before large changes, check:

```bash
git status
```

Never commit:
- `build/`
- `install/`
- `log/`
- object files;
- large generated files;
- credentials;
- GitHub tokens;
- private lab/project data.

## 12. Security / Repository Boundary

This GitHub repository is public.

Never put into it:
- passwords;
- Personal Access Tokens;
- SSH private keys;
- private APIs;
- personal secrets;
- unpublished lab source code;
- defense/military project code or data;
- proprietary datasets;
- files copied from confidential projects.

If code comes from another repository, respect its license and clearly distinguish reference code from original work.

The goal is to implement the important modules independently rather than copy an entire existing project.

## 13. Reference Projects

Useful references:

### Nav2
`ros-navigation/navigation2`

Role:
- final ROS2 navigation framework;
- understand plugin architecture and system integration.

Do not attempt to read the entire source tree.

### Nav2 Tutorials
`ros-navigation/navigation2_tutorials`

Role:
- official plugin examples;
- use when implementing Nav2 planner/controller plugins.

### ros_motion_planning
`ai-winter/ros_motion_planning`

Role:
- algorithm reference;
- compare implementation ideas for A*, Theta*, Hybrid A*, RRT, PID, LQR, MPC, etc.

Important:
- mainly ROS1-oriented;
- do not use it as the project base;
- reimplement core algorithms in this project's own architecture.

Other advanced references can be introduced only when needed.

## 14. Environment Assumptions

Primary development environment:

```text
Windows
  ↓
WSL2
  ↓
Ubuntu
  ↓
C++ / CMake / GDB / Git
  ↓
ROS2
```

Projects should live in the Linux filesystem, not under `/mnt/c`, unless there is a specific reason.

Typical location:

```text
/home/chd/ros2-navigation-planning-control
```

Before installing ROS2, first verify Ubuntu version:

```bash
lsb_release -a
```

Preferred pairing:
- Ubuntu 24.04 → ROS2 Jazzy
- Ubuntu 22.04 → ROS2 Humble

Do not repeatedly reinstall Ubuntu/ROS2 just to chase versions.

## 15. How AI Agents Should Assist

When working in this repository, do not blindly implement large amounts of code without explanation.

The user is using this project to learn and prepare for robotics internships.

For every meaningful module:

1. Explain its role in the overall system.
2. Explain the interface and data flow.
3. Implement in a way the user can understand.
4. Keep changes scoped.
5. Build and test after changes.
6. Explain compiler/runtime errors when they occur.
7. Avoid adding unnecessary abstractions.
8. Prefer incremental commits.
9. Never fabricate experimental results.
10. Never claim a feature is complete unless it was actually built/tested.

When introducing unfamiliar C++ or ROS2 syntax:
- explain why it exists;
- explain what problem it solves;
- explain the specific line in the current project.

Avoid fragmented teaching with excessive bullet points. Prefer coherent explanations organized around the system mainline.

## 16. Project Learning Rule

Do not turn this project into a sequence of disconnected tutorials.

The preferred learning cycle is:

```text
understand enough theory
        ↓
implement
        ↓
compile / run
        ↓
encounter concrete problem
        ↓
debug
        ↓
return to theory
        ↓
improve implementation
```

Roughly 60% understanding is enough to begin implementation.

The user should not spend days fully mastering a topic before touching the project.

## 17. Definition of “Resume-Quality”

A feature counts only when the user can answer:

- What problem does it solve?
- Where is it in the system architecture?
- What are its inputs and outputs?
- Why was this algorithm/design selected?
- How is it implemented?
- How was it tested?
- What failed during development?
- What metrics were measured?
- What trade-offs were observed?

A screenshot of Nav2 running is not enough.

The project should show original engineering work, system understanding, and quantitative evaluation.

## 18. Current Next Step

The repository setup is complete.

Immediate next task:

Create a minimal clean C++ planning-core skeleton and verify that it compiles.

Suggested first structure:

```text
planning_core/
├── CMakeLists.txt
├── include/
│   └── planning_core/
│       └── planner.hpp
└── src/
    ├── planner.cpp
    └── main.cpp
```

The first goal is not to implement A* immediately.

The first goal is:

```text
clean directory
→ CMake configuration
→ library target
→ executable target
→ successful build
→ successful run
→ Git commit
```

Then proceed into ROS2 according to the roadmap.

## 19. Continuity Rule

At the beginning of a new Codex session:

1. Read this `AGENTS.md`.
2. Inspect repository status:
   ```bash
   git status
   git log --oneline -10
   ```
3. Inspect current file tree.
4. Read the relevant source files before changing them.
5. Summarize:
   - current state;
   - last completed milestone;
   - next smallest useful task.
6. Continue from there instead of rebuilding the project from scratch.

If the repository state conflicts with this document, trust the actual repository state first and update this file when the project's direction materially changes.
