# Mesh Viewer

## Environment Setup

- Solution is created with Visual Studio 2017.

- It's assumed that OpenGL, FreeGLUT and Windows SDK 8.1 is already installed correctly on the system. This guide can be followed to get your dev. environment ready: http://www.cs.uky.edu/~cheng/cs633/OpenGLInstallGuideWindows.pdf

- Project must be compiled on x86 mode. (Release mode is preferred for performance)

- source folder glsl files inside should be on same directory with exe file.


## Information

- GL_CULL_FACE is enabled for improving performance

- There is only one global light source and it's fixed on the scene.

- For parsing .off files, the whole .off file is mapped into memory and then read from there.

- Camera only can be rotated on y axis. Adding another axis causes gimbal lock problems, this will be solved with future commits.

- .off files should be in same path with builded .exe file

- .off files should have LF line ending (\n). Loading Windows CR LF files will give error (\r\n).


## Controls

- n -> Load next model

- p -> Load previous model

- Left Arrow -> Rotate object by -2 degrees

- Right Arrow -> Rotate object by 2 degrees

- x -> Move mesh on x axis

- y -> Move mesh on y axis

- z -> Move mesh on z axis

- f -> Face drawing mode

- v -> Vertex drawing mode

- e -> Edge drawing mode

- Vertical Mouse Movement -> Rotate camera on y axis

- Mouse Wheel -> Zoom in/zoom out the camera