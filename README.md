# GraphicsRenderer

C++ implementation of graphics renderer. currently using OpenGL API. Codebase can support multiple graphics APIs with the same abstraction.

## Libraries used:
  - **GLFW**
  - **GLAD**
  - **glm**
  - **stb_image**

#### For now project is setup for multi platform/compiler support (windows visual studio, gmake tested), project files can be generated on the other platforms (x64).

## Project Generation/Compilation
Project files for specific platforms can be generated using [premake5](https://github.com/premake/premake-core/wiki/What-Is-Premake),
which is included in ${root}/vendor/premake as windows binary; Script is in the root directory.

#### Project Generation Example For Visual Studio 2017 and linux/gmake:
  - *From root directory*
  - *./vendor/premake/premake5.exe --os=windows vs2017*
  - *./vendor/premake/premake5 --os=linux gmake*

#### Project compilation example on linux:
  - *From root directory*
  - *Generate gmake project*
  - $ *make*

** Project Started as a private project so most of earlier commits aren't present here
