# Apollo — WRO Future Engineers 2021

![Team Apollo](Screen%20Shot%202021-10-23%20at%2011.03.44%20PM.png)

**UAE National Champions 2021 — World Robot Olympiad, Future Engineers Category**
Top 10 finish at the WRO International Finals (Germany), representing the UAE against 100+ participating countries.

Apollo is a fully autonomous 4x4 vehicle built for the WRO Future Engineers challenge, where the car must navigate a closed track, avoid randomly placed obstacles, and complete laps in the lowest possible time — entirely without human input.

---

## How It Works

Apollo combines computer vision with multi-sensor obstacle avoidance to navigate the track in real time:

- **Pixy2 Camera** — detects coloured traffic signs (red and green blocks) on the track and decides which side to pass them on
- **Three Ultrasonic Sensors** (front, left, right) — continuously measure distance to track walls and obstacles to keep the car centered and prevent collisions
- **Micro Servo** — steers the front axle based on combined camera and ultrasonic input
- **Dual-shaft 50 RPM BO Motor** — drives the rear axle for consistent torque and quick starts

The control loop runs on an **Arduino Mega 2560**, polling all three ultrasonic sensors and the Pixy2 camera every cycle, then adjusting steering angle and motor speed based on a priority system: obstacle signs detected by the camera take precedence, followed by wall proximity from the ultrasonics.

---

## Build

- **Chassis:** Modified LEGO Technic frame with custom 3D-printed servo mounts to reduce weight and improve steering response
- **Microcontroller:** Arduino Mega 2560
- **Vision:** CMU Pixy2 Camera (colour signature recognition)
- **Sensors:** 3x ultrasonic distance sensors (front, left, right)
- **Actuation:** 1x micro servo (steering), 1x dual-shaft 50 RPM BO motor (drive)
- **Language:** Arduino C++

---

## Repository Structure

```
apollo/
├── QUALIFYING ROUND CODE/
│   ├── FEC_Q_CLOCKWISE/     # Qualifying run, clockwise track direction
│   └── FEC_Q_CC/            # Qualifying run, counter-clockwise track direction
├── FINAL ROUND CODE/
│   ├── FEC_F_C/              # Final run, clockwise — full obstacle avoidance + Pixy2 logic
│   └── FEC_F_CC/             # Final run, counter-clockwise — full obstacle avoidance + Pixy2 logic
├── ccc_hello_world/
│   └── ccc_hello_world.ino   # Minimal Pixy2 test sketch — verifies camera block detection
└── TEAM APOLLO CAR PICTURES/  # Build photos (front, back, top, bottom, left, right)
```

The qualifying round code handles lap navigation and wall avoidance only. The final round code builds on this with full Pixy2 integration — detecting red and green signature blocks and steering left or right accordingly, plus a dedicated final-stage routine for the last approach.

Two directional versions of each (clockwise / counter-clockwise) exist because the track direction is announced on competition day, so both had to be ready ahead of time.

---

## Team

Built by **Team Apollo (UAE)** under the guidance of Unique World Robotics.

---

## Result

🏆 UAE National Champions, WRO Future Engineers 2021
🌍 Top 10 Internationally, WRO Finals, Germany — one of only 5 teams representing the UAE
