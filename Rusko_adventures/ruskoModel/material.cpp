//
//  material.cpp
//  Assignment3
//
//  Created by Pamela Martinez on 6/9/13.
//
//

#include "material.h"

material::material() {
    cleanup();
}

void material::cleanup()
{
    Kd_is_set_     = false;
    Ka_is_set_     = false;
    Ks_is_set_     = false;
    Tr_is_set_     = false;
    map_Kd_is_set_ = false;
}

bool material::is_valid(void) const
{ return Kd_is_set_ || Ka_is_set_ || Ks_is_set_ || Tr_is_set_; }



void material::set_Kd( float r, float g, float b )
{
    Kd_=STVector3(r,g,b);
    Kd_is_set_=true;
}

void material::set_Ka( float r, float g, float b )
{
    Ka_=STVector3(r,g,b);
    Ka_is_set_=true;
}

void material::set_Ks( float r, float g, float b )
{
    Ks_=STVector3(r,g,b);
    Ks_is_set_=true;
}

void material::set_Tr( float t )
{
    Tr_=t;
    Tr_is_set_=true;
}

void material::set_map_Kd( std::string _name, int _index_Kd )
{
    map_Kd_ = _name,
    index_Kd_ = _index_Kd;
    map_Kd_is_set_ = true;
};
