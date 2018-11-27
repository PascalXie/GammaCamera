#ifndef DATACAMERA_H 
#define DATACAMERA_H 1
#include <iostream>
using namespace std;

class DataCamera
{
    public:
        DataCamera(int ID, int IDCamera_);
        DataCamera(int ID, int IDCamera_, double para[9]);
        ~DataCamera();
    public:
        void ShowCamera();
    public:
        int ID_;
        int IDCamera_;
        double para_[9];

        // translation
        double Wrold_P_camORG_[3];
        double cam_P_WorldORG_[3];
};

#endif

