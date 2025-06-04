# Brut

- A Voxel game
---

## How to Run

### Desktop (Linux)

#### Requirements

Make sure the following dependencies are installed:

```bash
sudo apt install build-essential clang cmake
```

#### Build

From the project directory, run:

```bash
chmod +x Make.sh
./Make.sh -d # use [--displaysize] to use display size (fullscreen)
```

#### Run

After building:

```bash
./brut
```

A window should open displaying the game.

---

### Android
Make sure the following dependencies are installed:

```bash
sudo apt install build-essential clang cmake gladle
```

#### Build

From the project directory, run:

```bash
chmod +x Make.sh
./Make.sh -a
```

#### Run
After build your .apk will be saved in android/app/build/outputs/apk/release/