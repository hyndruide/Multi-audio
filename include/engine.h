#include "./Vecteur3d.h"
#include "./spk.h"
#include <thread>

struct Mouvement3D
{
	Vecteur3D Start;
	Vecteur3D End;
	Vecteur3D Direction;
	double Vitesse = 0;
	int buffer=0;

};

struct Spk3D
{
	Vecteur3D Spk_pos1,Spk_pos2 ;
	Spk *Speakers;
	
};


class Sound3D
{

public:
	Sound3D(Spk *u_fr,Spk *u_re, Spk *d_fr, Spk *d_re);
	~Sound3D();

	void init_Pos_spk(Vecteur3D up_front_left,Vecteur3D up_front_right,Vecteur3D up_rear_left,Vecteur3D up_rear_right,Vecteur3D down_front_left, Vecteur3D down_front_right, Vecteur3D down_rear_left , Vecteur3D down_rear_right);

	void Position(int buffer,Vecteur3D Postionz);
	void Position(Vecteur3D Pos);
	void Position(Vecteur3D Pos,int buffer_pose);
	void Deplacement(Vecteur3D Start,Vecteur3D End,double time,int buffer_pose);
	void effet_dopler(Vecteur3D pos, Vecteur3D dir, double vitesse, int buffer);

	void Action();
	void Set_general_volume(double i);
	void tick();
	void Start_buff(int buf);
	void Start_buff(int buf,float* pose);
	void Stop_buff(int buf);
	void Loop_buff(int buf);
	void NoLoop_buff(int buf);
	void set_clock(int t);
	void load_Spk(AudioFile<double> *newsound, string desc);
	void Clear_road();
	Spk* Speakers(int i);
	json Status_buffer();
	int input_proc(char* buffer);
	void Process();


private:
	int time = 40;
	Spk3D Speaker_3D[4];
	Vecteur3D position_general;
	Vecteur3D Point_Central;
	Vecteur3D Max_Size;
	double Volume_spk(Vecteur3D spk,Vecteur3D pos);
	Mouvement3D road[400];
	
};