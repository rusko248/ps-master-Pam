
uniform sampler2D DepthTexture;
uniform sampler2D ShadowTexture;

varying vec2 DepthTexCoord;
varying vec3 ShadowNear;
varying vec3 ShadowDir;

const vec3 shadowColor = vec3(0.0);

void main()
{
	float cameraDepth = texture2D(DepthTexture, DepthTexCoord).a;

	vec3 shadowPos = (cameraDepth * ShadowDir) + ShadowNear;
	float l = dot(shadowPos.yz, shadowPos.yz);
	float d = shadowPos.x;

	float k = texture2D(ShadowTexture, vec2(l, d)).r;

	gl_FragColor = vec4(shadowColor, k);
}