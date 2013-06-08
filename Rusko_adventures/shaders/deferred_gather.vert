// DEFERRED RENDERING
// -----------------------------------
//  does some transformations for us!
// -----------------------------------
// author: Ryan Schmitt
// date: 3-7-11

varying vec3 normal;
varying vec2 texPos;

void main()
{   
   //Same old, same old
   normal = gl_NormalMatrix * gl_Normal;
    
   // Copy the standard OpenGL texture coordinate to the output.
   texPos = gl_MultiTexCoord0.st;

   gl_Position = ftransform(); //gotta do this!
}