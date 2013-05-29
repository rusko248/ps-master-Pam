// displacement.vert

/*
 This GLSL vertex shader performs displacement mapping
 using an analytical displacement function.
 */

// This 'varying' vertex output can be read as an input
// by a fragment shader that makes the same declaration.
varying vec2 texPos;
varying vec3 modelPos;
varying vec3 lightSource;
varying vec3 normal;

varying float displacement;
float pi = 3.1459;
float delta = .000001;

float h(float x, float y){
    //return 0.1*cos(3.0*2.0*pi*x)*cos(3.0*2.0*pi*y);
    return 0.1*sin(pow(x*5.0,2.0) + pow(y*5.0,2.0));
}

void main()
{
    // Tell the fragment shader we have done vertex displacement
    displacement = 1.0;
    
	normal = gl_Normal.xyz;
	modelPos = gl_Vertex.xyz;
    
    // Copy the standard OpenGL texture coordinate to the output.
    texPos = gl_MultiTexCoord0.xy;
    
	/* CS 148 TODO: Modify 'modelPos' and 'normal' using your displacment function */
    
     float u = texPos.x;
     float v = texPos.y;
     float height = h(u, v);
     modelPos = modelPos + height * normal;
     float uDif = (h(u+delta,v)-h(u,v))/delta;
     float vDif = (h(u,v+delta)-h(u,v))/delta;
     vec3 T1 = normalize(vec3(1.0,uDif,0.0));
     vec3 T2 = normalize(vec3(0.0,-vDif,-1.0));
     normal = cross(T1, T2);
     
    // Render the shape using modified position.
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix *  vec4(modelPos,1.0);
    
    // we may need this in the fragment shader...
    modelPos = (gl_ModelViewMatrix * vec4(modelPos,1.0)).xyz;
    
	// send the normal to the fragment shader
	normal = (gl_NormalMatrix * normal);
    
    // pass the light source position to the fragment shader
    lightSource = gl_LightSource[0].position.xyz;
}
