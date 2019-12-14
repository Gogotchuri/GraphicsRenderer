# GraphicsRenderer
C++ implementation of graphics renderer. currently using OpenGL API. Codebase can support multiple graphics APIs with the same abstraction.
### Libraries used:
  -**GLFW**
  -**GLAD**
  -**glm**
  -**stb_image**
#### For now project is setup for windows visual studio, but can be compiled on the other platforms (x64) (With some minor tweaks to premake script).

## Project Generation/Compilation
Project files for specific platforms can be generated using [premake5](https://github.com/premake/premake-core/wiki/What-Is-Premake),
which is included in ${root}/vendor/premake as windows binary; Script is in the root directory.

#### Project Generation Example For Visual Studio 2017
  - *From root directory*
  - *./vendor/premake/premake5.exe --os=windows vs2017*

