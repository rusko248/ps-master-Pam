// -----------------------------------
//  stores G-Buffer values
// -----------------------------------


varying vec3 normal;

void main()
{
   vec3 packedNormal = (normalize(normal) + 1.0)*0.5; //compress normal
   gl_FragData[0] = vec4(packedNormal,1.0);
   gl_FragData[1] = gl_FrontMaterial.diffuse;
}