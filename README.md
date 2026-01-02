# Vehicle Telemetry Simulator

---

### 🎓 Project Context
This project was carried out during a two-week educational break. My goal was not to create complex software, but to learn the basics of C++ (memory management, OOP) and set up a clean development environment (Git, CMake) to prepare myself for the industrial requirements of my future work-study program.

### 📝 Description
The **Vehicle Telemetry Simulator** is a console-based C++ engine designed to generate synthetic vehicle performance data.

Instead of using pre-existing datasets, this program simulates the physical behavior of a car's powertrain in real-time. It models the relationship between **RPM (Engine Speed)**, **Velocity**, and **Gear Shifting logic**, creating a non-linear data stream that mimics real-world driving conditions.

The simulation runs a "0 to 130 km/h" acceleration scenario and exports the telemetry data to a structured `.csv` file. This raw data is intended to be consumed by Python (Pandas/Matplotlib) to visualize engine efficiency and transmission behavior.

### 🚀 Key Features
* **Physics Engine:** Custom algorithm simulating engine RPM drops and recovery during gear shifts.
* **Object-Oriented Design:** Modular `Vehicle` class encapsulating state (speed, gear, fuel) and behavior.
* **Data Serialization:** Efficient file I/O handling to stream simulation steps into `telemetry.csv`.
* **Clean Build System:** Project structured with **CMake** for cross-platform compatibility.