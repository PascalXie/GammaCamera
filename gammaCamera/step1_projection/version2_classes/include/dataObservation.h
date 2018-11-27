#ifndef DATAOBSERVATION_H
#define DATAOBSERVATION_H 1

#include <iostream>

using namespace std;

class DataObservation
{
    public:
        DataObservation(int ID, int IDCamera, int IDLandMark, double x, double y);
        ~DataObservation(); 
    public:
        void ShowObservation();
    
    public:
        int ID_;
        int IDCamera_;
        int IDLandMark_;
        double x_;
        double y_;
};

#endif
