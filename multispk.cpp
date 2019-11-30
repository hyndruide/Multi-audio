/******************************************/
/*
  playraw.cpp
  by Gary P. Scavone, 2007

  Play a specified raw file.  It is necessary
  that the file be of the same data format as
  defined below.
*/
/******************************************/

#include "include/RtAudio.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "include/AudioFile.h"
#include <thread>
#include "include/engine.h"
#include <unistd.h> 
#include <fcntl.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <fstream>
using namespace std;


#define PORT 3216
AudioFile<double> Music;
AudioFile<double> fx1;
AudioFile<double> fx2;
AudioFile<double> fx3;
AudioFile<double> fx4;
AudioFile<double> fx5;
AudioFile<double> fx6;
AudioFile<double> fx7;


AudioFile<double> note_c;
AudioFile<double> note_d;
AudioFile<double> note_e;
AudioFile<double> note_f;
AudioFile<double> note_g;
AudioFile<double> note_a;
AudioFile<double> note_b;
AudioFile<double> note_c2;

AudioFile<double> pack[32];

/*
typedef char  MY_TYPE;
#define FORMAT RTAUDIO_SINT8
#define SCALE  127.0
*/
/*
typedef signed short  MY_TYPE;
#define FORMAT RTAUDIO_SINT16
#define SCALE  32767.0


typedef S24 MY_TYPE;
#define FORMAT RTAUDIO_SINT24
#define SCALE  8388607.0

typedef signed int  MY_TYPE;
#define FORMAT RTAUDIO_SINT32
#define SCALE  2147483647.0

typedef float  MY_TYPE;
#define FORMAT RTAUDIO_FLOAT32
#define SCALE  1.0;
*/
typedef double  MY_TYPE;
#define FORMAT RTAUDIO_FLOAT64
#define SCALE  1.0;




// Platform-dependent sleep routines.


string audiolist[32];





// Interleaved buffers
int output( void *outputBuffer, void * /*inputBuffer*/, unsigned int nBufferFrames, 
double streamTime, RtAudioStreamStatus status, void *data )
{
	Spk *oData = (Spk *) data;
	double *buffer = (double *) outputBuffer;

	for (unsigned int i = 0; i < nBufferFrames; i++)
	{
		oData->channel_Out_Proc();
		//std::cout << oData->Out1() << std::endl;
		*buffer++ = oData->Out1();
		*buffer++ = oData->Out2();
	}
	return oData->isPlay();

}




int main( int argc, char *argv[] )
{

	int server_fd, new_socket /*, valread*/; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	
	for(int i = 0; i< 32;i++){
		audiolist[i] = "\0";
	}





	ifstream is_file ("./config.conf");
	if (is_file.is_open())
	{
		std::string line;
		while( std::getline(is_file, line) )
		{
			std::istringstream is_line(line);
			std::string key;
			if( std::getline(is_line, key, '=') )
			{
				std::string value;
				if( std::getline(is_line, value) ) {
					if(key == "audio"){
						int aud =0;
						size_t pos;
						string token;
						string delimiter = ";";
						while ((pos = value.find(delimiter)) != std::string::npos) {
							token = value.substr(0, pos);
							value.erase(0, pos + delimiter.length());
							audiolist[aud]=token;
							aud++;
						}
						audiolist[aud] = value;

					}
				}

				//cout << "clef : "<< key<< " value : " << value << endl;
			}
		}
	}

	Spk Player1; 
	Spk Player2;
	Spk Player3;
	Spk Player4;

	Sound3D Engine(&Player1,&Player4,&Player2,&Player3);

	
	// char *file;
	int fs1 = 44100, offset = 0;
	unsigned int bufferFrames = 512;
	

  // minimal command-line checking
	// file = argv[1];
	// if ( argc < 2) return 0;
	//std::cout << "\nPlaying raw file "<< file <<" (buffer frames = " << bufferFrames << ")." << std::endl;
	RtAudio dac1;
	if ( dac1.getDeviceCount() < 1 ) {
		std::cout << "\nNo audio devices found!\n";
		exit( 0 );
	}




	RtAudio::StreamParameters uprear;
	uprear.deviceId = 3;
	uprear.nChannels = 2;
	uprear.firstChannel = offset;

	RtAudio dac2;
	RtAudio::StreamParameters downrear;
	downrear.deviceId = 5;
	downrear.nChannels = 2;
	downrear.firstChannel = offset;


	RtAudio dac3;
	RtAudio::StreamParameters upfront;
	upfront.deviceId = 4;
	upfront.nChannels = 2;
	upfront.firstChannel = offset;

	RtAudio dac4;
	RtAudio::StreamParameters downfront;
	downfront.deviceId = 6;
	downfront.nChannels = 2;
	downfront.firstChannel = offset;
	int au=0;
	while(audiolist[au]!="\0"){

			if (audiolist[au].find(".wav") == std::string::npos){
				cout << "not good file" << endl;
				break;
			}
			else{
		cout << "loading ... " << audiolist[au] << endl;

		pack[au].load(audiolist[au]);
		cout << "loaded "<< endl;
		au++;
	}
	}



	Vecteur3D st;
	Vecteur3D end;


	st.x = 0.5;
	st.y = -4;
	st.z = 0.5;

	end.x = 0.5;
	end.y = 5;
	end.z = 0.5;

	//Sound3D::Sound3D(Spk *u_fr,Spk *u_re, Spk *d_fr, Spk *d_re)

	try {
		dac1.openStream( &upfront, NULL,  FORMAT, fs1, &bufferFrames, &output, (void *)Engine.Speakers(0)); // up-front
		dac2.openStream( &downfront, NULL, FORMAT, fs1, &bufferFrames, &output, (void *)Engine.Speakers(2)); // down-front
		dac3.openStream( &downrear, NULL, FORMAT, fs1, &bufferFrames, &output, (void *)Engine.Speakers(3)); // Down-rear
		dac4.openStream( &uprear, NULL, FORMAT, fs1, &bufferFrames, &output, (void *)Engine.Speakers(1)); // up-rear

		dac1.startStream();
		dac2.startStream();
		dac3.startStream();
		dac4.startStream();


		au =0;
		while(audiolist[au]!="\0"){

			if (audiolist[au].find(".wav") == std::string::npos){
				cout << "can't load" << endl;
				break;
			}
			else{	
				//cout << "loading ... " << audiolist[au] << endl;	
				Engine.load_Spk(&pack[au],audiolist[au]);
				//cout << "loaded "<< endl;
			}
			au++;
		}


		




		//t.join();
		cout << "Creating socket file descriptor\n" ;
		if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
		{ 
			perror("socket failed"); 
			exit(EXIT_FAILURE); 
		} 

		cout << " Forcefully attaching socket to the port 3216\n"  ;
		if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
			&opt, sizeof(opt))) 
		{ 
			perror("setsockopt"); 
			exit(EXIT_FAILURE); 
		} 
		address.sin_family = AF_INET; 
		address.sin_addr.s_addr = INADDR_ANY; 
		address.sin_port = htons( PORT ); 

		cout << "Forcefully attaching socket to the port 3216 \n" ;
		if (bind(server_fd, (struct sockaddr *)&address,  
			sizeof(address))<0) 
		{ 
			perror("bind failed"); 
			exit(EXIT_FAILURE); 
		} 

		

		if (listen(server_fd, 3) < 0) 
		{ 
			perror("listen"); 
			exit(EXIT_FAILURE); 
		} 



	}
	catch ( RtAudioError& e ) {
		std::cout << '\n' << e.getMessage() << '\n' << std::endl;
	}

	

	bool alive = true;

	char buffer[2048] = {0}; 
	cout << "listen... \n" ;
	std::thread t(&Sound3D::Action, &Engine);
	while ( alive==true ) {

		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
			(socklen_t*)&addrlen))<0) 
		{ 
			perror("accept"); 
			exit(EXIT_FAILURE); 
		} 

		while ( alive==true ) {
			

			
			if ((read( new_socket , buffer, 1024)) == 0){
				cout << "socket deco\n" ;
				close(new_socket);
				break;
			}else{

				if (buffer[0]!=0){ 
						//cout << buffer << endl ;
					if(Engine.input_proc(buffer) == 1){
						json j = Engine.Status_buffer();
						std::string info = j.dump();
						int n = info.length(); 
						char info_char[n + 1]; 
						strcpy(info_char, info.c_str());
						send(new_socket , info_char , strlen(info_char) , 0 ); 
					}
				}

				
				
			}

		}

		 // wake every 100 ms to check if we're done
		if ( dac1.isStreamRunning() == false && dac2.isStreamRunning() == false && dac3.isStreamRunning() == false && dac4.isStreamRunning() == false ) break;
	}


	

	return 0;
}
