=====================================================
RAYTRACER - PORTEFAIX MAXIME - mportefa@etud.u-pem.fr
=====================================================


=== REQUIREMENT ===
g++ compiler
cmake > v2.8
opengl (glut - lgu - gl libraries)
g3x


=== CONTENT ===
A CMakeLists.txt to complile the project.
A src folder which contains all sources.
A build folder which contains build infos and the executable.


=== INSTALL ===
The archive already contains a build and so an executable.

If you really want to compile : i recommend to use VSCode
(which is the environement used for this project) or
enter in the root of the project and type :
'$ cmake .'


=== LAUNCH ===
An executable for the raytracer is locatated in the build
folder and named RayTracer ('$ ./build/RayTracer').


=== FEATURES ===
- 3D Objects as SPHERE which can rotate/translate/scale
- 3D Scene which can create scenes in opengl
- Camera which can observe the scene and display herself 
  and raytrace in 3D
- Lights : ambiance, diffusion, specular point, shininess,
  reflexion


=== USER MANUAL ===
Below the window you have light handling :
    shininess, specular, diffusion, ambiance. 
On the right side of the window you have the camera handling :
    rotation phi & theta, focus, distance, recursion.
To change the camera resolution, i didn't put a scroller, you
can change it in the 'src/config.hpp' file and recompile.
To change the scene, you can change it in the init function
of the 'src/ray_tracer.cpp' file. 


=== BUGS & NON-WORKING FEATURES ===
First, transparency is not implemented.
Going to 3D, i had a lot of bugs with cubes, you can try it with
the scene 3.
The recursion seems to have some bugs : the recursion 2 
is praticly fine but >2 has plenty of unwanted behaviours.
