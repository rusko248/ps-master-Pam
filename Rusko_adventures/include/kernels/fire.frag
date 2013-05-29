#version 120

uniform sampler2D texture;
varying vec4 texCoord;
 
void main(void) {
    vec3 N;
    N.xy = gl_PointCoord* 2.0 - vec2(1.0);
    float mag = dot(N.xy, N.xy);
    if(mag > 1.0)
     discard; // kill pixels outside circle

    gl_FragColor = texture2D(texture, texCoord.xy) * .5;
}