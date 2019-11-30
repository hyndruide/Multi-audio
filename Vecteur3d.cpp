#include "include/Vecteur3d.h"

Vecteur3D::Vecteur3D(double _x, double _y, double _z){
	x=_x;
	y=_y;
	z=_z;
}

Vecteur3D::Vecteur3D(){

}


Vecteur3D::~Vecteur3D(){
	
}

double Vecteur3D::distanceVecteur(Vecteur3D End){
	double posx = End.x-x;
	double posy = End.y-y;
	double posz = End.z-z;
	return sqrt( (posx*posx) + (posy*posy) + (posz*posz));

}

// double Vecteur3D::DirectionVecteur(Vecteur End){

// 	posx = (End.x-x)==0?1:(End.x-x);
// 	posy = (End.y-y)==0?1:(End.y-y);
// 	posz = (End.z-z)==0?1:(End.z-z);

// 	depace =(posx*posy*posz)/(abs(posx*posy*posz));
// 	return (dir.x==0?1:dir.x)*(dir.y==0?1:dir.y)*(dir.z==0?1:dir.z);
// }

double operator||(Vecteur3D a,Vecteur3D b)
{
    
    return a.distanceVecteur(b);
}