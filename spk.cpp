
#include "include/spk.h"



Spk::Spk(){

}

Spk::~Spk(){

}

int Spk::PreProcess(int num_Buffer){
	return 0;
	
}



void Spk::channel_Out_Proc(){
	int ju =0; 
	Spk1_Out = 0;
	Spk2_Out = 0;
	//std::cout << "thread buf "<<  std::endl;
	for(int num_Buffer = 0; num_Buffer < MAXBUFF; num_Buffer++ ){

		if(Buf[num_Buffer].State == STOP){
			Buf[num_Buffer].Frame =0;

		}	
		if(Buf[num_Buffer].State == START){
			PreProcess(num_Buffer);
			Buf[num_Buffer].Frame+=Buf[num_Buffer].Pitch;

			if( Buf[num_Buffer].Frame + Buf[num_Buffer].Pitch > Buf[num_Buffer].num_Samples  ) {
				// std::cout << "feofei" << std::endl;
				if (!Buf[num_Buffer].loop) {
					Buf[num_Buffer].State = STOP;
				}
				else {
					Buf[num_Buffer].Frame = 1;
				}
			}

			ju++;

			
			if(Buf[num_Buffer].num_Canal == 1){
				
				Spk1_Out += Buf[num_Buffer].audio->samples[CANAL1][Buf[num_Buffer].Frame] * Buf[num_Buffer].vol[SPK1] * ( (Buf[num_Buffer].Sortie==SPK1 || Buf[num_Buffer].Sortie==BOTH) ? 1 : 0 );
				Spk2_Out += Buf[num_Buffer].audio->samples[CANAL1][Buf[num_Buffer].Frame] * Buf[num_Buffer].vol[SPK2] * ( (Buf[num_Buffer].Sortie==SPK2 || Buf[num_Buffer].Sortie==BOTH) ? 1 : 0 );

			}

			else if(Buf[num_Buffer].num_Canal == 2){
				
				Spk1_Out += Buf[num_Buffer].audio->samples[CANAL1][Buf[num_Buffer].Frame] * Buf[num_Buffer].vol[SPK1] * ( (Buf[num_Buffer].Sortie==SPK1 || Buf[num_Buffer].Sortie==BOTH) ? 1 : 0 );
				Spk2_Out += Buf[num_Buffer].audio->samples[CANAL2][Buf[num_Buffer].Frame] * Buf[num_Buffer].vol[SPK2] * ( (Buf[num_Buffer].Sortie==SPK2 || Buf[num_Buffer].Sortie==BOTH) ? 1 : 0 );

			}


		}

	}
	if( ju == 0){
		Spk1_Out = 0;
		Spk1_Out = 0;
	}
	Spk1_Out = Spk1_Out * Spk_Volume[SPK1];
	Spk2_Out = Spk2_Out * Spk_Volume[SPK2];


}



double Spk::Out1(){
	return Spk1_Out;
}

double Spk::Out2(){
	return Spk2_Out	;
}


void Spk::set_Pitch(float pit,int buffer){
	Buf[buffer].Pitch = pit;
	Buf[buffer].num_Samples = Buf[buffer].num_Samples * Buf[buffer].Pitch;

}


void Spk::set_Volume(int speaker,double Volume){
	if (speaker == BOTH){
		Spk_Volume[SPK1] = Volume;
		Spk_Volume[SPK2] = Volume;

	} 
	else Spk_Volume[speaker] = Volume;

}

void Spk::set_Volume(int speaker,double Volume,int buffer){
	if (speaker == BOTH){
		if(Volume == 0){		
			Buf[buffer].vol[SPK1] =  Volume;
			Buf[buffer].vol[SPK2] =  Volume;
		} else{
			Buf[buffer].vol[SPK1] = Volume;
			Buf[buffer].vol[SPK2] =  Volume;
		}
	} 
	else Buf[buffer].vol[speaker] = Volume;
	
}


int Spk::Add_buffer(AudioFile<double> *newsound, int Speaker,string desc){
	int i=0;
	
	while(!Buf[i].isempty){
		i++;
		if (i >= MAXBUFF) break;
	}
	if (i >= MAXBUFF){
		// std::cout << "pas de buf dispo" << std::endl;
		return NOPE;
	}
	Buf[i].audio = newsound;
	Buf[i].num_Samples = newsound->getNumSamplesPerChannel();
	Buf[i].num_Canal = newsound->getNumChannels();
	Buf[i].State = PAUSE;
	Buf[i].vol[SPK1] = 1;
	Buf[i].vol[SPK2] = 1;
	Buf[i].Sortie = Speaker;
	Buf[i].description = desc;
	Buf[i].isempty = false;

	// std::cout << "ajouter sur buffer : " << i <<  std::endl;
	return i;


}

void Spk::start_sound_buffer(int buffer){
	Buf[buffer].State = START;
}


void Spk::start_sound_buffer_one_way(int buffer,int L,int R){
	Buf[buffer].vol[SPK1] = L;
	Buf[buffer].vol[SPK2] = R;
	Buf[buffer].State = START;
}



void Spk::stop_sound_buffer(int buffer){
	Buf[buffer].vol[SPK1] = 1;
	Buf[buffer].vol[SPK2] = 1;
	Buf[buffer].State = STOP;
}



void Spk::NoLoop_buffer(int buffer){
	Buf[buffer].loop = false;
}


void Spk::Loop_buffer(int buffer){
	Buf[buffer].loop = true;
}

// int fx_fade(int fade,int buf,int speaker = BOTH,double time = 1){
// 	master->Buf[buf].buf_time_fx = time;
// 	master->Buf[buf].buf_fx = FADEIN;
// 	master->Buf[buf].balance = speaker;

// }

int Spk::isPlay(){
	if (Spk_State == STOP) return 1;
	else return 0;
}










