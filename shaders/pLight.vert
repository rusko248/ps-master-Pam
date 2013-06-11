// DEFERRED RENDERING
// -----------------------------------
//  point light vertex shader
// -----------------------------------

uniform vec3 LightPosition;
varying vec4 lightPos;
varying vec3 ecPosition;  // Eye Coordinate Position
//varying vec3 ecPosition3; // Eye Coordinate Position in 3 space
varying vec3 lightVec;
varying vec3 viewVec;
varying float attenuation;

uniform float radius;

void main()
{
   //lightPos = gl_ModelViewMatrix * vec4(LightPosition, 1.0); //construct light's position in view space!
   
	lightPos = vec4(LightPosition.xyz, 1.0);
	//ecPosition  = vec3(gl_ModelViewMatrix * gl_Vertex);
	//ecPosition = gl_Vertex.xyz;
   lightVec = normalize(LightPosition - ecPosition);

   // Compute distance between surface and light position

   //vec4 origin  = gl_ModelViewMatrix * vec4(0.0, 0.0, 0.0, 1.0);
   //vec4 point = gl_Vertex - origin;

	//vec3 point = lightPos.xyz - ecPosition;


	lightPos = gl_ModelViewProjectionMatrix*vec4(0.0,0.0,0.0,1.0);

	//gl_Position = ftransform();
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; //gotta do this!

}