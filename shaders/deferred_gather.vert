// DEFERRED RENDERING
// -----------------------------------
//  does some transformations for us!
// -----------------------------------


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

   vec4 modelPos4 = gl_ModelViewMatrix * gl_Vertex;
//   modelPos = (gl_ModelViewMatrix * gl_Vertex).xyz;	// added
//   modelPos = modelPos4.xyz / modelPos4.w;
   modelPos = modelPos4.xyz;
//   lightSource = (gl_ModelViewProjectionMatrix * gl_LightSource[0].position).xyz;	// added
//   lightSource = (gl_ModelViewMatrix * gl_LightSource[0].position).xyz;	// added
   lightSource = gl_LightSource[0].position).xyz;

   gl_Position = ftransform(); //gotta do this!
}