//
//  material.h
//  Assignment3
//
//  Created by Pamela Martinez on 6/9/13.
//
//

#ifndef __Assignment3__material__
#define __Assignment3__material__

#include <iostream>
using namespace std;
#include "st.h"

class material
{
public:
    
    material();
    void cleanup();
    
    bool is_valid(void) const;
    
    bool has_Kd(void)     { return Kd_is_set_;     }
    bool has_Ka(void)     { return Ka_is_set_;     }
    bool has_Ks(void)     { return Ks_is_set_;     }
    bool has_Tr(void)     { return Tr_is_set_;     }
    bool has_map_Kd(void) { return map_Kd_is_set_; }
    
    
    void set_Kd( float r, float g, float b );
    void set_Ka( float r, float g, float b );
    void set_Ks( float r, float g, float b );
    void set_Tr( float t );
    void set_map_Kd( std::string _name, int _index_Kd );
    
    const STVector3& Kd( void ) const { return Kd_; }
    const STVector3& Ka( void ) const { return Ka_; }
    const STVector3& Ks( void ) const { return Ks_; }
    float  Tr( void ) const { return Tr_; }
    const std::string& map_Kd( void ) { return map_Kd_ ; }
    const int& map_Kd_index( void ) { return index_Kd_ ; }
    
    
private:
    
    STVector3 Kd_;                          bool Kd_is_set_; // diffuse
    STVector3 Ka_;                          bool Ka_is_set_; // ambient
    STVector3 Ks_;                          bool Ks_is_set_; // specular
    float Tr_;                              bool Tr_is_set_; // transperency
    
    string map_Kd_; int index_Kd_; bool map_Kd_is_set_; // Texture
    
};


#endif /* defined(__Assignment3__material__) */
