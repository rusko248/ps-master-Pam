#version 120

uniform sampler2D texture;
uniform sampler2D texDepthBuffer;
varying vec4 texCoord;
 
void main(void) {
    float sceneDepth = texture2D( texDepthBuffer, texCoord.xy).r;
    //float currDepth = gl_FragDepth;
    //float currDepth = gl_FragCoord.z;
    //if(currDepth > sceneDepth) discard;
    vec3 N;
    N.xy = gl_PointCoord* 2.0 - vec2(1.0);
    float mag = dot(N.xy, N.xy);
    if(mag > 1.0)
     discard; // kill pixels outside circle
    //gl_FragDepth = currDepth;
    gl_FragColor = texture2D(texture, texCoord.xy) * .5;
}