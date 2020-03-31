#!/bin/bash
read -p "Enter selection :> " sel

case $sel in
    1)
        ./Vendor/bin/premake/mac/premake5 gmake2
        make -j8 verbose=1 config=debug
        echo -e "\n\n\n\nDebug Build completed.\n\n\n\n"
        ;;
    2)
        ./Vendor/bin/premake/mac/premake5 gmake2
        make -j8 verbose=1 config=release
        echo -e "\n\n\n\nRelease Build completed.\n\n\n\n"
        ;;
    3)
        ./bin/Debug-macosx-x86_64/Foundations/Foundations
        ;;
    4)
      ./bin/Release-macosx-x86_64/Foundations/Foundations
      ;;
    0)
        rm -rf bin
        rm -rf bin-int
        rm -rf node_modules
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