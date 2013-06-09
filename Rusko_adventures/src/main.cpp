#include <cstdio>
//#include "Framework.h"
#include "Graphics.h"
//#include "Renderable.h"
#include <pthread.h>
#include "time.h"
using namespace std;

/*Threading for updates of world and particles*/

const int thread_num=3;
ParticleManager *particles;

//Torch Fire
ParticleManager *torchParticles;

Sound *systemSound;

float xpos = -1.0f;
float zpos = -1.0f;
float ypos = -1.0f;

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
            usleep(50000);
        }
    }else if(tid == 1){ //other Particle updating
        while(true){
            particles->update();
            usleep(50000);

        }
    }else{
        systemSound->update();
        usleep(200000);
    }
	return 0;
}

void createThreads(){
    pthread_t threads[thread_num];
	for(int tid=0;tid<thread_num;tid++){
        ////create threads, return 0 if the thread is correctly created
        
		int rc=pthread_create(&threads[tid],NULL,threaded_update,(void*)tid);
		if(rc){std::cerr<<"cannot create thread "<<tid<<std::endl;}
	}

    GraphicsMainLoop();
    
    for(int tid=0;tid<thread_num;tid++){
        pthread_join(threads[tid], NULL);
	}
}

int main(int argc, char** argv) {
    
    particles = new ParticleManager(10000);
    torchParticles = new ParticleManager(2500);
    //Sound
    systemSound = new Sound();
    
    GraphicsInit(argc, argv);
    createThreads();
	return 0;
}