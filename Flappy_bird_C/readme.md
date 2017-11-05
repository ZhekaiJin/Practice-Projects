Flappy_bird_C: Primitive flappybird on terminal
=========================================

## Description ##

This is a classic flappy bird implmentation on terminal.

## Dependencies ##
* ncurses
* gcc/Clang
* make

## Installing ncurses on linux 
```bash
sudo apt-get update
sudo apt-get install libncurses5-dev
```
## Installing ncurses on MACOS
```bash
curl -O ftp://ftp.gnu.org/gnu/ncurses/ncurses-5.9.tar.gz
tar -xzvf ncurses-5.9.tar.gz
cd ./ncurses-5.9
./configure --prefix=/usr/local \
  --without-cxx --without-cxx-binding --without-ada --without-progs --without-curses-h \
  --with-shared --without-debug \
  --enable-widec --enable-const --enable-ext-colors --enable-sigwinch --enable-wgetch-events \
&& make
sudo make install
```
## Compilation and Usage ##
```bash
make
./bird
```
