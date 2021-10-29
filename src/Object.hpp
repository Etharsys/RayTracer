#pragma once

#include <g3x.h>

#include <iostream>
#include <memory>


struct Object
{
    Object (G3Xcolor color)
        : _color { color }
    { }

    /**
     * @brief reset object matrix Md, Mi and Mn
     */
    void reset    ();

    /**
     * @brief rescale object / produce a homothetie on matrix Md, Mi and Mn
     * @arg alpha : multiplier in x
     * @arg beta  : multiplier in y
     * @arg gamma : multiplier in z
     */
    void rescale  (double alpha, double beta, double gamma);

    /**
     * @brief produce a theta rotation around axe x /
     * x rotation on matrix Md, Mi and Mn
     * @arg theta : angle to rotate
     */
    void rotate_x (double theta);

    /**
     * @brief produce a theta rotation around axe y /
     * y rotation on matrix Md, Mi and Mn
     * @arg theta : angle to rotate
     */
    void rotate_y (double theta);

    /**
     * @brief produce a theta rotation around axe z /
     * z rotation on matrix Md, Mi and Mn
     * @arg theta : angle to rotate
     */
    void rotate_z (double theta);

    /**
     * @brief move object / produce a translation on matrix Md, Mi and Mn
     * @arg x : movement on x
     * @arg y : movement on y
     * @arg z : movement on z
     */
    void translate(double x, double y, double z);

    /**
     * @brief display object with openGL on the window (not the raytracing)
     * @arg ambi : ambiant coefficient
     * @arg diff : diffusion coefficient
     * @arg spec : specular coefficient
     * @arg shin : shine coefficient
     */
    virtual void display([[maybe_unused]] double ambi,
                         [[maybe_unused]] double diff,
                         [[maybe_unused]] double spec,
                         [[maybe_unused]] double shin) const 
    { std::cout << "should not happen" << std::endl; }
    
    /**
     * @brief return if a ray cross object
     * @arg ray_org : starting point of the ray
     * @arg ray_v   : ray vector
     * @arg inter_p : address of the crossing point 
     * @arg inter_v : address of the normal object vector going through J
     */
    virtual bool inter  ([[maybe_unused]] const G3Xpoint& ray_org,
                         [[maybe_unused]] const G3Xvector& ray_v,
                         [[maybe_unused]] G3Xpoint* inter_p,
                         [[maybe_unused]] G3Xvector* inter_v) const
    { return false; }

    G3Xhmat  _Md;
    G3Xhmat  _Mn;
    G3Xhmat  _Mi;
    G3Xcolor _color;
};

/**
 * CAUTION : square don't actually works for raytracing
 */
struct Cube : public Object
{
    Cube (G3Xcolor color);
    void display(double ambi, double diff, double spec, double shin) const override;

    bool inter  (const G3Xpoint& ray_org, 
                 const G3Xvector& ray_v,
                 G3Xpoint* inter_p,
                 G3Xvector* inter_v) const override;
};

struct Sphere : public Object
{
    Sphere (G3Xcolor color);
    void display(double ambi, double diff, double spec, double shin) const override;

    bool inter  (const G3Xpoint& ray_org, 
                 const G3Xvector& ray_v,
                 G3Xpoint* inter_p,
                 G3Xvector* inter_v) const override;
};