#include "Scene.hpp"

using namespace std;


void Scene::display()
{
    //g3x_SetBkgCol(0.5);
    for (auto& obj : _objs)
    { // objects
        obj->display(_ambiance, _diffusion, _spec, _shine);
    }
}

G3Xcolor Scene::update_tracer(const G3Xpoint& ray_org, 
                              const G3Xvector& ray_v, 
                              u_int rec)
{
    if (rec == 0)
    {
        return G3Xk;
    }

    _light = g3x_GetLight()->pos;
    // final values :
    G3Xcolor  final_color { G3Xk };
    double    min_dist = 100000.;
    G3Xpoint  final_inter_p;
    G3Xvector final_inter_v;
    G3Xvector final_inter_norm;

    for (auto& obj : _objs)
    {
        G3Xpoint  inter_p;
        G3Xvector inter_v;
        G3Xpoint  obj_ray_p = g3x_ProdHMatPoint (obj->_Mi, ray_org);
		G3Xvector obj_ray_v = g3x_ProdHMatVector(obj->_Mi, ray_v);
        g3x_Normalize(&obj_ray_v);

        if (obj->inter(obj_ray_p, obj_ray_v, &inter_p, &inter_v))
        {            
            g3x_Normalize(&inter_v);
            double d_cur = g3x_SqrDist(g3x_ProdHMatPoint(obj->_Md, inter_p), ray_org);
            if (d_cur < min_dist)
            { // update final values
                final_inter_p    = g3x_ProdHMatPoint  (obj->_Md, inter_p);
                final_inter_norm = g3x_ProdHMatVector (obj->_Mn, inter_v);
                g3x_Normalize(&final_inter_norm);
                final_inter_v = obj_ray_v;
                g3x_Normalize(&final_inter_v);
                min_dist      = d_cur;
                final_color   = obj->_color;
            }
        }
    }

    // LIGHT HANDLING
    auto light_vec = g3x_SetVect(final_inter_p, _light);
    g3x_Normalize(&light_vec);
    auto final_cpy = final_color;

    compute_ambiance (&final_color);
    compute_diffusion(&final_color, final_cpy, final_inter_norm, light_vec);
    compute_halo     (&final_color, G3Xw     , final_inter_norm, light_vec, final_inter_v );

    if (_shine == 0)
    {
        return final_color;
    }
    auto ur = reflect_ray(final_inter_norm, final_inter_v);
    auto color_reflect = update_tracer(final_inter_p, ur, rec - 1);
    
    compute_reflect(&final_color, color_reflect);

    return final_color;
}

void Scene::compute_ambiance(G3Xcolor* final_color)
{
    final_color->b *= _ambiance;
    final_color->r *= _ambiance;
    final_color->g *= _ambiance;
}

void Scene::compute_diffusion(G3Xcolor* final_color,
                              const G3Xcolor& flat_color,
                              const G3Xvector& inter_norm, 
                              const G3Xvector& inter_light)
{
    auto ps = g3x_ProdScal(inter_norm, inter_light);
    final_color->b += _diffusion * ps * flat_color.b;
    final_color->r += _diffusion * ps * flat_color.r;
    final_color->g += _diffusion * ps * flat_color.g;
    *final_color = ps < 0    ? G3Xk : *final_color;
    *final_color = ps > PI/2 ? G3Xk : *final_color;
}

void Scene::compute_halo(G3Xcolor* final_color,
                         const G3Xcolor& flat_color,
                         const G3Xvector& inter_norm, 
                         const G3Xvector& inter_light,
                         const G3Xvector& ray_v)
{
    auto ps = g3x_ProdScal(inter_norm, inter_light) * 2;
    G3Xvector wr { ps * inter_norm.x, ps * inter_norm.y, ps * inter_norm.z };
    wr = g3x_SubVect(wr, inter_light);
    g3x_Normalize(&wr);

    auto ps2 = -g3x_ProdScal(ray_v, wr);
    
    if (ps2 > 0 && ps2 < PI/2) {
        final_color->b += _spec * _shine * pow(ps2, 1./(1-_shine)) * flat_color.b;
        final_color->r += _spec * _shine * pow(ps2, 1./(1-_shine)) * flat_color.r;
        final_color->g += _spec * _shine * pow(ps2, 1./(1-_shine)) * flat_color.g;
    }
}

G3Xvector Scene::reflect_ray(const G3Xvector& inter_norm,
                             const G3Xvector& ray_v)
{
    auto ps = g3x_ProdScal(inter_norm, ray_v) * -2.;
    G3Xvector ur = { ps * inter_norm.x + ray_v.x, ps * inter_norm.y + ray_v.y, ps * inter_norm.z + ray_v.z };
    g3x_Normalize(&ur);
    return ur;
}

void Scene::compute_reflect(G3Xcolor* final_color,
                            const G3Xcolor& col_reflect)
{
    final_color->b += _spec * col_reflect.b;
    final_color->r += _spec * col_reflect.r;
    final_color->g += _spec * col_reflect.g;
}


void Scene::add(unique_ptr<Object> obj)
{
    _objs.emplace_back(std::move(obj));
}

void Scene::init_scene1()
{
    unique_ptr<Sphere> cir0 = make_unique<Sphere>(G3Xw);
    unique_ptr<Sphere> cir1 = make_unique<Sphere>(G3Xb);
	unique_ptr<Sphere> cir2 = make_unique<Sphere>(G3Xr);
	unique_ptr<Sphere> cir3 = make_unique<Sphere>(G3Xg);
	unique_ptr<Sphere> cir4 = make_unique<Sphere>(G3Xy);
	unique_ptr<Sphere> cir5 = make_unique<Sphere>(G3Xo);
	unique_ptr<Sphere> cir6 = make_unique<Sphere>(G3Xc);
    unique_ptr<Sphere> cir7 = make_unique<Sphere>(G3Xw);
    unique_ptr<Sphere> cir8 = make_unique<Sphere>(G3Xk);

    cir0->rescale(2., 2., 2.);
	cir1->translate( 2.5,  2.5, 0);
	cir2->translate(-2.5,  2.5, 0);
	cir3->translate( 2.5, -2.5, 0);
	cir4->translate(-2.5, -2.5, 0);
	cir5->translate( 0  ,  3.5, 0);
	cir6->translate( 3.5,  0  , 0);
    cir7->translate(-3.5,  0  , 0);
    cir8->translate( 0  , -3.5, 0);

    add(std::move(cir0));
	add(std::move(cir1));
	add(std::move(cir2));
    add(std::move(cir3));
    add(std::move(cir4));
    add(std::move(cir5));
    add(std::move(cir6));
    add(std::move(cir7));
    add(std::move(cir8));

    _light = G3Xpoint { 7, 7, 7 };
}

void Scene::init_scene2()
{
    unique_ptr<Sphere> cir0 = make_unique<Sphere>(G3Xw);
    unique_ptr<Sphere> cir1 = make_unique<Sphere>(G3Xb);

    cir0->rescale(2., 2., 2.);
	cir1->translate( 3,  3, 0);

    add(std::move(cir0));
	add(std::move(cir1));

    _light = G3Xpoint { 7, 7, 7 };
}

void Scene::init_scene3()
{
    unique_ptr<Cube> sq = make_unique<Cube>(G3Xr);

	//sq->translate( 3,  3, 0);

    add(std::move(sq));

    _light = G3Xpoint { 7, 7, 7 };
}