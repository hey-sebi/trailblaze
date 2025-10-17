# Trailblaze roadmap

## Stage 1: Initial setup & foundations

_Necessary setup and structuring, implementation of core data types_

- Directory structure, CMake, Doxygen, clang-format and clang-tidy
- Core datatypes:
  - State spaces
  - Path modelling
- Evaluation and testing
  - Unit tests
  - Plot generation

## Stage 2: Foundation Extensions — "Path Mechanics"

_Features that make the current path modeling richer and more practical._

### 1. Path Metrics & Cost Models

- Geometric metrics: Length, curvature, smoothness, clearance (if obstacles known).
- Energy-based costs: Acceleration, jerk, or curvature penalties.
- Composite metrics: Weighted combination for optimization and evaluation.

-->️ Enables cost-based comparisons and optimization of paths.

### 2. Kinematic Feasibility & Constraints

- Add motion constraints: max velocity, acceleration, curvature radius.
- Support differential-drive and Ackermann kinematics models.
- Feasability checks. Functions like `bool is_feasible(const path&, const kinematic_model&)`

-->️ Practical use cases when working with mobile robot motion.

## Stage 3: Spatial Intelligence — "Path in Context"

_Environment models and reasoning._

### 1. Environment Representation

- Environment model interface: different environment models (also third party) should be usable.
- Our own environment model implementation
  - 2D occupancy grid(s)
  - polygonal maps
  - distance fields
- Interfaces to query obstacles and distances.

### 2. Collision Checking

- Collision checking interface to allow arbitrary collision checkers.
- Add our own collision checking mechanisms.
- Check if a state / path is collision free

->️ Foundation for planning and validation.

## Stage 4: Path planning

- Add sample based and/or graph based / deterministic planning algorithms

## Stage 5: Optimization and smoothing

- Add gradient-based smoothers (e.g., CHOMP-like approaches).
- Maybe elastic-band or shortcut smoothing.
- Integrate with cost models defined earlier.

--> imporove rough paths into high-quality, dynamically feasible ones.
