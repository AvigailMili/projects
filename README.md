The program depends on "ncurses" library on Linux,
install:
sudo apt-get install libncurses5-dev libncursesw5-dev
compile:
g++  -o snake.out point.cpp snake.cpp game.cpp main_snake.cpp -lncurses
