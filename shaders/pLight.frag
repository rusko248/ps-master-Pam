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

//Makes depth values linear (i.e. inverse of the perpective projection)
float DepthToLinearZ(float dVal)
{
	return float(far*near) / (float(far)-(dVal*float(far-near)));
}

void main()
{
    //normalize coord
//   Vec2 coord = (gl_FragCoord).xy;
    vec2 coord = (gl_FragCoord).xy;
    coord.x = coord.x / float(screenWidth);
    coord.y = coord.y / float(screenHeight);
	
    //Data lookups
    vec4 color = texture2D(colors, coord);
    vec3 normal = normalize(vec3((texture2D(normals, coord) * 2.0) - 1.0));

    // Compute vector from surface to light position
    vec3 VP = vec3(LightPosition) - ecPosition;

    // Compute distance between surface and light position
    float d = length(VP);

    // Normalize the vector from surface to light position
    VP = normalize(VP);

    vec3 halfVector = normalize(VP + viewVec);

    float nDotVP = max(0.0, dot(normal, VP));
    float nDotHV = max(0.0, dot(normal, halfVector));

//    float attenuation = 1.0;

    // Compute attenuation
   float attenuation = 1.0 / (LightAttenuation[0] +
                               LightAttenuation[1] * d +
                               LightAttenuation[2] * d * d);

//float attenuation = (1.0 - (d / radius)) * (1.0 / (d * d));

    vec4 diffuse = vec4(diffuseLightColor, 1.0) * nDotVP * attenuation;
	
   //Set the color
   gl_FragColor = diffuse;
}
