# GL Car Game

A car game I'm trying to make while learning opengl.

---

## How to Run

### Desktop (Linux)

#### Requirements

Make sure the following dependencies are installed:

```bash
sudo apt install build-essential clang libglfw3-dev cmake
```

#### Build

From the project directory, run:

```bash
chmod +x LinuxBuild.sh
./LinuxBuild.sh [-c] # use -c for clean last build before new build
```

#### Run

After building:

```bash
./glcargame
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
pkg install cmake clang glfw
```

#### Build & Run

In the project directory, run:

```bash
bash TermuxX11Build.sh [-c] # use -c for clean last build before new build
```

This script will build the project and launch the game.
Now open the **Termux:X11** app — the OpenGL window should appear.

---

## Notes
- On desktop Linux, make sure your system supports OpenGL and has proper graphics drivers.
