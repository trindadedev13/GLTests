#!/usr/bin/bash

export RUNNING_PATH="\"$(pwd)\""
export PLATFORM=BRUT_PLATFORM_TERMUX_X11

EXECUTABLE="brut_desktop"

P1="$1"

mkdir build

cmake -S . -B build
cmake --build build --target $EXECUTABLE

cp build/desktop/$EXECUTABLE .

if [ ! "$P1" = "-termux" ]; then
  chmod +x $EXECUTABLE
  ./$EXECUTABLE
fi

if [ "$P1" = "-termux" ]; then

  cp $EXECUTABLE $HOME/
  rm $EXECUTABLE

  # start termux-x11 in background and save its PID
  termux-x11 :0 &
  X11_PID=$!

  # define cleanup function to kill termux-x11
  cleanup() {
    echo "Shutting down termux-x11..."
    kill $X11_PID
    exit
  }

  # trap Ctrl+C (SIGINT) and call cleanup
  trap cleanup SIGINT

  # wait for X11 to start
  sleep 5

  # set display
  export DISPLAY=:0

  # run program
  chmod +x $HOME/$EXECUTABLE
  $HOME/$EXECUTABLE

  # cleanup after program ends
  cleanup
fi