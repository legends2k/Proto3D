A skeleton project to get started with learning 3D using OpenGL 3.3.  Dependencies

* [GLFW][] for cross-platform window and GL context creation
* [GLM][] for 3D math utilities
* [Meson][] build system
* [ninja][] build tool

Getting these packages with your favourite package manager should be straight forward:

``` shell
# Archlinux
pacman -S glfw-x11 glm meson ninja

# macOS
brew install glfw glm meson ninja
```

Once you’ve the dependencies installed, just clone this repository and do

``` shell
# create build related files in a separate 'build' directory
meson setup build

cd build

# build
ninja

# run
./proto3d
```

GLAD is already part of the sources; configured for OpenGL 3.3 Core profile with the `GL_KHR_debug` extension.

    
[GLFW]: https://www.glfw.org/
[GLM]: https://github.com/g-truc/glm
[Meson]: https://mesonbuild.com/
