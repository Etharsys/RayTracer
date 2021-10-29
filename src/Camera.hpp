#pragma once

#include <vector>
#include <array>
#include <iostream>
#include <g3x.h>
#include <math.h>
#include <memory>

#include "Object.hpp"
#include "Scene.hpp"

#include "config.hpp"


template <unsigned int Res_Col, unsigned int Res_Row>
class Camera
{
    public:
        Camera (Scene& cam_scene,
                double theta, double phi,
                double focus, double dist,
                int rec,
                G3Xpoint target)
            : _theta  { theta },
              _phi    { phi },
              _focus  { focus },
              _dist   { dist },
              _rec    { rec },
              _target { target },
              _scene  { cam_scene }
        { }
        
        /**
         * display the camera on the window with openGL functions
         */
        void display() //display cam on scene
        {
            /* chargement de la matrice de la caméra dans la pile GL */
            glPushMatrix();
            glMultMatrixd(_Md.m);

            /* caméra canonique */

            /*= Chargement Pixmap => Texture Gl =*/
            glDisable(GL_LIGHTING);
            glEnable(GL_TEXTURE_2D);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGBA,Res_Row,Res_Col,GL_RGBA,GL_FLOAT,render_to_ptr());
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                glColor3f(1.,1.,1.);
                glBegin(GL_QUADS);
                glTexCoord2d(0,0); glVertex3d(-1.,-1.,0.);
                glTexCoord2d(1,0); glVertex3d(-1.,+1.,0.);
                glTexCoord2d(1,1); glVertex3d(+1.,+1.,0.);
                glTexCoord2d(0,1); glVertex3d(+1.,-1.,0.);
                glEnd();
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_LIGHTING);

            /* cadre */
            glDisable(GL_LIGHTING);
            glColor3f(1.,1.,1.);
            glBegin(GL_LINE_LOOP);
                glVertex3d(-1.,-1.,0.);
                glVertex3d(-1.,+1.,0.);
                glVertex3d(+1.,+1.,0.);
                glVertex3d(+1.,-1.,0.);
            glEnd();
            glColor3f(.5,.5,.5);
            glBegin(GL_LINES);
                glVertex3d(-1.,-1., 0.);
                glVertex3d( 0., 0.,-1.);
                glVertex3d(-1.,+1., 0.);
                glVertex3d( 0., 0.,-1.);
                glVertex3d(+1.,+1., 0.);
                glVertex3d( 0., 0.,-1.);
                glVertex3d(+1.,-1., 0.);
                glVertex3d( 0., 0.,-1.);
            glEnd();
            glColor3f(1.,0.,0.);
            glBegin(GL_LINES);
                glVertex3d(0., 0.,-1.);
                glVertex3d(0., 0.,0.5*_dist);
            glEnd();
            glEnable(GL_LIGHTING);
            /* dépilage de la matrice */
            glPopMatrix();
        }

        /**
         * transform the raytracing render from array<array<color>> to a void*
         * This is usefull for function gluBuild2DMipmaps of openGL (on display())
         */
        void* render_to_ptr()
        {
            G3Xcolor res[Res_Col * Res_Row];
            u_int i = 0;
            for (const auto& line : _render)
            {
                for (const auto& px : line)
                {
                    res[i] = px;
                    i++;
                }
            }
            void * ref;
            ref = &res;
            return ref;
        }

        /**
         * update the camera features (rotations, focal, distance from target)
         * on the window / the scene by updating Md matrix
         */
        void update_camera()
        {
            G3Xpoint pos = G3Xpoint { _target.x + _dist * cos(_theta) * sin(_phi),
                                      _target.y + _dist * sin(_theta) * sin(_phi),
                                      _target.z + _dist * cos(_phi)};
            G3Xvector u = g3x_SetVect(pos, _target);
            g3x_Normalize(&u);
            double rot_y = acos(u.z);
            double rot_z = (G3Xiszero(rot_y) ? 
                            PI : 
                            (u.y < 0. ? -1. : +1.) * acos(u.x/sin(rot_y)) );

            _Md = g3x_Identity();
            _Md = g3x_ProdHMat(g3x_MakeHomothetieXYZ(Res_Row/(1.*Res_Col) , 1., _focus),_Md);
            _Md = g3x_ProdHMat(g3x_MakeRotationZ(PI/2.), _Md);
            _Md = g3x_ProdHMat(g3x_MakeRotationY(rot_y), _Md);
            _Md = g3x_ProdHMat(g3x_MakeRotationZ(rot_z), _Md);
            _Md = g3x_ProdHMat(g3x_MakeTranslationV(pos), _Md);
        }

        /**
         * main function to call to update the ray_tracer 
         */
        void update_tracer()
        {
            G3Xpoint E = g3x_ProdHMatPoint(_Md, G3Xpoint { 0., 0., -1. });

            double x_step = 2./Res_Col;
            double y_step = 2./Res_Row;
            for (u_int x = 0; x < Res_Row; ++x) // rows
            {
                for (u_int y = 0; y < Res_Col; ++y) // cols
                {
                    G3Xpoint  pix_cam = G3Xpoint { -1.+ x * x_step, -1.+ y * y_step, 0.};
                    G3Xpoint  ray_p   = g3x_ProdHMatPoint(_Md, pix_cam);
                    G3Xvector ray_v   = g3x_SetVect(E, ray_p); 
                    g3x_Normalize(&ray_v);

                    auto color = _scene.update_tracer(ray_p, ray_v, _rec);

                    // draw rays : (let commented for descent efficiency)
                    /*glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                    glBegin(GL_LINES);
                        glVertex3f(ray_p.x, ray_p.y, ray_p.z);
                        glVertex3f(ray_p.x + 10 * ray_v.x, ray_p.y + 10 * ray_v.y, ray_p.z + 10 * ray_v.z);
                    glEnd();*/
                            
                    _render.at(x).at(y) = color;
                }
            }
        }

        
        G3Xhmat   _Md = g3x_Identity();

        double _theta;
        double _phi;
        double _focus;
        double _dist;
        int    _rec;

        G3Xpoint  _target;

    private:
        Scene&  _scene;

        std::array<std::array<G3Xcolor, Res_Col>, Res_Row> _render;
};
