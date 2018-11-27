#ifndef DATALANDMARK_H 
#define DATALANDMARK_H 1
#include <iostream>
using namespace std;

class DataLandMark
{
    public:
        DataLandMark(int ID, int IDLandMark, double x, double y, double z);
        ~DataLandMark();
    public:
        void ShowLandMark();
    public:
        int ID_;
        int IDLandMark_;
        double x_,y_,z_;
};

#endif
