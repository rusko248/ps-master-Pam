// DEFERRED RENDERING
// -----------------------------------
//  renders a directional light source
// -----------------------------------
// author: Ryan Schmitt
// date: 3-7-11

//G-Buffer data
uniform sampler2D normals;
uniform sampler2D depths;
uniform sampler2D colors;

//Util vars
uniform int screenWidth;
uniform int screenHeight;

//Lighting vars
uniform vec3 lightDirection; //light direction in world space
uniform vec3 ambientLightColor;
uniform vec3 diffuseLightColor;

void main()
{
   //normalize coord
	vec2 coord = (gl_FragCoord).xy;
	coord.x = coord.x / float(screenWidth);
	coord.y = coord.y / float(screenHeight);

        if (texture2D(depths, coord).r == 1.0) discard;	// Assume no object rendered

	//Data lookups
	vec4 n = (texture2D(normals, coord)*2.0)-1.0;
	n.a = 1.0;
	vec4 c = texture2D(colors, coord);
	
	//Lighting Calcs
	vec4 ambient = c * vec4(ambientLightColor, 1.0);
	float diffuseModifier = max(dot(n.xyz, normalize(lightDirection)*(-1.0)), 0.0);
	vec4 diffuse = c * diffuseModifier * vec4(diffuseLightColor, 1.0);
	
	//Set the color
	gl_FragColor = diffuse + ambient;
}