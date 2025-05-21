# Brut

- A Voxel game
---

## How to Run

### Desktop (Linux)

#### Requirements

Make sure the following dependencies are installed:

```bash
sudo apt install build-essential clang cmake libsdl3-dev libglm-dev
```

#### Build

From the project directory, run:

```bash
chmod +x LinuxBuild.sh
bash DesktopMake.sh
```

#### Run

After building:

```bash
./brut
```

A window should open displaying the game.

---

### Android (via Termux + Termux:X11)

#### Requirements

- [Termux](https://f-droid.org/en/packages/com.termux/)
- [Termux:X11](https://github.com/termux/termux-x11)

#### Install dependencies

In Termux:

```bash
pkg install cmake clang sdl3 glm
```

#### Build & Run

In the project directory, run:

```bash
bash DesktopMake.sh -termux
```

This script will build the project and launch the game.
Now open the **Termux:X11** app — the OpenGL window should appear.

---

## Notes
- On desktop Linux, make sure your system supports OpenGL and has proper graphics drivers.
