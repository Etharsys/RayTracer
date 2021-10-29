#include "Object.hpp"

#include <g3x.h>


using namespace std;


/* === Cube === */

Cube::Cube(G3Xcolor color)
    : Object { color }
{
    reset();
}

void Cube::display (double ambi, double diff, double spec, double shin) const
{
    g3x_Material(_color, ambi, diff, spec, shin, 1.);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glMultMatrixd(_Md.m);
        glutSolidCube(2.);
    glPopMatrix();
}

bool Cube::inter (const G3Xpoint& ray_org, 
                    const G3Xvector& ray_v,
                    G3Xpoint* inter_p,
                    G3Xvector* inter_v) const
{ // apparently full of bugs and not working !
    G3Xvector ctr[6] = { {+1., 0., 0.}, {0., +1., 0.}, {0., 0., +1.},
                         {-1., 0., 0.}, {0., -1., 0.}, {0., 0., -1.}};
    G3Xvector nor[6] = { {+1., 0., 0.}, {0., +1., 0.}, {0., 0., +1.},
                         {-1., 0., 0.}, {0., -1., 0.}, {0., 0., -1.}};

    bool flag[6] = { false, false, false, false, false, false };
    if(ray_org.x > 1) flag[0] = true; else if (ray_org.x < -1) flag[3] = true;
    if(ray_org.y > 1) flag[1] = true; else if (ray_org.y < -1) flag[4] = true;
    if(ray_org.z > 1) flag[2] = true; else if (ray_org.z < -1) flag[5] = true;

    for (u_int i = 0; i < 6; ++i)
    {
        if (flag[i] == false) continue;

        G3Xpoint C = ctr[i];
        *inter_v = nor[i];

        G3Xvector AC = g3x_SetVect(ray_org, C);
        double ps1 = g3x_ProdScal(AC    , *inter_v); if (ps1 >= 0.) continue;
        double ps2 = g3x_ProdScal(ray_v , *inter_v); if (ps2 >= 0.) continue;
        double t = ps1 / ps2;
        inter_p->x = ray_org.x + t*ray_v.x;
        inter_p->y = ray_org.y + t*ray_v.y;
        inter_p->z = ray_org.z + t*ray_v.z;
        if (inter_p->x > 1. || inter_p->y > 1. || inter_p->z > 1.) continue;
        return true;
    }
    return false;
}


/* === Sphere === */

Sphere::Sphere(G3Xcolor color)
    : Object { color }
{
    reset();
}

void Sphere::display (double ambi, double diff, double spec, double shin) const
{
    g3x_Material(_color, ambi, diff, spec, shin, 1.); // 1. = alpha
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glMultMatrixd(_Md.m);
        glutSolidSphere(1., 40, 40);
    glPopMatrix(); 
}

bool Sphere::inter (const G3Xpoint& ray_org, 
                    const G3Xvector& ray_v, 
                    G3Xpoint* inter_p,
                    G3Xvector* inter_v) const
{
    double t = -g3x_ProdScal(ray_v, (G3Xvector) ray_org);
    if (t <= 0.) 
    { // vector not even on the direction of the sphere
        return false;
    }

    double d = g3x_SqrNorm(g3x_ProdVect(ray_v, (G3Xvector) ray_org));
    if (d > 1.) 
    { // vector not going through the sphere
        return false;
    }

    t = t-sqrt(1. -d);
    inter_p->x = ray_org.x + t*ray_v.x;
    inter_p->y = ray_org.y + t*ray_v.y;
    inter_p->z = ray_org.z + t*ray_v.z;
    *inter_v = G3Xvector { inter_p->x, inter_p->y, inter_p->z };

    return true;
}


/* === Transformations === */

void Object::reset()
{
    _Md = g3x_Identity();
    _Mn = g3x_Identity();
    _Mi = g3x_Identity();
}

void Object::rescale(double alpha, double beta, double gamma)
{
    _Md = g3x_ProdHMat(g3x_MakeHomothetieXYZ(alpha, beta, gamma), _Md);
    _Mn = g3x_ProdHMat(g3x_MakeHomothetieXYZ(beta*gamma, alpha*gamma, alpha*beta), _Mn);
    _Mi = g3x_ProdHMat(_Mi, g3x_MakeHomothetieXYZ(1./alpha, 1./beta, 1./gamma));
}

void Object::rotate_x(double theta)
{
    _Md = g3x_ProdHMat(g3x_MakeRotationX(theta), _Md);
    _Mn = g3x_ProdHMat(g3x_MakeRotationX(theta), _Mn);
    _Mi = g3x_ProdHMat(_Mi, g3x_MakeRotationX(-theta));
}

void Object::rotate_y(double theta)
{
    _Md = g3x_ProdHMat(g3x_MakeRotationY(theta), _Md);
    _Mn = g3x_ProdHMat(g3x_MakeRotationY(theta), _Mn);
    _Mi = g3x_ProdHMat(_Mi, g3x_MakeRotationY(-theta));
}

void Object::rotate_z(double theta)
{
    _Md = g3x_ProdHMat(g3x_MakeRotationY(theta), _Md);
    _Mn = g3x_ProdHMat(g3x_MakeRotationY(theta), _Mn);
    _Mi = g3x_ProdHMat(_Mi, g3x_MakeRotationY(-theta));
}

void Object::translate(double x, double y, double z)
{
    _Md = g3x_ProdHMat(g3x_MakeTranslationXYZ(x, y, z), _Md);
    _Mi = g3x_ProdHMat(_Mi, g3x_MakeTranslationXYZ(-x, -y, -z));
}