# Mesh Viewer

![Project Screenshot](https://image.ibb.co/cuWYRd/Screenshot.png)

A 3d mesh viewer for models with .off extension, developed with OpenGL on C++.

## Environment Setup

- Solution is created with Visual Studio 2017.

- It's assumed that OpenGL, FreeGLUT and Windows SDK 8.1 is already installed correctly on the system. This guide can be followed to get your dev. environment ready: http://www.cs.uky.edu/~cheng/cs633/OpenGLInstallGuideWindows.pdf

- Project must be compiled on x86 mode. (Release mode is preferred for performance)

- Source folder with shader files inside should be on same directory with exe file.

## Running The Program

Run the command on cmd:

`MeshViewer.exe seashell.off dragon.off`

## Information

- GL_CULL_FACE is enabled for improving performance (Can be disabled from source code, if your models does not generated with taking face culling into account, and if it has missing faces when program is executed)

- There is only one global light source and it's fixed on the scene.

- For parsing .off files, the whole .off file is mapped into memory and then read from there.

- Camera only can be rotated on y axis. Adding another axis causes gimbal lock problems, this will be solved with future commits.

- .off files should be in same path with builded .exe file

## Controls

- n -> Load next model

- p -> Load previous model

- Left Arrow -> Rotate object by -2 degrees

- Right Arrow -> Rotate object by 2 degrees

- x -> Move mesh on x axis (Press capsclock for change direction of movement)

- y -> Move mesh on y axis (Press capsclock for change direction of movement)

- z -> Move mesh on z axis (Press capsclock for change direction of movement)

- f -> Face drawing mode

- v -> Vertex drawing mode

- e -> Edge drawing mode

- Vertical Mouse Movement -> Rotate camera on y axis

- Mouse Wheel -> Zoom in/zoom out the camera

## Licence

Copyright (C) 2018 Doğa Can YANIKOĞLU

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/

## Contributing

Contributors are encouraged to fork this repository and issue pull requests.
