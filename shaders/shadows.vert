
uniform mat3 WorldToShadow;
uniform vec3 SphereOrigin;

uniform vec3 CameraPos;
uniform vec3 CameraDir;
uniform float DepthNear;
uniform float DepthFar;

varying vec2 DepthTexCoord;
varying vec3 ShadowNear;
varying vec3 ShadowDir;

void main()
{

	gl_Position = ftransform();
	gl_Position.xyz /= gl_Position.w;
	gl_Position.w = 1.0;

	DepthTexCoord = gl_Position.xy * 0.5 + 0.5;
	
	vec3 offset = (gl_Vertex.xyz / gl_Vertex.w) - CameraPos;
	
	float z = -dot(offset, CameraDir);
	
	vec3 shadowOffsetNear = offset * DepthNear / z;
	vec3 shadowOffsetFar = offset * DepthFar / z;
	
	vec3 worldPositionNear = CameraPos + shadowOffsetNear;
	vec3 worldPositionFar = CameraPos + shadowOffsetFar;

	vec3 ShadowFar = WorldToShadow * (worldPositionFar - SphereOrigin);
	ShadowNear = WorldToShadow * (worldPositionNear - SphereOrigin);
	ShadowDir = ShadowFar - ShadowNear;
	
}