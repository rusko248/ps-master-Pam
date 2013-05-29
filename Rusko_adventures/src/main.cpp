#include <cstdio>
#include "Framework.h"
#include "Graphics.h"
#include "Renderable.h"

using namespace std;

int main(int argc, char** argv) {

	GraphicsInit(argc, argv);
	GraphicsMainLoop();
	
	return 0;
}
