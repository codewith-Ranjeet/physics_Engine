![Header](https://capsule-render.vercel.app/api?type=waving&color=gradient)
# Physics Engine
![Typing SVG](https://readme-typing-svg.herokuapp.com?color=00FF00&lines=Building+Physics+Engine;Learning+C%2B%2B;Testing+Problem+Solving+Skills)

A hobby project where I’m building a simple 2D physics engine from scratch to improve my C++ skills and understand how physics systems actually work under the hood.

This project focuses on understanding core physics concepts like motion, velocity, gravity, and collision systems, while gradually building a cleaner and more structured engine architecture..

---

## 🚀 Current Progress

- Basic window rendering using SFML
- Custom physics system (independent of SFML)
- Velocity-based movement system
- Gravity simulation
- Friction handling
- Ground collision (basic)
- Clean separation of:
  - Physics logic
  - Rendering
  - Input handling

---

## 🧠 Architecture

The project is structured to mimic a real engine design:

- **PhysicsObject** → Stores object state (position, velocity, size)
- **PhysicsWorld** → Handles physics updates and simulation
- **main.cpp** → Handles input and rendering only

> Physics is the source of truth. SFML is used only for visualization.

---

## 🛠 Tech Stack

![C++](https://img.shields.io/badge/C++-blue)
![SFML](https://img.shields.io/badge/SFML-green)

---

## 📁 Project Structure

```
physics_engine/
│
├── src/
│   ├── main.cpp
│   ├── PhysicsObject.h
│   ├── PhysicsObject.cpp
│   ├── PhysicsWorld.h
│   ├── PhysicsWorld.cpp
│
├── bin/
│   └── app.exe
│
├── .gitignore
└── README.md
```

## 🎯 Learning Goals

- Build a physics system from scratch
- Understand motion (position, velocity, acceleration)
- Implement collision systems
- Design scalable game/engine architecture

---

## 🧩 What I’ve Learned So Far

- How velocity-based motion works
- Why separating physics from rendering is important
- Basic collision detection challenges

---

## 🔜 Upcoming Features

- AABB collision system (object vs object)
- Multiple platforms
- Ground detection system (proper)
- Jump mechanics using grounded state
- Delta time (frame-independent physics)

---

## ⚠️ Note

This is not meant to be a production-ready engine.  
It’s a learning project focused on building fundamentals step by step.

---

## 💡 Author

Built as a learning project to strengthen C++ and problem-solving skills.
