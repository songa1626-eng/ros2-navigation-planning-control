# AGENTS.md

## 1. 项目概述

项目名称：`ros2-navigation-planning-control`

仓库信息：
- WSL 本地路径：`/home/chd/ros2-navigation-planning-control`
- GitHub：`songa1626-eng/ros2-navigation-planning-control`
- 主分支：`main`
- GitHub 认证方式：SSH
- 当前远程地址：
  ```text
  git@github.com:songa1626-eng/ros2-navigation-planning-control.git
  ```

项目目标：

使用 C++ 构建一个具备简历价值的 **ROS2/Nav2 移动机器人自主规划与控制系统**。项目从仿真开始，逐步加入自研规划算法、路径跟踪控制、Nav2 插件、Benchmark 和工程化结构。

本项目不能停留在“ROS2 跑通 Demo”层面。最终要求是：
- 能独立解释系统架构；
- 能解释核心算法原理与代码实现；
- 能完整复现；
- 能进行定量实验；
- 能说明开发过程中遇到的问题与调试过程；
- 能作为机器人规划与控制方向的实习项目写入简历。

---

## 2. 用户当前基础

用户正在以机器人方向为目标学习现代 C++，当前并非零基础。

已经接触或学习过：
- C++ 基本语法；
- 类与对象；
- 继承、多态；
- 引用、指针；
- 智能指针；
- STL；
- 模板与泛型编程；
- `priority_queue`、`unordered_set` 等容器；
- A* 算法及其一个中型 C++ 项目实现；
- Linux / WSL 基础；
- C++ 多文件编译；
- CMake；
- `add_library`、`add_executable`；
- GDB 基础调试；
- Linux 文件权限；
- Linux 进程；
- PATH；
- `find`、`grep`、管道；
- Git / GitHub 基础工作流；
- GitHub SSH 认证。

用户当前仍处于“边做项目边补工程基础”的阶段。

因此：
- 不要假设用户已经系统掌握大型 C++ 工程；
- 遇到新的 C++、ROS2、Nav2、CMake 语法时需要解释；
- 但不要把用户当成零基础，从变量、循环等最基础内容重新讲起。

---

## 3. 职业与技术主线

当前职业主线：

**Robot Motion Planning / Planning & Control**

核心能力主线：

```text
C++ / Linux / ROS2
        ↓
机器人软件工程
        ↓
路径规划 / 运动规划
        ↓
轨迹优化 / 控制
        ↓
MPC / 更复杂约束规划
        ↓
Robot Learning / World Model / VLA
```

当前项目优先级：

```text
工程基础
→ 规划算法
→ ROS2 / Nav2 系统集成
→ 控制
→ Benchmark
→ 工程化
→ 再考虑更前沿 AI 方法
```

不要为了追逐 VLA、World Model、强化学习等热点而跳过机器人系统基础。

---

## 4. 当前项目状态

已经完成：

- 已创建 GitHub 仓库；
- 已创建 WSL 本地仓库；
- 本地主分支为 `main`；
- 已配置 Git 用户名与邮箱；
- 已创建 `README.md`；
- 已创建 `.gitignore`；
- 已完成首次 Git commit；
- 已完成首次 GitHub push；
- 已配置 GitHub SSH Key；
- 已成功通过：
  ```bash
  ssh -T git@github.com
  ```
  验证 GitHub 身份；
- 当前仓库远程地址已经从 HTTPS 切换为 SSH；
- 以后执行：
  ```bash
  git push
  ```
  通常不再需要输入 GitHub 用户名或 Personal Access Token；
- `AGENTS.md` 已纳入版本管理。

当前项目仍处于正式编码前的初始化阶段。

---

## 5. 当前最近任务

当前最小任务不是直接实现完整 A* 或直接进入 Nav2，而是先建立一个干净、可编译的 C++ 项目骨架。

第一阶段目标：

```text
建立 planning_core
→ 建立 include / src
→ 配置 CMake
→ 建立 library target
→ 建立 executable target
→ 成功编译
→ 成功运行
→ Git commit
```

完成后再进入 ROS2 基础与 Nav2。

---

## 6. 目标系统架构

总体系统：

```text
Map / Costmap
      ↓
Global Planner
Dijkstra / A* / Theta*
后续加入 Hybrid A*
      ↓
nav_msgs/Path
      ↓
Controller
Pure Pursuit
后续加入 LQR / MPC
      ↓
cmd_vel
      ↓
TurtleBot3
      ↓
Gazebo / RViz
```

最终 Nav2 集成结构：

```text
RViz Goal
   ↓
Nav2
   ↓
Planner Server
   ↓
自定义 Nav2 Planner Plugin
   ↓
自研 Planning Core
   ↓
nav_msgs/Path
   ↓
Controller
   ↓
cmd_vel
   ↓
TurtleBot3
```

后续控制器也可以进一步封装成 Nav2 Controller Plugin。

---

## 7. 计划中的仓库结构

仓库后续逐步演化为：

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

注意：

不要为了“看起来像大型项目”而一次性创建大量空目录。

目录应在真正需要对应模块时逐步建立。

---

## 8. 八周开发主线

### 第 1 周：开发环境与 ROS2 基础

目标：
- 确认 C++ / CMake / Git / GDB / VS Code + WSL 工作流；
- 建立第一个规范 C++ 工程；
- 学习 ROS2 Node；
- 学习 Topic；
- 学习 Publisher / Subscriber；
- 理解 Message；
- 用 C++ 写第一个 ROS2 节点；
- 初步理解 Service、Action、TF。

### 第 2 周：TurtleBot3 + Gazebo + Nav2

目标：
- 启动 TurtleBot3 仿真；
- 理解 Gazebo 和 RViz 的区别；
- 理解 `cmd_vel`；
- 理解 `odom`；
- 理解 LaserScan；
- 理解 TF；
- 理解 Occupancy Grid；
- 理解 Costmap；
- 跑通 Nav2 完整导航流程；
- 建立对 Nav2 系统架构的整体认识。

### 第 3 周：自研 Planning Core

使用现代 C++ 实现：

- `Planner` 抽象接口；
- `GridMap`；
- `Node`；
- Dijkstra；
- A*；
- 基础测试；
- 基础 Benchmark。

这一阶段规划算法应尽量与 ROS2 解耦。

### 第 4 周：Nav2 Planner Plugin

目标：
- 阅读官方 Nav2 Planner Plugin 示例；
- 创建自定义 planner package；
- 将 Nav2 Costmap 转换为内部 GridMap；
- 实现世界坐标与栅格坐标转换；
- 调用自己的 A*；
- 输出 `nav_msgs/Path`；
- 在 TurtleBot3 + Gazebo 中完成闭环导航。

### 第 5 周：多算法与 Benchmark

目标：
- 统一 Planner 接口；
- 实现 Theta*；
- 通过配置切换算法；
- 比较 Dijkstra / A* / Theta*。

Benchmark 至少包括：
- 规划耗时；
- 路径长度；
- 扩展节点数；
- 路径转折情况；
- 成功率。

这一阶段结束后，应达到第一版实习投递标准。

### 第 6 周：路径跟踪控制

目标：
- 明确 Planning 与 Control 的边界；
- 理解 Pure Pursuit；
- C++ 实现 Pure Pursuit；
- 订阅 Path；
- 订阅 Odometry；
- 发布 `cmd_vel`；
- 完成自研 Planner + 自研 Controller 闭环；
- 统计跟踪误差。

### 第 7 周：工程化

重点：
- 代码重构；
- CMake 结构；
- 错误处理；
- ROS2 logging；
- GDB；
- VS Code Debug；
- Git 提交质量；
- README；
- 可复现性；
- 项目目录整理。

### 第 8 周：简历与面试整理

重点：
- Dijkstra / A* / Theta*；
- 启发函数；
- 最优性；
- Nav2 架构；
- ROS2 通信机制；
- C++ 工程设计；
- Planner Plugin；
- Benchmark；
- 实验结果；
- Demo；
- README；
- 简历项目描述；
- 开始正式实习投递。

---

## 9. 第一阶段实习投递标准

满足以下条件后即可开始第一轮投递：

```text
自研 Dijkstra / A* / Theta*
        +
Nav2 Planner Plugin
        +
TurtleBot3 Gazebo 闭环导航
        +
多地图 Benchmark
        +
清晰 README
        +
可展示 Demo
```

不要为了“等项目全部完成”而无限推迟实习投递。

Hybrid A*、MPC、World Model、VLA、真机部署都属于后续加分项。

---

## 10. 后续增强路线

主系统完成后，按优先级考虑：

1. Hybrid A*
2. Pure Pursuit 优化
3. LQR
4. MPC
5. 动态障碍处理
6. Nav2 Controller Plugin
7. 真机部署
8. Learning-based Local Planner / Controller
9. Robot Learning
10. World Model
11. VLA 与 Planning / Control 的结合

---

## 11. C++ 编码原则

优先使用现代 C++。

推荐：
- C++17 或以上；
- RAII；
- `const` correctness；
- 引用避免不必要复制；
- 智能指针管理动态所有权；
- STL；
- 清晰的接口设计；
- 模块化；
- 小而可测试的组件；
- 明确的命名；
- 尽量减少全局状态。

原则：

```text
正确性
→ 可读性
→ 可测试性
→ 工程结构
→ 性能
```

不要过早优化。

不要为了“高级”而强行使用复杂模板、元编程或晦涩语法。

用户如果不理解某个语法，应解释：
1. 为什么需要它；
2. 它解决什么问题；
3. 它在当前代码中具体做什么。

---

## 12. CMake 原则

优先使用现代 target-based CMake。

推荐风格：

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

推荐构建方式：

```bash
cmake -S . -B build
cmake --build build
```

不要把生成文件提交进 Git。

---

## 13. Git 工作流

当前 GitHub 使用 SSH 认证。

远程仓库应为：

```text
origin  git@github.com:songa1626-eng/ros2-navigation-planning-control.git
```

可以使用：

```bash
git remote -v
```

检查。

正常日常流程：

```bash
git status
git diff
git add .
git commit -m "描述本次实际修改"
git push
```

推荐 commit：

```text
Add initial planning core structure
Implement Dijkstra planner
Implement AStar planner
Add grid map coordinate conversion
Integrate custom planner with Nav2
Add ThetaStar benchmark
Implement Pure Pursuit controller
```

避免：

```text
update
fix
test
123
```

每次较大修改前先执行：

```bash
git status
```

除非有明确原因，不要重新切回 HTTPS 认证。

---

## 14. Git 安全边界

本仓库为 Public。

禁止提交：
- GitHub Personal Access Token；
- 密码；
- SSH 私钥；
- API Key；
- 个人隐私信息；
- 实验室私有代码；
- 未公开项目代码；
- 军工项目源代码；
- 军工项目数据；
- 保密文档；
- 商业私有数据；
- 大型生成文件；
- `build/`；
- `install/`；
- `log/`。

特别注意：

```text
~/.ssh/id_ed25519
```

是 SSH 私钥，不得复制到仓库。

公钥：

```text
~/.ssh/id_ed25519.pub
```

可以公开，但通常也没有必要放进项目仓库。

---

## 15. 外部项目参考原则

可以参考，但不要整库复制。

### navigation2

仓库：

`ros-navigation/navigation2`

用途：
- Nav2 正式框架；
- 学习系统架构；
- 查看接口定义；
- 理解插件系统。

不要试图从头到尾阅读整个源码。

### navigation2_tutorials

仓库：

`ros-navigation/navigation2_tutorials`

用途：
- 官方 Planner / Controller Plugin 示例；
- 后续自己实现插件时重点参考。

### ros_motion_planning

仓库：

`ai-winter/ros_motion_planning`

用途：
- A*；
- Theta*；
- Hybrid A*；
- RRT；
- PID；
- LQR；
- MPC；
- 规划与控制算法设计参考。

该项目主要偏 ROS1。

本项目不能直接以其为基础复制，而应：
- 学习其设计；
- 理解算法；
- 自己重新建立 ROS2 / Nav2 版本。

---

## 16. 开发环境

当前总体环境：

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

项目应优先放在 Linux 文件系统：

```text
/home/chd/ros2-navigation-planning-control
```

而不是：

```text
/mnt/c/...
```

安装 ROS2 前先执行：

```bash
lsb_release -a
```

根据 Ubuntu 版本选择：
- Ubuntu 24.04 → ROS2 Jazzy
- Ubuntu 22.04 → ROS2 Humble

不要为了版本追新而反复重装系统。

---

## 17. AI Agent 工作方式

Codex 或其他 AI Agent 在这个仓库工作时，应遵守以下原则。

首先理解，再修改。

每次开始新任务前：
- 阅读相关代码；
- 检查仓库结构；
- 检查 Git 状态；
- 理解当前模块所在系统位置。

不要未经说明一次性生成大量代码。

每个重要模块都应说明：
- 它解决什么问题；
- 它位于系统哪个位置；
- 输入是什么；
- 输出是什么；
- 为什么这样设计；
- 与其他模块如何连接。

代码修改应尽量小步进行：

```text
一个明确目标
→ 修改
→ 编译
→ 运行
→ 测试
→ 解释结果
→ commit
```

不要一次跨越多个尚未理解的技术层级。

---

## 18. 教学与解释规范

用户通过项目学习，因此 AI 不只是“代写代码”。

对于陌生概念，应优先讲清：

```text
为什么存在
→ 在整个系统里做什么
→ 当前代码怎么体现
→ 必要语法
```

避免：
- 过度分点；
- 每句话单独成段；
- 只解释语法、不解释系统作用；
- 一次抛出大量高级概念；
- 为了完整而讲过多当前用不到的理论。

讲解应保持整体主线。

例如分析某个类时，应优先：

```text
这个类在系统里的职责
→ 输入输出
→ 成员变量
→ 核心函数
→ 关键语法
```

而不是逐字符解释整份代码。

---

## 19. 学习原则

本项目采用项目驱动方式。

核心循环：

```text
理解必要理论
      ↓
开始实现
      ↓
编译 / 运行
      ↓
遇到具体问题
      ↓
调试
      ↓
返回理论
      ↓
修正理解
      ↓
继续实现
```

不要求某个知识点达到 100% 掌握后才开始写代码。

大约理解 60% 后即可进入实践。

不要重新陷入：
- 长时间只看教程；
- 长时间只读源码；
- 无限补基础；
- 为“准备好了再开始项目”而拖延。

---

## 20. 简历项目完成标准

一个模块只有在用户能够回答以下问题时，才算真正属于自己的项目能力：

- 它解决什么问题？
- 它在整个导航系统哪里？
- 输入和输出是什么？
- 为什么选择这个算法？
- 算法核心原理是什么？
- C++ 是如何实现的？
- 为什么采用当前数据结构？
- 如何测试？
- 出现过什么 Bug？
- 如何定位 Bug？
- 使用什么指标评价？
- 和其他算法相比结果如何？
- 当前方法有什么局限？

只跑通 TurtleBot3 / Nav2 官方 Demo 不算核心项目成果。

核心价值来自：

```text
自研算法
+
ROS2 / Nav2 集成
+
工程实现
+
实验评估
+
完整解释能力
```

---

## 21. 当前下一步

仓库初始化、GitHub、SSH、AGENTS.md 已经完成。

当前正式开发的第一步：

建立：

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

第一阶段不要急着实现 A*。

先验证：

```text
目录结构正确
→ CMake 配置正确
→ planning_core library 成功生成
→ planning_demo executable 成功生成
→ 编译成功
→ 程序运行成功
→ Git commit
```

完成这一阶段后，再继续 ROS2。

---

## 22. 新 Codex 会话继承规则

每次新建 Codex 对话后，优先执行：

1. 阅读根目录 `AGENTS.md`。
2. 执行：
   ```bash
   git status
   git log --oneline -10
   ```
3. 查看仓库目录。
4. 阅读当前任务涉及的源码。
5. 先总结：
   - 当前项目进度；
   - 最近完成内容；
   - 当前代码结构；
   - 下一步最小任务。
6. 用户确认后再进行较大修改。

推荐新会话开场提示词：

```text
请先完整阅读仓库根目录的 AGENTS.md，并检查当前 Git 状态、最近 10 次提交和项目文件结构。

先不要大规模修改代码。

请先告诉我：
1. 当前项目进行到哪里；
2. 当前仓库的主要代码结构；
3. 最近一次完成的功能；
4. 当前最合理的下一步最小任务。

之后再按照 AGENTS.md 中的项目主线继续开发。
```

如果 `AGENTS.md` 与真实仓库状态冲突：

```text
真实代码与 Git 状态
>
AGENTS.md 中的旧描述
```

应优先相信实际仓库，并在发生明显阶段变化时更新 `AGENTS.md`。

---

## 23. AGENTS.md 更新原则

`AGENTS.md` 不是每日开发日志。

不需要因为：
- 修复一个 Bug；
- 写完一个函数；
- 做了一次小实验；
- 普通 commit；

就修改本文件。

以下变化发生时才建议更新：
- 项目阶段发生变化；
- 总体架构变化；
- 技术路线变化；
- 新增重要模块；
- 开发环境发生长期变化；
- 确定新的工程规范；
- 调整简历目标；
- 原有计划明显不再适用。

日常进度主要通过：

```text
代码
+
Git commit
+
README
+
Benchmark 结果
```

进行记录。
