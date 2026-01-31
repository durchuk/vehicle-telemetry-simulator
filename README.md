# Vehicle Telemetry Simulator

---
The simulation runs a "0 to 130 km/h" acceleration scenario and exports the telemetry data to a structured .csv file. This raw data is intended to be consumed by Python (Pandas/Matplotlib) to visualize engine efficiency and transmission behavior.
### 🎓 Project Context
This project was carried out during a two-week educational break. My goal was not to create complex software, but to learn the basics of C++ (memory management, OOP) and set up a clean development environment (Git, CMake) to prepare myself for the industrial requirements of my future work-study program.

### 📝 Description
The **Vehicle Telemetry Simulator** is a console-based C++ engine designed to generate synthetic vehicle performance data.

Instead of using pre-existing datasets, this program proceduraly generates telemetry data based on physics. It models the relationship between **RPM (Engine Speed)**, **Velocity**, and **Gear Shifting logic**, creating a non-linear data stream that mimics real-world driving mechanics.

The program executes a **"Top Speed Run" performance test**:
1.  **Acceleration Phase:** Wide-open throttle (WOT) acceleration simulates the engine torque curve and automatic gear shifting logic.
2.  **Aerodynamic Limit:** The physics engine dynamically calculates air resistance ($F_{drag} \propto v^2$) and rolling resistance.

The simulation exports high-frequency telemetry (60Hz) to a `.csv` file, which is automatically processed by an embedded Python script to generate the performance report.

### 🚀 Key Features
* **Physics Engine:** Custom algorithm simulating engine RPM drops and recovery during gear shifts.
* **Object-Oriented Design:** Modular `Vehicle` class encapsulating state (speed, gear, fuel) and behavior.
* **Data Serialization:** Efficient file I/O handling to stream simulation steps into `telemetry.csv`.
* **Clean Build System:** Project structured with **CMake** for cross-platform compatibility.