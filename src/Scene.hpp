#pragma once

#include "Object.hpp"

#include "config.hpp"

#include <vector>
#include <memory>
#include <g3x.h>

using Objects = std::vector<std::unique_ptr<Object>>;

class Scene
{
    public:
        
        /**
         * @brief display the the scene on the window with openGL function 
         */
        void display();

        /**
         * @brief raytrace object from the scene
         * @arg ray_org : starting point of the ray 
         * @arg ray_vec : ray vector
         * @arg rec     : recursion step (to 0), 1 = no recursion
         */
        G3Xcolor update_tracer(const G3Xpoint& ray_org, 
                               const G3Xvector& ray_vec, 
                               u_int rec = DEFAULT_RECURSION);

        /**
         * @brief add an object to the scene
         * @arg obj : the object to add
         */
        void add(std::unique_ptr<Object> obj);

        /**
         * @brief initiate example on scene
         */
        void init_scene1();
        void init_scene2();
        void init_scene3();

        /**
         * @brief apply ambiance to color
         * @arg final_color : the object flat color
         */
        void compute_ambiance(G3Xcolor* final_color);

        /**
         * @brief apply diffusion to color
         * @arg final_color : address for final color
         * @arg flat_color  : the object flat color
         * @arg inter_norm  : the normal object vector going through ray-object intersection point
         * @arg inter_light : light ray going through ray-object intersection point 
         */
        void compute_diffusion(G3Xcolor* final_color, 
                               const G3Xcolor& flat_color,
                               const G3Xvector& inter_norm, 
                               const G3Xvector& inter_light);

        /**
         * @brief apply specular stain (halo) to color
         * @arg final_color : address for final color
         * @arg flat_color  : the object flat color
         * @arg inter_norm  : the normal object vector going through ray-object intersection point
         * @arg inter_light : light ray going through ray-object intersection point 
         * @arg ray_v       : ray vector
         */
        void compute_halo(G3Xcolor* final_color, 
                          const G3Xcolor& flat_color,
                          const G3Xvector& inter_norm, 
                          const G3Xvector& inter_light,
                          const G3Xvector& ray_v);

        /**
         * @brief get the reflection ray bouncing on object
         * @arg inter_norm   : the normal object vector going through ray-object intersection point
         * @arg ray_v        : ray vector 
         * @return the reflection vector (ray to send)
         */
        G3Xvector reflect_ray(const G3Xvector& inter_norm,
                              const G3Xvector& ray_v);

        /**
         * @brief apply reflection new color to color
         * @arg final_color : address for final color
         * @arg col_reflect : the reflection new color
         */
        void compute_reflect(G3Xcolor* final_color,
                             const G3Xcolor& col_reflect);
        
        G3Xpoint _light;
        double   _ambiance  = DEFAULT_AMBIANCE;
        double   _diffusion = DEFAULT_DIFFUSION;
        double   _spec      = DEFAULT_SPEC;
        double   _shine     = DEFAULT_SHINE;

    private:
        Objects  _objs;

};