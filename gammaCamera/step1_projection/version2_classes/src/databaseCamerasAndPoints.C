#include "databaseCamerasAndPoints.h"
DatabaseCamerasAndPoints::DatabaseCamerasAndPoints()
{
    cout<<"Hello , this is DataCameraAndPoints"<<endl;    
}

DatabaseCamerasAndPoints::~DatabaseCamerasAndPoints()
{}

void DatabaseCamerasAndPoints::addACamera_NORotation_translationInversed(int IDCamera, double translation[3], double focalLength)
{
    // parameters
    double para[9];
    // angle-axis rotation
    para[0] = 0;
    para[1] = 0;
    para[2] = 0;
    // Translation inversed
    // translation : -1*I*Wrold_P_camORG
    para[3] = -1.*translation[0];
    para[4] = -1.*translation[1];
    para[5] = -1.*translation[2];
    // focal length
    para[6] = focalLength;
    // radius distortion
    para[7] = 0;
    para[8] = 0;

    /*
    // debug
    cout<<"translation: "<<para[3]/mm<<"    "<<para[4]/mm<<"    "<<para[5]/mm<<"    "<<endl;
    cout<<"focal length: "<<para[6]/mm<<endl;
    */

    int ID = cameras.size();
    DataCamera cam(ID,IDCamera,para); 
    cameras.push_back(cam);
}

void DatabaseCamerasAndPoints::addACamera_NORotation(int IDCamera, double translation[3], double focalLength)
{
    // parameters
    double para[9];
    // angle-axis rotation
    para[0] = 0;
    para[1] = 0;
    para[2] = 0;
    // translation : Wrold_P_camORG
    para[3] = 1.*translation[0];
    para[4] = 1.*translation[1];
    para[5] = 1.*translation[2];
    // focal length
    para[6] = focalLength;
    // radius distortion
    para[7] = 0;
    para[8] = 0;

    /*
    // debug
    cout<<"translation: "<<para[3]/mm<<"    "<<para[4]/mm<<"    "<<para[5]/mm<<"    "<<endl;
    cout<<"focal length: "<<para[6]/mm<<endl;
    */

    int ID = cameras.size();
    DataCamera cam(ID,IDCamera,para); 
    cameras.push_back(cam);
}
void DatabaseCamerasAndPoints::addALandMark(int IDLandMark, double x, double y, double z)
{
    int ID = landMarks.size();
    DataLandMark lm(ID,IDLandMark,x,y,z);
    landMarks.push_back(lm);
}

void DatabaseCamerasAndPoints::addAnObservation(int IDCamera, int IDLandMark, double x, double y)
{
    int ID = observations.size();
    DataObservation ob(ID,IDCamera,IDLandMark,x,y);
    observations.push_back(ob);
}


void DatabaseCamerasAndPoints::write(string filename)
{
    ofstream file(filename.c_str());

    // part 1 : numbers
    int numCameras = cameras.size();
    int numLandMarks = landMarks.size();
    int numObservations = observations.size();
    file<<numCameras<<"   "<<numLandMarks<<"    "<<numObservations<<endl;


    // part 2 : observations
    for(int i=0;i<observations.size();i++)
    {
        int IDCamera    = observations[i].IDCamera_;
        int IDLandMark  = observations[i].IDLandMark_;
        double x = observations[i].x_;
        double y = observations[i].y_;
        file<<IDCamera<<"   "<<IDLandMark<<"    "<<x<<" "<<y<<endl;
    }

    // part 3 : cameras
    for(int i=0;i<cameras.size();i++)
    {
        //cout<<"CameraID: "<<cameras[i].IDCamera_<<endl;
        for(int j=0;j<9;j++) file<<cameras[i].para_[j]<<endl;
    }

    // part 4 : landmarks
    for(int i=0;i<landMarks.size();i++)
    {
        int IDLandMark  = landMarks[i].IDLandMark_;
        double x = landMarks[i].x_;
        double y = landMarks[i].y_;
        double z = landMarks[i].z_;
        //file<<IDLandMark<<"    "<<x<<" "<<y<<"  "<<z<<endl;
        file<<x<<endl;
        file<<y<<endl;
        file<<z<<endl;
    }
    file.close();
}

void DatabaseCamerasAndPoints::ShowCameras()
{
    cout<<"DatabaseCamerasAndPoints:: Show Cameras"<<endl;
    for(int i=0;i<cameras.size();i++)
    {
        int ID = cameras[i].IDCamera_;
        double rot1 = cameras[i].para_[0];
        double rot2 = cameras[i].para_[1];
        double rot3 = cameras[i].para_[2];
        double tran1 = cameras[i].para_[3];
        double tran2 = cameras[i].para_[4];
        double tran3 = cameras[i].para_[5];
        double focalLength = cameras[i].para_[6];
        double distortion1 = cameras[i].para_[7];
        double distortion2 = cameras[i].para_[8];
        cout<<"Camera ID: "<<ID<<", Rotation "<<rot1<<" "<<rot2<<"  "<<rot3<<", translation "<<tran1<<"    "<<tran2<<"    "<<tran3<<", focalLength "<<focalLength<<", distortion "<<distortion1<<"   "<<distortion2<<endl;
    }
}

void DatabaseCamerasAndPoints::ShowLandMarkers()
{
    cout<<"DatabaseCamerasAndPoints:: Show LandMarkers"<<endl;
    for(int i=0;i<landMarks.size();i++)
    {
        int IDLandMark  = landMarks[i].IDLandMark_;
        double x = landMarks[i].x_;
        double y = landMarks[i].y_;
        double z = landMarks[i].z_;
        cout<<"LandMarker ID "<<IDLandMark<<", position "<<x<<" "<<y<<" "<<z<<endl;
    }
}
