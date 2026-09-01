# ROS2 Navigation Planning & Control

基于 ROS2 / Nav2 的移动机器人自主规划与控制项目。

## Current Progress

- [ ] ROS2 development environment
- [ ] TurtleBot3 simulation
- [x] Dijkstra planner
- [x] A* planner
- [ ] Theta* planner
- [ ] Nav2 planner plugin
- [x] Planning benchmark
- [ ] Pure Pursuit controller

## Build and Run

```bash
cmake -S planning_core -B planning_core/build
cmake --build planning_core/build
ctest --test-dir planning_core/build --output-on-failure
planning_core/build/planning_demo dijkstra
planning_core/build/planning_demo astar
planning_core/build/planning_benchmark
```

Benchmark 输出为 CSV，可直接重定向到文件：

```bash
planning_core/build/planning_benchmark > benchmark.csv
```
