#include "dataLandMark.h"

DataLandMark::DataLandMark(int ID, int IDLandMark, double x, double y, double z)
:   ID_(ID),
    IDLandMark_(IDLandMark),
    x_(x),
    y_(y),
    z_(z)
{}

DataLandMark::~DataLandMark()
{}

void DataLandMark::ShowLandMark()
{
    cout<<"LandMark ID          :"<<ID_<<endl;
    cout<<"LandMark IDLandMark  :"<<IDLandMark_<<endl;
    cout<<"LandMark x           :"<<x_<<endl;
    cout<<"LandMark y           :"<<y_<<endl;
    cout<<"LandMark z           :"<<z_<<endl;
}
