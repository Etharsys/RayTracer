#include <iostream>
#include <g3x.h>
#include <memory>

#include "config.hpp"

#include "Scene.hpp"
#include "Camera.hpp"

using namespace std;


// main scene
Scene scene;
// main camera
Camera<CAM_RES_COL, CAM_RES_ROW> cam 
{ 
	scene, 
	DEFAULT_CAM_THETA, 
	DEFAULT_CAM_PHI, 
	DEFAULT_CAM_FOCUS, 
	DEFAULT_CAM_DIST, 
	DEFAULT_RECURSION,
	G3Xpoint { 0, 0, 0 } 
};

inline void set_control_panels()
{
	// CAMERA HANDLING
	g3x_CreateScrollv_d((char*)"phi", &cam._phi   , 0. , 2.*PI, PI/16, "");
	g3x_CreateScrollv_d((char*)"the", &cam._theta , 0. , 2.*PI, PI/16, "");
	g3x_CreateScrollv_d((char*)"foc", &cam._focus , 0.5, 10.  , 0.1  , "");
	g3x_CreateScrollv_d((char*)"dst", &cam._dist  , 1. , 30   , 0.1  , "");
	g3x_CreateScrollv_i((char*)"rec", &cam._rec   , 1  , 5    , 1    , "");

	// LIGHT
	g3x_CreateScrollh_d((char*)"AMBI", &scene._ambiance , 0., 1., 0.05, "");
	g3x_CreateScrollh_d((char*)"DIFF", &scene._diffusion, 0., 1., 0.05, "");
	g3x_CreateScrollh_d((char*)"SPEC", &scene._spec     , 0., 1., 0.05, "");
	g3x_CreateScrollh_d((char*)"SHIN", &scene._shine    , 0., 1., 0.05, "");

}


static void init(void)
{
	set_control_panels();
	g3x_SetCameraCartesian(DEFAULT_CAM_POINT, G3Xpoint { 0, 0, 0 });

	// choose the scene here, 3 has cube which render won't work
	scene.init_scene1();
	//scene.init_scene2();
	//scene.init_scene3();
}

static void draw()
{
	scene.display();
	cam.update_camera();
	cam.update_tracer();
	cam.display();
}

static void quit()
{
    cerr << "RayTracing ended correctly." << endl;
}

int main(int argc, char** argv)
{
    if (argc != 1)
    {
        cout << argc << argv << endl;
    }

    g3x_InitWindow(*argv, WWIDTH, WHEIGHT);

	g3x_SetInitFunction(init);
	
    g3x_SetDrawFunction(draw);
	
    g3x_SetExitFunction(quit);
    
    return g3x_MainStart();
}
