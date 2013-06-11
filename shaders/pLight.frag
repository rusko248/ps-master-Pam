// DEFERRED RENDERING
// -----------------------------------
//  renders a point light source
// -----------------------------------
// A. Tamplin
// 6/4/13
// -----------------------------------

//from vert shader
uniform vec3 LightPosition;
uniform vec3 LightAttenuation;
varying vec4 pos;  // location of fragment in view space
varying vec4 lightPos; // light position in view space
varying vec3 ecPosition;  // Eye Coordinate Position
varying vec3 viewVec;
//varying float attenuation;

//G-Buffer data
uniform sampler2D normals;
uniform sampler2D depths;
uniform sampler2D colors;

//Util vars
uniform int screenWidth;
uniform int screenHeight;
uniform float near;
uniform float far;

//Lighting vars
uniform float radius;
uniform vec3 diffuseLightColor;


void main()
{
  

    //normalize coord
    vec2 coord = (gl_FragCoord).xy;
    coord.x = (2.0 * coord.x - float(screenWidth)) / float(screenWidth);
    coord.y = (2.0 * coord.y - float (screenHeight)) / float(screenHeight);
	
 	


    float attenuation = 1.0;


	vec2 torch=vec2(0.24, -0.02);

	vec2 lp = vec2(lightPos.x/lightPos.w,lightPos.y/lightPos.w);
	//float d = length(coord-torch);
	float d = length(coord-lp);


   if (d >= 0.8) {
      attenuation = 0.0;
   } else {
      float attFactor = d/.8;
      attFactor = d / (1.0 - attFactor * attFactor);
      attFactor = attFactor / 0.8 + 1.0;
      attenuation = 1.0 / (attFactor * attFactor);
      //attenuation = 1.0;	// for testing
   }

	//attenuation = 1.0;


//    vec4 diffuse = vec4(diffuseLightColor, 1.0) * nDotVP * attenuation;
    vec4 diffuse = vec4(diffuseLightColor * attenuation, 1.0);

	//vec4 diffuse = vec4( attenuation, 0.0, 0.0, 1.0);

	
   //Set the color
   gl_FragColor = diffuse;

	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
