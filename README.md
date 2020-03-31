# OpenGL Windows / Mac Premake 5 Project

[This project is included with 'Template'](https://gist.github.com/ivSlesser/9b22ee1ac97fcc9e5d201486f73a9942)

Premake is a build configuration tool for C/C++ in that it generates project files using a LUA configuration.
[Read more about Premake](https://premake.github.io/)

## Features

*   Visual Studio & GNU Make support
*   Easy build and clean up scripts
*   GLFW & Glad included
*   Easily extensible!

## Building

To build the project there is an included file for both MacOS and Windows, this will generate the project files using the include Premake executable for that platform's build tool.

Windows (VS2019) `Generate.bat` 
GNU Make (gamke2) `./Generate.sh` 

If you wish to build for other platforms then you can run Premake directly from the `vendor/bin/<platform>` folder, where `<platform>` is either `win` or `mac` 

## Clean Up

The project includes a `.gitignore` file that will filter out the specific project files and outputs, but if you need to manually trigger a clean up then you can use one of two scripts depending on your platform to remove all generated files.

Windows `Clean.bat` 

