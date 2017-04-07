#include <iostream>
#include <kdl/kdl.hpp>
#include <kdl/tree.hpp>
#include <kdl/chain.hpp>
#include <math.h>
#include <stdlib.h>

using namespace std;
int main(int argc,char *argv[]){
	KDL::Chain chain;
	double pi = M_PI;
	double a1 = 2, a2 = 1, teta1, teta2, d3;
	if(argc == 4) 	// Wprowadzamy wartości z wiersza poleceń
	{ 
		teta1 =  strtol(argv[1], NULL, 10);
		teta2 = strtol(argv[2], NULL, 10);
		d3 = strtol(argv[3], NULL, 10);
	}
	else // Domyślne wartości
	{
		teta1 = pi/3;
		teta2 = pi/8;
		d3 = 2;
	}

	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ),KDL::Frame::DH(a1, 0, 0, teta1)));
	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ),KDL::Frame::DH(a2, pi, 0, teta2)));
	chain.addSegment(KDL::Segment(KDL::Joint(KDL::Joint::RotZ),KDL::Frame::DH(0, 0, d3, 0)));

	double zlacze[3], koncowka[3];
	double roll, pitch, yaw; // Szukane parametry
	for (int i = 0; i < 3; ++i)
		{
			for(int j = 0; j < 3; j++)
			{
				zlacze[j] = chain.getSegment(i).getJoint().JointAxis().data[j];
				koncowka[j] = chain.getSegment(i).getFrameToTip().p.data[j];
			}

		chain.getSegment(i).getFrameToTip().M.GetRPY(roll, pitch, yaw);

		cout << "Wezel " << i << " rpy : " << zlacze[0] << ", " << zlacze[1] << ", " <<zlacze[2] << endl;
		cout << "Koncowka " << i << " rpy : " << roll << ", " << pitch << ", " << yaw << endl;
		cout << "Koncowka " << i << " xyz : " << koncowka[0] << ", " << koncowka[1] << ", " << koncowka[2] << endl;
		}

	return 0;
}
