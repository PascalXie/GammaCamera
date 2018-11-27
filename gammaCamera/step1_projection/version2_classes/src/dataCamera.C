#include "dataCamera.h"

DataCamera::DataCamera(int ID, int IDCamera)
:   ID_(ID),
    IDCamera_(IDCamera)
{
    for(int i=0;i<9;i++)    
    {
        para_[i] = 0;
    }
    
}

DataCamera::DataCamera(int ID, int IDCamera, double para[9])
:   ID_(ID),
    IDCamera_(IDCamera)
{
    for(int i=0;i<9;i++)    
    {
        para_[i] = para[i];
    }
    
}

DataCamera::~DataCamera()
{}

void DataCamera::ShowCamera()
{
    cout<<"Camera ID:"<<ID_<<", ";
    cout<<"IDCamera:"<<IDCamera_<<", ";
    cout<<"para[0]:"<<para_[0]<<", ";
    cout<<"para[1]:"<<para_[1]<<", ";
    cout<<"para[2]:"<<para_[2]<<", ";
    cout<<"para[3]:"<<para_[3]<<", ";
    cout<<"para[4]:"<<para_[4]<<", ";
    cout<<"para[5]:"<<para_[5]<<", ";
    cout<<"para[6]:"<<para_[6]<<", ";
    cout<<"para[7]:"<<para_[7]<<", ";
    cout<<"para[8]:"<<para_[8]<<endl;
}
