#pragma once

#include <g3x.h>

// window size
constexpr unsigned int WWIDTH  = 720;
constexpr unsigned int WHEIGHT = 720;

// camera resolution - TO CHANGE FOR NEW RESOLUTION
constexpr unsigned int CAM_RES_COL = 310;
constexpr unsigned int CAM_RES_ROW = 310; 

// camera starter constant
constexpr G3Xpoint DEFAULT_CAM_POINT { 0, 0, 25 };

// spheric camera default 
constexpr double DEFAULT_CAM_PHI   = 0.;
constexpr double DEFAULT_CAM_THETA = 0.;
constexpr double DEFAULT_CAM_DIST  = 5.;
constexpr double DEFAULT_CAM_FOCUS = 2.;

// light object variables
constexpr double DEFAULT_AMBIANCE  = 0.1;
constexpr double DEFAULT_DIFFUSION = 0.5;
constexpr double DEFAULT_SPEC      = 0.5;
constexpr double DEFAULT_SHINE     = 0.99;

// raytracer recursion
constexpr int DEFAULT_RECURSION = 2;
