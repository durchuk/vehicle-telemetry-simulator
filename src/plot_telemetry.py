import pandas as pd
import matplotlib.pyplot as plt

try:
    df = pd.read_csv("telemetry.csv")
except FileNotFoundError:
    print("Error: The file telemetry.csv doesn't exist")
    exit()

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

# First graph: Speed & RPM
ax1.set_title('Speed & RPM')
color = 'tab:blue'
ax1.set_ylabel('Speed (km/h)', color=color)
ax1.plot(df['Time'], df['Speed_kmh'], color=color, label='Speed')
ax1.tick_params(axis='y', labelcolor=color)
ax1.grid(True, which='both', linestyle='--', alpha=0.5)

ax1_rpm = ax1.twinx()
color = 'tab:red'
ax1_rpm.set_ylabel('RPM', color=color)
ax1_rpm.plot(df['Time'], df['RPM'], color=color, linestyle='--', label='RPM')
ax1_rpm.tick_params(axis='y', labelcolor=color)

# Second graph: Gears
ax2.plot(df['Time'], df['Gear'], color='purple', marker='o', markersize=2, linestyle='-', label='Gear')
ax2.set_ylabel('Gear')
ax2.set_xlabel('Time (s)')
ax2.set_yticks([1, 2, 3, 4, 5])
ax2.grid(True)
ax2.set_title('Gear Shifting')

plt.tight_layout()
plt.savefig("simulation_results.png")