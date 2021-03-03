A skeleton project to get started with learning 3D using OpenGL 3.3.  Dependencies

* [GLFW][] for cross-platform window and GL context creation
* [GLM][] for 3D math utilities
* [CMake][] build system

Getting these packages with your favourite package manager should be straight forward:

``` shell
# Archlinux
pacman -S glfw-x11 glm cmake

# macOS
brew install glfw glm cmake
```

[GLAD][] is used for extension loading but it’s already part of the sources; configured for OpenGL 3.3 Core profile with the `GL_KHR_debug` extension.  Needn’t be installed separately.

Clone this repo and proceed after installing dependencies.

# Build

CMake has many generators.  Use whatever is comfortable for you, I’ve shown `Unix Makefiles` for its simplicity and ubiquity.  Check `man cmake-generators`.  `Ninja` is perhaps faster.

``` shell
# avoid polluting working tree with build-related files
mkdir build && cd build

cmake -G "Unix Makefiles" ..

make

cd ..

./Proto3D
```

# Debug

[Qt Creator][] is an efficient cross-platform C++ IDE with decent debugging capability that works atop the GCC/GDB or Clang/LLDB toolchains.  Qt Creator also has full support for CMake-based projects.  Once installed, do the following

1. Setup 32-bit Desktop kit
    1. Open _Qt Creator -> Preferences -> Kits_
    2. Choose `Desktop x86-darwin-generic-mach_o-32bit`
    3. Make sure the C and C++ compilers are set to `Clang (C,x86 32bit in /usr/bin)` and `Clang (C++,x86 32bit in /usr/bin)`
    4. Make sure the debugger is set to `System LLDB at /usr/bin/lldb`
2. _File -> Open File or Project_ and select `/CMakeLists.txt`
3. Choose the kit that was just configured with the _Debug_ configuration and click _Configure Project_
    1. _Build -> Build All Projects_ should succeed; check _4 Compile Output_ panel
4. Click on _Projects_, under _Build & Run_, select _Run_; uncheck _Add build library search path to `DYLD_LIBRARY_PATH` and `DYLD_FRAMEWORK_PATH`_ to [avoid loader errors][qt-macos-dbg-quirk]
    1. Make sure the _Working directory_ is set to the project root
    2. _Build -> Run_ i.e. running without debugging should work fine
5. Add a breakpoint in `/src/main.cpp` and try _Debug -> Start Debugging -> Start Debugging of startup project_
    1. You should be able to step over, into and out of code after some breakpoint is hit; variables and their values should be inspectable

If you’re on macOS or Windows, perhaps Xcode or Visual Studio are better choices.  Simply use the respective generators and get going!

``` shell
cmake -G Xcode ..

cmake -G "Visual Studio 15 2017" -A x64 ..
```

Opening the generated solution should build and debug like any other project.

# Release

``` shell
cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ..
```

# Thanks

Thanks to _Joey De Vries_ for his excellent [LearnOpenGL.com][]; files under `cmake/` also from this [project’s repro][learn-opengl-repo].


[GLFW]: https://www.glfw.org/
[GLM]: https://github.com/g-truc/glm
[CMake]: https://cmake.org/
[GLAD]: https://github.com/Dav1dde/glad
[LearnOpenGL.com]: https://learnopengl.com/
[learn-opengl-repo]: https://github.com/JoeyDeVries/LearnOpenGL
[Qt Creator]: https://www.qt.io/offline-installers
[qt-macos-dbg-quirk]: https://stackoverflow.com/q/38131011/183120
