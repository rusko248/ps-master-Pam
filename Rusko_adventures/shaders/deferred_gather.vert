// -----------------------------------
//  does some transformations
// -----------------------------------


varying vec3 normal;

void main()
{   
   //Same old, same old
   normal = gl_NormalMatrix * gl_Normal;
   gl_Position = ftransform();
}