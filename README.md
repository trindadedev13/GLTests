# OpenGL Tests

Simple OpenGL experiments for learning and testing purposes.

---

## How to Run

### Desktop (Linux)

#### Requirements

Make sure the following dependencies are installed:

```bash
sudo apt install build-essential gcc libglfw3-dev libgl1-mesa-dev
```

#### Build

From the project directory, run:

```bash
chmod +x ./LinuxBuild [-c] # use -c for clean last build before new build
```

#### Run

After building:

```bash
./gltests
```

A window should open displaying the OpenGL test.

---

### Android (via Termux + Termux:X11)

#### Requirements

- [Termux](https://f-droid.org/en/packages/com.termux/)
- [Termux:X11](https://github.com/termux/termux-x11)

#### Install dependencies

In Termux:

```bash
pkg install make clang glfw opengl mesa-dev
```

#### Build & Run

In the project directory, run:

```bash
bash TermuxX11Build [-c] # use -c for clean last build before new build
```

This script will build the project and launch the app.  
Now open the **Termux:X11** app — the OpenGL window should appear.

---

## Notes
- On desktop Linux, make sure your system supports OpenGL and has proper graphics drivers.
