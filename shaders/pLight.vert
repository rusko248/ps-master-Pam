// DEFERRED RENDERING
// -----------------------------------
//  does some transformations for us!
// -----------------------------------
// author: A. Tamplin
// date: 6/4/13

uniform vec3 LightPosition;
varying vec4 lightPos;
varying vec3 ecPosition;  // Eye Coordinate Position
//varying vec3 ecPosition3; // Eye Coordinate Position in 3 space
varying vec3 lightVec;
varying vec3 viewVec;

void main()
{
//   lightPos = gl_ModelViewMatrix * vec4(0.0, 0.0, 0.0, 1.0); //construct light's position in view space!
   lightPos = gl_ModelViewMatrix * vec4(LightPosition, 1.0); //construct light's position in view space!
   ecPosition  = vec3(gl_ModelViewMatrix * gl_Vertex);
//   ecPosition3 = (vec3(ecPosition)) / ecPosition.w;
   lightVec = normalize(LightPosition - ecPosition);
//   viewVec = normalize(-ecPosition);
   viewVec = vec3(0.0, 0.0, 1.0);
   gl_Position = ftransform(); //gotta do this!
}