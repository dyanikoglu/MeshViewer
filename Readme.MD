Mesh Viewer by Doga Can YANIKOÐLU
-----------------------------------------------------

Contents
--------
i. Environment Setup
ii. Information
iii. Controls
iv. Bugs & Known Issues


i. Environment Setup
--------------------
-> Just launch project by opening "HW4.vcxproj". Project should be builded on x86 - Release mode. (It's important
that project should be launched on "Release", code should be optimized for getting optimal performance)
-> vshader.glsl and fshader.glsl from the project should be in same path with .exe file


ii. Information
---------------
-> GL_CULL_FACE is enabled for improving performance
-> There is only one global light source and it's fixed on the scene.
-> For parsing .off files, the whole .off file is mapped into memory and then read from there. Memorymapped.cpp is used for this (code is not mine)
-> Camera only can be rotated on y axis. Adding another axis causes gimbal lock problems. I talked about this with class teacher, she said that it's not necessary to implement full camera controls due to gimbal lock problems.
-> .off files should be in same path with builded .exe file

iii. Controls
------------
n,N -> Load next model
p,P -> Load previous model
Left Arrow -> Rotate object by -2 degrees
Right Arrow -> Rotate object by 2 degrees
x,X -> Move mesh on x axis
y,Y -> Move mesh on y axis
z,Z -> Move mesh on z axis
f -> Face drawing mode
v -> Vertex drawing mode
e -> Edge drawing mode
Vertical Mouse Movement -> Rotate camera on y axis
Mouse Wheel -> Zoom in/zoom out the camera


iv. Bugs & Known Issues
-----------------------
-> A group of triangles in stanford bunny is not visible while GL_CULL_FACE is enabled. Probably, they're given in clockwise order in .off file.
-> Due to example off files are in linux file ending style, .off files should have LF line ending (\n). Loading Windows CR LF files will give error (\r\n).