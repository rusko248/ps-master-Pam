// DEFERRED RENDERING
// -----------------------------------
//  does some transformations for us!
// -----------------------------------
// author: A. Tamplin
// date: 6/9/13

varying vec3 normal;
varying vec2 texPos;

varying vec3 modelPos;		// added
varying vec3 lightSource;	// added

void main()
{   
   //Same old, same old
   normal = gl_NormalMatrix * gl_Normal;
    
   // Copy the standard OpenGL texture coordinate to the output.
   texPos = gl_MultiTexCoord0.st;

   modelPos = (gl_ModelViewMatrix * gl_Vertex).xyz;	// added
   lightSource = (gl_ModelViewProjectionMatrix * gl_LightSource[0].position).xyz;	// added

   gl_Position = ftransform(); //gotta do this!
}