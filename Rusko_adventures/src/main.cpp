#include <cstdio>
//#include "Framework.h"
#include "Graphics.h"
//#include "Renderable.h"
#include <pthread.h>

using namespace std;

/*Threading for updates of world and particles*/

const int thread_num=2;
ParticleManager *particles;

//Torch Fire
ParticleManager *torchParticles;

float xpos = 0.0f;
float zpos = 0.0f;
float ypos = 0.0f;

pthread_mutex_t mutex;

////function called by each thread
void* threaded_update(void* tid_input)
{
    ////get the thread id
	int tid=*((int*)(&tid_input));
    if(tid == 0){//torch updating
        while(true){
            torchParticles->resetPos(0, vector3(xpos, ypos, zpos));
            torchParticles->update();
            //sleep(50);
        }
    }else if(tid == 1){ //other Particle updating
        while(true){
            particles->update();
            //sleep(1);
        }
    }else{

        cout << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << "start glut" << endl;
        int argc = 1;
        char *argv[1];
        argv[0] = "a";
    }
	return 0;
}

void createThreads(){
    pthread_t threads[thread_num];
	for(int tid=0;tid<thread_num;tid++){
        ////create threads, return 0 if the thread is correctly created
        cout << tid << endl;
        
		int rc=pthread_create(&threads[tid],NULL,threaded_update,(void*)tid);
		if(rc){std::cerr<<"cannot create thread "<<tid<<std::endl;}
	}

    //cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    GraphicsMainLoop();
    for(int tid=0;tid<thread_num;tid++){
        pthread_join(threads[tid], NULL);
	}
    cout << "Reaching this point" << endl;
}

int main(int argc, char** argv) {
    
    particles = new ParticleManager(20000);
    torchParticles = new ParticleManager(3000);
    GraphicsInit(argc, argv);
    createThreads();
    //GraphicsInit(argc, argv);
    //cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    //GraphicsMainLoop();
    //GraphicsMainLoop();
	return 0;
}