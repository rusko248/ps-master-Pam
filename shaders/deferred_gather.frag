// DEFERRED RENDERING
// -----------------------------------
//  stores G-Buffer values
// -----------------------------------
// author: A. Tamplin
// date: 6/9/13

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
//      gl_FragData[1] = texture2D(texture, texPos);
//      return;
      materialColor = texture2D(texture, texPos).xyz;
      materialDiff  = texture2D(texture, texPos).xyz;
      materialSpec  = texture2D(texture, texPos).xyz;
   } else {			// added
      materialColor = gl_FrontMaterial.ambient.xyz;
      materialDiff  = gl_FrontMaterial.diffuse.xyz;
      materialSpec  = gl_FrontMaterial.specular.xyz;
   }

	// added Phong shading

   vec3 C = vec3(0.0, 0.0, 0.0); // camera position

   vec3 ambientColor  = gl_LightSource[0].ambient.xyz;
   vec3 diffuseColor  = gl_LightSource[0].diffuse.xyz;
   vec3 specularColor = gl_LightSource[0].specular.xyz;

//   vec3 materialColor = gl_FrontMaterial.ambient.xyz;
//   vec3 materialDiff  = gl_FrontMaterial.diffuse.xyz;
//   vec3 materialSpec  = gl_FrontMaterial.specular.xyz;
   float shininess    = gl_FrontMaterial.shininess;

   vec3 Nm = normalize(normal);
   vec3 Lm = normalize(lightSource - modelPos);
   vec3 Rm = normalize(reflect(-Lm, Nm));
//   vec3 V  = normalize(C - modelPos);
   vec3 V  = normalize(lightSource - modelPos);
   vec3 Phong = ambientColor * materialColor;
	Phong += diffuseColor * materialDiff * max(dot(Lm, Nm), 0.0);
//	Phong += specularColor * materialSpec * pow(max(dot(Rm, V), 0.0), shininess);
	Phong += specularColor * materialSpec * pow(max(dot(Rm, Nm), 0.0), shininess);
   gl_FragData[1] = vec4(Phong, 1.0);
}