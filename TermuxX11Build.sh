#!/usr/bin/bash

export RUNNING_PATH="\"$(pwd)\""
export PLATFORM=BRUT_PLATFORM_TERMUX_X11

# compile
if [ "$1" = "-c" ]; then
  rm -rf build
fi

mkdir build
cd build

cmake ..
make

cp desktop/brut_desktop ../

cd ..

# copy executable to home
cp brut_desktop $HOME/brut_desktop
rm brut_desktop

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
chmod +x $HOME/brut_desktop
$HOME/brut_desktop

# cleanup after program ends
cleanup