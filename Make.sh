#!/usr/bin/bash

set -e

export RUNNING_PATH="\"$(pwd)\""

# Flags
MODE_ANDROID=false
CONFIG_TERMUX_X11_SERVER=false
CONFIG_USE_DISPLAY_SIZE=false

enable_mode_android() {
  MODE_ANDROID=true
  CONFIG_USE_DISPLAY_SIZE=true
  if [ "$CONFIG_TERMUX_X11_SERVER" = true ]; then
    echo "Android Usage:"
    echo "| Params between [] is optional"
    echo "| --android"
    echo "| Type --help to read about options."
    exit 1
  fi
}

enable_mode_desktop() {
  if [ "$MODE_ANDROID" = true ]; then
    echo "Desktop Usage:"
    echo "| Params between [] is optional"
    echo "| --desktop [--displaysize] [--termux]"
    echo "| Type --help to read about options."
    exit 1
  fi
  MODE_ANDROID=false
}

enable_mode_termux() {
  CONFIG_TERMUX_X11_SERVER=true
  if [ "$MODE_ANDROID" = true ]; then
    echo "Termux option should be used with --desktop option."
    exit 1
  fi
}

help() {
  echo "Help"
  echo ""
  echo "Arguments: "
  echo "| --android or -a : Builds Brut for Android."
  echo "| --desktop or -d : Builds Brut for Desktop (probably Linux)."
  echo ""
  echo "Optionals:"
  echo "| --termux      or  -t : Should be used with --desktop, Open a Local X11 Server in Termux."
  echo "| --displaysize or -ds : Should be used with --desktop, Use Display Size in window, instead of fixed size."
  exit 1
}

compile() {
  # Avoid SDL compile error
  export DISPLAY=${DISPLAY:-:0}

  CMAKE_FLAGS=()

  if [ "$CONFIG_USE_DISPLAY_SIZE" = true ]; then
    CMAKE_FLAGS+=("-DBRUT_WINDOW_USE_DISPLAY_SIZE=ON")
  fi

  if [ "$MODE_ANDROID" = true ]; then
    export BRUT_ANDROID=true
    export BRUT_WINDOW_USE_DISPLAY_SIZE=true
    cd android
    chmod +x gradlew
    ./gradlew assembleRelease
  else
    CMAKE_FLAGS+=("-DBRUT_ANDROID=OFF")
    if [ "$CONFIG_TERMUX_X11_SERVER" = true ]; then
      CMAKE_FLAGS+=("-DBRUT_TERMUX=ON")
    fi

    EXECUTABLE="brut_desktop"
    cd desktop
    mkdir -p build

    cmake -S . -B build "${CMAKE_FLAGS[@]}"
    cmake --build build --target "$EXECUTABLE"

    cp build/"$EXECUTABLE" .
  fi
}

termux_x11_server() {
  if [ "$CONFIG_TERMUX_X11_SERVER" = true ]; then
    EXECUTABLE="brut_desktop"
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
}

# cmd args
if [ $# -eq 0 ]; then
  help
  exit 1
fi

for arg in "$@"; do
  case "$arg" in
    -a|--android)
      enable_mode_android
      ;;
    -d|--desktop)
      enable_mode_desktop
      ;;
    -t|--termux)
      enable_mode_termux
      ;;
    -ds|--displaysize)
      CONFIG_USE_DISPLAY_SIZE=true
      ;;
    *)
      help
      ;;
  esac
done

compile
termux_x11_server