attribute vec2 pos;
varying vec4 texCoord;
uniform float pointRadius;  // point size in world space
uniform float point_size;   // scale to calculate size in pixels
 
void main(void) {
    vec4 wpos = vec4(gl_Vertex.xyz, 1.0);
    gl_Position = gl_ModelViewProjectionMatrix * wpos;
    texCoord = vec4(pos.xy / 2.0 + 0.5, 1, 1);
    
    //gl_PointSize = point_size;

    // calculate window-space point size
    vec4 eyeSpacePos = gl_ModelViewMatrix * wpos;
    float dist = length(eyeSpacePos.xyz);
    gl_PointSize = pointRadius * (point_size / dist);
}
