#include <math.h> 

class Vecteur3D 
{
public:
	double x=0;
	double y=0;
	double z=0;
	Vecteur3D();
	Vecteur3D(double _x, double _y, double _z);
	~Vecteur3D();
	double distanceVecteur(Vecteur3D End);

};

double operator||(Vecteur3D a,Vecteur3D b);