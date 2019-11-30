/******************************************/
/*
  playraw.cpp
  by Gary P. Scavone, 2007

  Play a specified raw file.  It is necessary
  that the file be of the same data format as
  defined below.
*/
/******************************************/

#include "AudioFile.h"
#include <math.h> 
#include <string>
#include <nlohmann/json.hpp>
//#include "./Vecteur3d.h"

// for convenience
using json = nlohmann::json;
using namespace std; 

#if defined( WIN32 )
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif




// FX
#define NOFX 0
#define FADEIN 2
#define FADEOUT 4


// Replace sound
#define REPLACE 8
#define REPLACEFD 16


// State Audio
#define START 1
#define PAUSE 2
#define STOP 0

//maximum buffer 
#define MAXBUFF 32

//Caneaux de sortie

#define CANAL1 0
#define CANAL2 1

#define NOPE 255


//Pan
#define SPK1 0
#define SPK2 1
#define BOTH 2

//

#define MONO false
#define STEREO true


	struct buffer_Audio
{
	AudioFile<double> *audio;
	unsigned int num_Samples =0;

	int num_Canal = 0;
	int Sortie = BOTH;
	char State = STOP;
	float Pitch = 1.0f;
	bool loop= true; 
	bool isempty = true;
	double vol[2] ={1,1};
	string description  = "none";
	float Frame = 0;
	
/*	int Fx = NOFX;
	int time = 0;
	int Fx_Balance;*/

};






class Spk
{

public:
	Spk();
	~Spk();
	//output( void *outputBuffer, void * /*inputBuffer*/, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *data )
	
	int Add_buffer(AudioFile<double> *newsound, int Speaker = BOTH,string desc = "new sound");

	int PreProcess(int num_Buffer);
	void channel_Out_Proc(void);
	void spk_pan(int );
	void print_stat();
	void set_Volume(int speaker,double Volume);
	void set_Volume(int speaker,double Volume,int buffer);
	void start_sound_buffer(int buffer);
	void start_sound_buffer_one_way(int buffer,int L,int R);
	void stop_sound_buffer(int buffer);
	void NoLoop_buffer(int buffer);
	void Loop_buffer(int buffer);
	double Out1();
	double Out2();
	void set_Pitch(float pit,int buffer);
	int isPlay();
	buffer_Audio Buf[MAXBUFF];
/*
	void fx_fade(int fade,int buf,int speaker = BOTH,double time = 1);
	int fx_replace(AudioFile<double> *newsound)
	int fx_replace_fade(double time = 1)

	*/

private:
    int Spk_State = START;
	double Spk_Volume[2] ={1,1};
	//buffer_Audio Buf[MAXBUFF];
	double Spk1_Out=0,Spk2_Out=0;

	
};


