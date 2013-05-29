#version 120

uniform sampler2D tex;
uniform sampler2D tex2;
uniform mat4 PrevMatrix;
varying vec2 vTexCoord;

uniform sampler2D texture;
varying vec4 texCoord;
 
void main(void) {
    vec3 N;
    N.xy = gl_PointCoord* 2.0 - vec2(1.0);
    float mag = dot(N.xy, N.xy);
    if(mag > 1.0)
     discard; // kill pixels outside circle

    vec4 color = texture2D(tex, vTexCoord);
    vec4 zOverW = texture2D(tex2, vTexCoord);
    // H is the viewport position at this pixel in the range -1 to 1.
    vec4 H = vec4(vTexCoord.x * 2 - 1, (1 - vTexCoord.y) * 2 - 1, zOverW.g, 1);
    // Transform by the view-projection inverse.
    vec4 D = gl_ModelViewProjectionMatrixInverse * H;
    // Divide by w to get the world position.
    vec4 worldPos = D / vec4(D.w);
    
    // Current viewport position
    vec4 currentPos = H;
    // Use the world position, and transform by the previous view-projection matrix.
    vec4 previousPos = PrevMatrix * worldPos;
    // Convert to nonhomogeneous points [-1,1] by dividing by w.
    previousPos = previousPos / vec4(previousPos.w);
    // Use this frame's position and last frame's to compute the pixel velocity.
    vec2 velocity = vec2(currentPos.xy - previousPos.xy)/2.0;
    //velocity = (velocity + 1.0 ) / 2.0;
    
    gl_FragColor = vec4(velocity.x, velocity.y, color.g, 1.0);

}