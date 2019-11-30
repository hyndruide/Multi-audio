
#include "include/engine.h"

Sound3D::Sound3D(Spk *u_fr,Spk *u_re, Spk *d_fr, Spk *d_re){
	Max_Size.x = 1;
	Max_Size.y = 1;
	Max_Size.z = 1;

	Speaker_3D[0].Speakers = u_fr;
	Speaker_3D[0].Spk_pos1.x = 0;
	Speaker_3D[0].Spk_pos1.y = 2.5;
	Speaker_3D[0].Spk_pos1.z = 3.12;

	Speaker_3D[0].Spk_pos2.x = 2.42;
	Speaker_3D[0].Spk_pos2.y = 2.5;
	Speaker_3D[0].Spk_pos2.z = 3.12;


	Speaker_3D[1].Speakers = u_re;
	Speaker_3D[1].Spk_pos1.x = 0;
	Speaker_3D[1].Spk_pos1.y = 2.5;
	Speaker_3D[1].Spk_pos1.z = 0;

	Speaker_3D[1].Spk_pos2.x = 2.42;
	Speaker_3D[1].Spk_pos2.y = 2.5;
	Speaker_3D[1].Spk_pos2.z = 0;


	Speaker_3D[2].Speakers = d_fr;
	Speaker_3D[2].Spk_pos1.x = 0;
	Speaker_3D[2].Spk_pos1.y = 0;
	Speaker_3D[2].Spk_pos1.z = 3.12;

	Speaker_3D[2].Spk_pos2.x = 2.42;
	Speaker_3D[2].Spk_pos2.y = 0;
	Speaker_3D[2].Spk_pos2.z = 3.12;


	Speaker_3D[3].Speakers = d_re;
	Speaker_3D[3].Spk_pos1.x = 0;
	Speaker_3D[3].Spk_pos1.y = 0;
	Speaker_3D[3].Spk_pos1.z = 0;

	Speaker_3D[3].Spk_pos2.x = 2.42;
	Speaker_3D[3].Spk_pos2.y = 0;
	Speaker_3D[3].Spk_pos2.z = 0;

	Point_Central.x = (Speaker_3D[0].Spk_pos1.x + Speaker_3D[1].Spk_pos1.x +Speaker_3D[2].Spk_pos1.x + Speaker_3D[3].Spk_pos1.x + Speaker_3D[0].Spk_pos2.x + Speaker_3D[1].Spk_pos2.x + Speaker_3D[2].Spk_pos2.x + Speaker_3D[3].Spk_pos2.x)/8;
	Point_Central.y = (Speaker_3D[0].Spk_pos1.y + Speaker_3D[1].Spk_pos1.y +Speaker_3D[2].Spk_pos1.y + Speaker_3D[3].Spk_pos1.y + Speaker_3D[0].Spk_pos2.y + Speaker_3D[1].Spk_pos2.y + Speaker_3D[2].Spk_pos2.y + Speaker_3D[3].Spk_pos2.y)/8;
	Point_Central.z = (Speaker_3D[0].Spk_pos1.z + Speaker_3D[1].Spk_pos1.z +Speaker_3D[2].Spk_pos1.z + Speaker_3D[3].Spk_pos1.z + Speaker_3D[0].Spk_pos2.z + Speaker_3D[1].Spk_pos2.z + Speaker_3D[2].Spk_pos2.z + Speaker_3D[3].Spk_pos2.z)/8;

	cout << "coord x : " << Point_Central.x << endl;
	cout << "coord y : " << Point_Central.y << endl;
	cout << "coord z : "<< Point_Central.z << endl;

}


Sound3D::~Sound3D(){

}


void Sound3D::tick(){
	SLEEP( time );

}


void Sound3D::set_clock(int t){
	time = t;


}


void Sound3D::init_Pos_spk(Vecteur3D up_front_left,Vecteur3D up_front_right,Vecteur3D up_rear_left,Vecteur3D up_rear_right,Vecteur3D down_front_left, Vecteur3D down_front_right, Vecteur3D down_rear_left , Vecteur3D down_rear_right){
	Speaker_3D[0].Spk_pos1 = up_front_left;

	Speaker_3D[0].Spk_pos2 = up_front_right;

	Speaker_3D[1].Spk_pos1 = up_rear_left;

	Speaker_3D[1].Spk_pos2 = up_rear_right;

	Speaker_3D[2].Spk_pos1 = down_front_left;

	Speaker_3D[2].Spk_pos2 = down_front_right;

	Speaker_3D[3].Spk_pos1 = down_rear_left;

	Speaker_3D[3].Spk_pos2 = down_rear_right;
	Point_Central.x = (Speaker_3D[0].Spk_pos1.x + Speaker_3D[1].Spk_pos1.x +Speaker_3D[2].Spk_pos1.x + Speaker_3D[3].Spk_pos1.x + Speaker_3D[0].Spk_pos2.x + Speaker_3D[1].Spk_pos2.x + Speaker_3D[2].Spk_pos2.x + Speaker_3D[3].Spk_pos2.x)/8;
	Point_Central.y = (Speaker_3D[0].Spk_pos1.y + Speaker_3D[1].Spk_pos1.y +Speaker_3D[2].Spk_pos1.y + Speaker_3D[3].Spk_pos1.y + Speaker_3D[0].Spk_pos2.y + Speaker_3D[1].Spk_pos2.y + Speaker_3D[2].Spk_pos2.y + Speaker_3D[3].Spk_pos2.y)/8;
	Point_Central.z = (Speaker_3D[0].Spk_pos1.z + Speaker_3D[1].Spk_pos1.z +Speaker_3D[2].Spk_pos1.z + Speaker_3D[3].Spk_pos1.z + Speaker_3D[0].Spk_pos2.z + Speaker_3D[1].Spk_pos2.z + Speaker_3D[2].Spk_pos2.z + Speaker_3D[3].Spk_pos2.z)/8;


}

/*
Pos.x = 1
Pos.y = 1
Pos.z = 1
*/

//Volume mini 0 max 100

double echelle (double value, double start1, double stop1, double start2, double stop2 ){
	if(value > 4.06202 ) return 0;
	else return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}


double Sound3D::Volume_spk(Vecteur3D spk,Vecteur3D Pos){
	double Distance ;
	Distance = Pos || spk ;
	if(2/(exp(pow(Distance,2))) >= 1) return 1;
	return 2/(exp(pow(Distance,2)));

}

void Sound3D::Position(Vecteur3D Pos){
	for(int i = 0; i < 4; i++){
		std::cout << "player [" << i<< "] spk 1 : " << Volume_spk(Speaker_3D[i].Spk_pos1,Pos) << std::endl;
		std::cout << "player [" << i<< "] spk 2 : " << Volume_spk(Speaker_3D[i].Spk_pos2,Pos) << std::endl;
		Speaker_3D[i].Speakers->set_Volume(SPK1,Volume_spk(Speaker_3D[i].Spk_pos1,Pos));
		Speaker_3D[i].Speakers->set_Volume(SPK2,Volume_spk(Speaker_3D[i].Spk_pos2,Pos));
	}

}


void Sound3D::Position(Vecteur3D Pos,int buffer_pose){
	for(int i = 0; i < 4; i++){
		//std::cout << "player [" << i<< "] spk 1 : " << Volume_spk(Speaker_3D[i].Spk_pos1,Pos) << std::endl;
		//std::cout << "player [" << i<< "] spk 2 : " << Volume_spk(Speaker_3D[i].Spk_pos2,Pos) << std::endl;
		Speaker_3D[i].Speakers->set_Volume(SPK1,Volume_spk(Speaker_3D[i].Spk_pos1,Pos),buffer_pose);
		Speaker_3D[i].Speakers->set_Volume(SPK2,Volume_spk(Speaker_3D[i].Spk_pos2,Pos),buffer_pose);
	}

}

void Sound3D::Deplacement(Vecteur3D Start,Vecteur3D End,double timemilis,int buffer_pose){
	double Distance =Start || End;
	//std::cout << " Distance "<< Distance << std::endl;
	double Vitesse = Distance / (timemilis/time);
	int i=0;
	while (road[i].Vitesse != 0) i++; 
	road[i].Direction.x = (End.x-Start.x) / (abs(End.x-Start.x)==0?1:abs(End.x-Start.x)) ;
	// std::cout << " direc x : "<< road[i].Direction.x << std::endl;
	road[i].Direction.y = (End.y-Start.y) / (abs(End.y-Start.y)==0?1:abs(End.y-Start.y)) ;
	// std::cout << " direc y : "<< road[i].Direction.y << std::endl;
	road[i].Direction.z = (End.z-Start.z) / (abs(End.z-Start.z)==0?1:abs(End.z-Start.z)) ;
	// std::cout << " direc z : "<< road[i].Direction.z << std::endl;
	// std::cout << " Vitesse "<< Vitesse << std::endl;
	road[i].Vitesse = Vitesse;
	road[i].Start = Start;
	road[i].End = End;
	road[i].buffer = buffer_pose;
	//std::cout << " ajout de deplacement en i : "<< i << std::endl;

}

void Sound3D::Clear_road(){
	for (int i = 0; i < 400; i++)
	{
		road[i].Vitesse = 0;
	}
}

void Sound3D::effet_dopler(Vecteur3D pos,Vecteur3D dir, double vitesse, int buffer){
	double posx ;
	double posy ;
	double posz; 
	double depace,value ;
	float pitch;
	posx = (Point_Central.x-pos.x)==0?1:(Point_Central.x-pos.x);
	posy = (Point_Central.y-pos.y)==0?1:(Point_Central.y-pos.y);
	posz = (Point_Central.z-pos.z)==0?1:(Point_Central.z-pos.z);

	depace =(posx*posy*posz)/(abs(posx*posy*posz));
	value = (dir.x==0?1:dir.x)*(dir.y==0?1:dir.y)*(dir.z==0?1:dir.z);
	if(depace==value){
		pitch = 1*14.4/(14.4-vitesse);
	}
	else{
		pitch = 1*14.4/(14.4+vitesse);
	}
	for(int i = 0; i < 4; i++){
		Speaker_3D[i].Speakers->set_Pitch(pitch,buffer);
	}


}


Spk* Sound3D::Speakers(int i){
	return Speaker_3D[i].Speakers;
}

void Sound3D::load_Spk(AudioFile<double> *newsound,string desc){
	Speaker_3D[0].Speakers->Add_buffer(newsound,BOTH,desc);
	Speaker_3D[1].Speakers->Add_buffer(newsound,BOTH,desc);
	Speaker_3D[2].Speakers->Add_buffer(newsound,BOTH,desc);
	Speaker_3D[3].Speakers->Add_buffer(newsound,BOTH,desc);
}

void Sound3D::Set_general_volume(double i){
	Speaker_3D[0].Speakers->set_Volume(BOTH,i);
	Speaker_3D[1].Speakers->set_Volume(BOTH,i);
	Speaker_3D[2].Speakers->set_Volume(BOTH,i);
	Speaker_3D[3].Speakers->set_Volume(BOTH,i);
}

void Sound3D::Start_buff(int buf){
	Speaker_3D[0].Speakers->start_sound_buffer(buf);
	Speaker_3D[1].Speakers->start_sound_buffer(buf);
	Speaker_3D[2].Speakers->start_sound_buffer(buf);
	Speaker_3D[3].Speakers->start_sound_buffer(buf);
}

void Sound3D::Start_buff(int buf,float* pose){
	Vecteur3D posi;
	posi.x = pose[0];
	posi.y = pose[1];
	posi.z = pose[2];
	Start_buff(buf);
	Position(posi,buf);
}


void Sound3D::Stop_buff(int buf){
	Speaker_3D[0].Speakers->stop_sound_buffer(buf);
	Speaker_3D[1].Speakers->stop_sound_buffer(buf);
	Speaker_3D[2].Speakers->stop_sound_buffer(buf);
	Speaker_3D[3].Speakers->stop_sound_buffer(buf);
}

void Sound3D::NoLoop_buff(int buf){
	Speaker_3D[0].Speakers->NoLoop_buffer(buf);
	Speaker_3D[1].Speakers->NoLoop_buffer(buf);
	Speaker_3D[2].Speakers->NoLoop_buffer(buf);
	Speaker_3D[3].Speakers->NoLoop_buffer(buf);
}


void Sound3D::Loop_buff(int buf){
	Speaker_3D[0].Speakers->Loop_buffer(buf);
	Speaker_3D[1].Speakers->Loop_buffer(buf);
	Speaker_3D[2].Speakers->Loop_buffer(buf);
	Speaker_3D[3].Speakers->Loop_buffer(buf);
}

void Sound3D::Action(){
	int i=0;
	double posx ;
	double posy ;
	double posz; 
	double Distance ;
	while(1){

		i=0;
		
		while (road[i].Vitesse == 0){
			//cout << road[i].Vitesse << endl;
			i++;
			if(i>400) break;
		} 
		if(i<400){
			//cout << "road : " << i << "buffer : " << road[i].buffer << endl;
			Start_buff(road[i].buffer);
			posx = abs(road[i].End.x-road[i].Start.x);
			posy = abs(road[i].End.y-road[i].Start.y);
			posz = abs(road[i].End.z-road[i].Start.z);
			Distance =sqrt( (posx*posx) + (posy*posy) + (posz*posz));
	//std::cout << "i : "<< i << " Distance : " << Distance << " Distance y : " << posy << " Vitesse : " << road[i].Vitesse << std::endl;
			if (Distance >= road[i].Vitesse){
				if (posx >= road[i].Vitesse) {
					road[i].Start.x += road[i].Direction.x * road[i].Vitesse;
				}

				if (posy >= road[i].Vitesse) {
					road[i].Start.y += road[i].Direction.y * road[i].Vitesse;
				}

				if (posz >= road[i].Vitesse) {
					road[i].Start.z += road[i].Direction.z * road[i].Vitesse;
				}


				Position(road[i].Start,road[i].buffer);
				effet_dopler(road[i].Start,road[i].Direction,road[i].Vitesse, road[i].buffer);


			}
			else {
				road[i].Vitesse = 0;
				Stop_buff(road[i].buffer);
			}
		}
		tick();
	}

}

void Sound3D::Process(){

	std::thread first (&Sound3D::Action,this);
}

json Sound3D::Status_buffer(){
	json j;
	for (int i=0;i<4;i++){
		for(int u=0;u<MAXBUFF;u++){
			if(!Speaker_3D[i].Speakers->Buf[u].isempty){
				j[std::to_string(i)][std::to_string(u)]["n_S"] = Speaker_3D[i].Speakers->Buf[u].num_Samples;
				j[std::to_string(i)][std::to_string(u)]["Out"] = Speaker_3D[i].Speakers->Buf[u].Sortie;
				j[std::to_string(i)][std::to_string(u)]["St"] = Speaker_3D[i].Speakers->Buf[u].State;
				j[std::to_string(i)][std::to_string(u)]["Pit"] = Speaker_3D[i].Speakers->Buf[u].Pitch;
				j[std::to_string(i)][std::to_string(u)]["loop"] = Speaker_3D[i].Speakers->Buf[u].loop;
				j[std::to_string(i)][std::to_string(u)]["L"] = Speaker_3D[i].Speakers->Buf[u].vol[0];
				j[std::to_string(i)][std::to_string(u)]["R"] = Speaker_3D[i].Speakers->Buf[u].vol[1];
				j[std::to_string(i)][std::to_string(u)]["desc"] = Speaker_3D[i].Speakers->Buf[u].description;
				j[std::to_string(i)][std::to_string(u)]["fr"] = Speaker_3D[i].Speakers->Buf[u].Frame;
			}
		}
	}
	//std::cout << std::setw(4) << j << std::endl;
	return j;
}

int Sound3D::input_proc(char* buffer){
	json j;
	std::string s;
	Vecteur3D st,st_once;
	Vecteur3D end;

	s += buffer;

	st.x = 0.5;
	st.y = -4;
	st.z = 0.5;

	st_once.x = 0.5;
	st_once.y = 0.5;
	st_once.z = 0.5;

	end.x = 0.5;
	end.y = 5;
	end.z = 0.5;

	try
	{
        // parsing input with a syntax error 
		j= json::parse(s);
		


		if(j.size()==1) return 1;
		else{
			std::cout << s << std::endl;
			float pos[3];
			Vecteur3D Start,End;
			int A= j[0].get<int>(), B = j[1].get<int>();
			std::string C = j[2].get<std::string>();
			double D = j[3].get<double>();
			std::cout << std::setw(4) << j << std::endl;


			switch ( C[0] )
			{
				case 'L':
				Speaker_3D[A].Speakers->Buf[B].vol[0] = D;
				break;

				case 'R':
				Speaker_3D[A].Speakers->Buf[B].vol[1] = D;
				break;

				case 'M':
				
				if (A < 0){
					
					Deplacement(st_once,end,2000,int(D));
					for(int l = 1; l < B; l++){
						std::cout << "ca descend !!" << '\n';
						Deplacement(st,end,4000,int(D));
					}
				}
				//ca monte ! 
				else if (A > 0){ 
					Deplacement(st_once,st,2000,int(D));
					for(int l = 1; l < B; l++){
						Deplacement(end,st,4000,int(D));
						std::cout << "ca monte !!" << '\n';
					}
				}
				break;

				
				case 'P':
				if(j[4].is_array()){

					pos[0] = j[4][0].get<float>();
					pos[1] = j[4][1].get<float>();
					pos[2] = j[4][2].get<float>();
				}
				else if(j[4].is_string()){
					if(j[4]=="center"){
						pos[0] = Point_Central.x;
						pos[1] = Point_Central.y;
						pos[2] = Point_Central.z;
					}
				}
				
				if(int(D) == 1) NoLoop_buff(B);
				else Loop_buff(B);
				if (char(A) == 0xFF) {
					Stop_buff(B);
					Start_buff(B);
				}
				else {
					Stop_buff(B);
					Start_buff(B,pos);
				}
				break;

				case 'D':
				if(j[4].is_array()){

					Start.x = j[4][0].get<double>();
					Start.y = j[4][1].get<double>();
					Start.z = j[4][2].get<double>();
					End.x = j[4][3].get<double>();
					End.y = j[4][4].get<double>();
					End.z = j[4][5].get<double>();
				}
				Deplacement(Start,End,D,B);
				break;

				case 'S':
				Stop_buff(B);
				break;

				case 'O':
				std::cout << "stop le son"<< std::endl;
				Clear_road();
				Stop_buff(B);
				break;


			}

			return 0;
		}
	}
	catch (std::invalid_argument& e)
	{
        // output exception information
		//std::cout << "message: " << e.what() << '\n';
	}
	return 0;

}