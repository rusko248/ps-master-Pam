// DEFERRED RENDERING with G-BUFFER
// --------------------------------
// A. Tamplin
// 5/26/13
//---------------------------------

uniform sampler2D bufferToDraw;
uniform int screenWidth;
uniform int screenHeight;
uniform float near;
uniform float far;
uniform bool doDepth;

//Makes depth values linear (i.e. inverse of the perpective projection)
float DepthToLinearZ(float dVal)
{
	return (far*near) / (far-(dVal*(far-near)));
}

void main()
{
   //normalize coord
	vec2 coord = (gl_FragCoord).xy;
	coord.x = coord.x / float(screenWidth);
	coord.y = coord.y / float(screenHeight);
	
	//set color
	if(doDepth) {
	   float depth = DepthToLinearZ(texture2D(bufferToDraw, coord).r);
	   gl_FragColor = vec4(depth/far, depth/far, depth/far, 1.0);
	}
	else {
	   gl_FragColor = texture2D(bufferToDraw, coord);
	}
}