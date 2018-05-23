# Mesh Viewer

Environment Setup
--------------------
- Just launch project by opening "MeshViewer.vcxproj". Project should be builded on x86 - Release mode. (It's important
that project should be launched on "Release", code should be optimized for getting optimal performance)

- vshader.glsl and fshader.glsl from the project should be in same path with .exe file


Information
---------------
- GL_CULL_FACE is enabled for improving performance

- There is only one global light source and it's fixed on the scene.

- For parsing .off files, the whole .off file is mapped into memory and then read from there.

- Camera only can be rotated on y axis. Adding another axis causes gimbal lock problems, this will be solved with future commits.

- .off files should be in same path with builded .exe file


Controls
------------
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



Bugs & Known Issues
-----------------------
- A group of triangles in stanford bunny is not visible while GL_CULL_FACE is enabled. Probably, they're given in clockwise order in .off file.

- Due to example off files are in linux file ending style, .off files should have LF line ending (\n). Loading Windows CR LF files will give error (\r\n).
