#include "dataObservation.h"
#include "units.h"

DataObservation::DataObservation(int ID, int IDCamera, int IDLandMark, double x, double y)
:   ID_(ID),
    IDCamera_(IDCamera),
    IDLandMark_(IDLandMark),
    x_(x),
    y_(y)
{}

DataObservation::~DataObservation()
{}

void DataObservation::ShowObservation()
{
    cout<<"Observation ID           :"<<ID_<<endl;
    cout<<"Observation IDCamera     :"<<IDCamera_<<endl;
    cout<<"Observation IDLandMark   :"<<IDLandMark_<<endl;
    cout<<"Observation x            :"<<x_<<endl;
    cout<<"Observation y            :"<<y_<<endl;
}
