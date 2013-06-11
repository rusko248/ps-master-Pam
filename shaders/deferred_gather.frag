// DEFERRED RENDERING
// -----------------------------------
//  stores G-Buffer values


uniform sampler2D texture;
uniform int useTexture;

varying vec3 normal;
varying vec2 texPos;

varying vec3 modelPos;    // fragment position in model space		added
varying vec3 lightSource; // light source position in model space	added

void main()
{
   vec3 materialColor;
   vec3 materialDiff;
   vec3 materialSpec;

   vec3 packedNormal = (normalize(normal) + 1.0)*0.5; //compress normal
   gl_FragData[0] = vec4(packedNormal,1.0);

   if (useTexture == 1) {
      materialColor = texture2D(texture, texPos).xyz;
   } else {
      materialColor = vec3(1.0, 1.0, 1.0);
   }

	// added Phong shading

   vec3 C = vec3(0.0, 0.0, 0.0); // camera position

   vec3 ambientColor  = gl_LightModel.ambient.rgb;
   vec3 diffuseColor  = gl_LightSource[0].diffuse.rgb;
   vec3 specularColor = gl_LightSource[0].specular.rgb;

   vec3 Nm = normalize(normal);
   vec3 Lm = normalize(lightSource - modelPos);
   vec3 Rm = normalize(reflect(-Lm, Nm));
   vec3 amb = ambientColor * gl_FrontMaterial.ambient.rgb;
   vec3 diff = diffuseColor * gl_FrontMaterial.diffuse.rgb * max(dot(Lm, Nm), 0.0);
   vec3 spec = specularColor * gl_FrontMaterial.specular.rgb * pow(max(dot(Rm, Nm), 0.0), gl_FrontMaterial.shininess);
   vec3 Phong = amb;
   Phong += diff + spec;
//   if (useTexture == 1) Phong *= materialColor;
   Phong *= materialColor;
   gl_FragData[1] = vec4(Phong, 1.0);
}