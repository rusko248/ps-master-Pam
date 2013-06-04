// ---------------------------
//  does some transformations 
// ---------------------------


varying vec4 lpos;
varying vec4 pos;

void main()
{
   lpos = gl_ModelViewMatrix * vec4(0.0, 0.0, 0.0, 1.0); //construct light's position in view space!
   //pos = gl_ModelViewMatrix * gl_Vertex;
	
	pos.xyz /= pos.w;

   gl_Position = ftransform();
}

//maybe we need to do something with dividing by w