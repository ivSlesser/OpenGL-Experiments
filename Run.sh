#!/bin/bash
read -p "Enter selection :> " sel

case $sel in
    1)
      mkdir Build
      cd Build
      cmake -DCMAKE_BUILD_TYPE=Debug ..
      make -j8
      cd ..
      ;;
    2)
      ./Build/Foundations
      ;;
    0)
        rm -rf .vs
        rm -rf **/*.xc*
        rm -rf *.xcworkspace
        rm -rf **/*.vcx*
        rm -rf *.sln
        rm -rf Makefile
        rm -rf **/Makefile
        rm -rf config
        rm -rf .vscode
        rm -rf Build
        ;;
esac