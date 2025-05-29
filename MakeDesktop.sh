#!/usr/bin/bash

export RUNNING_PATH="\"$(pwd)\""

EXECUTABLE="brut_desktop"

# Flags
TERMUX_MODE=false
USE_DISPLAY_SIZE=false

# Process all input arguments
for arg in "$@"; do
  case "$arg" in
    -t)
      TERMUX_MODE=true
      ;;
    --termux)
      TERMUX_MODE=true
      ;;
    -d)
      USE_DISPLAY_SIZE=true
      ;;
    --displaysize)
      USE_DISPLAY_SIZE=true
      ;;
    *)
      echo "Unknown argument: $arg"
      ;;
  esac
done

export DISPLAY=:0

if [ "$USE_DISPLAY_SIZE" = true ]; then
  export BRUT_WINDOW_USE_DISPLAY_SIZE=true
fi

mkdir -p build

cmake -DCMAKE_SYSTEM_NAME=Linux -S . -B build
cmake --build build --target "$EXECUTABLE"

cp build/desktop/"$EXECUTABLE" .

if [ "$TERMUX_MODE" = true ]; then
  cp "$EXECUTABLE" "$HOME/"
  rm "$EXECUTABLE"

  termux-x11 :0 &
  X11_PID=$!

  cleanup() {
    echo "Shutting down termux-x11..."
    kill "$X11_PID"
    exit
  }

  trap cleanup SIGINT

  sleep 5

  chmod +x "$HOME/$EXECUTABLE"
  "$HOME/$EXECUTABLE"

  cleanup
fi