// DEFERRED RENDERING
// -----------------------------------
//  stores G-Buffer values
// -----------------------------------
// author: A. Tamplin
// date: 6/7/13

uniform sampler2D texture;
uniform int useTexture;

varying vec3 normal;
varying vec2 texPos;

void main()
{
   vec3 packedNormal = (normalize(normal) + 1.0)*0.5; //compress normal
   gl_FragData[0] = vec4(packedNormal,1.0);
   if (useTexture == 1) gl_FragData[1] = texture2D(texture, texPos);
   else                 gl_FragData[1] = gl_FrontMaterial.diffuse;
}