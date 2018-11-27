#include <iostream>
#include <fstream>
#include <time.h>

// openCV
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
// Eigen
#include <Eigen/Dense>

// camera
#include "camera.h"
// data 
#include "databaseCamerasAndPoints.h"
// Units
#include "units.h"

using namespace std;
using namespace cv;
using namespace Eigen;

int main(int argc, char** argv) 
{
    cout<<"Hello"<<endl;
    // output data
    DatabaseCamerasAndPoints data;

    //
    // step 3 : make source
    //
    double lenx = 2.*mm;
    double leny = 4.*mm;
    double lenz = 10*mm;
    double transz = 30*mm;

    vector<Vector3d> corners;

    corners.push_back(Vector3d( 1.*lenx/2., 1.*leny/2.,transz+0));
    corners.push_back(Vector3d(-1.*lenx/2., 1.*leny/2.,transz+0));
    corners.push_back(Vector3d(-1.*lenx/2.,-1.*leny/2.,transz+0));
    corners.push_back(Vector3d( 1.*lenx/2.,-1.*leny/2.,transz+0));
    corners.push_back(Vector3d( 1.*lenx/2., 1.*leny/2.,transz+lenz));
    corners.push_back(Vector3d(-1.*lenx/2., 1.*leny/2.,transz+lenz));
    corners.push_back(Vector3d(-1.*lenx/2.,-1.*leny/2.,transz+lenz));
    corners.push_back(Vector3d( 1.*lenx/2.,-1.*leny/2.,transz+lenz));

    for(int i=0;i<corners.size();i++)
    {
        //cout<<"LandMark "<<i<<": "<<corners[i].transpose()<<endl;
        data.addALandMark(i,corners[i](0,0),corners[i](1,0),corners[i](2,0));
    }
    //data.ShowLandMarkers();

    /*
    Camera cam1;
    RNG rng((unsigned)time(NULL));
    cam1.Setlocation(-3,0,-0.5);
    for(int i=0; i<1e7; i++)
    {
        double x = rng.uniform(-1.*lenx/2.,lenx/2.)*mm;
        double y = rng.uniform(-1.*leny/2.,leny/2.)*mm;
        double z = rng.uniform(0.,lenz)*mm;
        cam1.Fill(x,y,z);

        //if(i%int(1e8)==0) cam1.GetImage();
    }
    cam1.GetImage();
    */


    RNG rng((unsigned)time(NULL));
    int bin = 30;
    double minx = 0;
    double maxx = 2.2;
    double binSize = (maxx-minx)/bin;

    double x_sensor, y_sensor;

    for(int j=0; j<bin; j++) 
    {
        double xCam = minx+binSize*double(j)*mm;
        double yCam = xCam;
        double zCam = 0*mm;
        double translationCam[3] = {xCam,yCam,zCam};
        Camera cam;
        cam.Setlocation(xCam,yCam,zCam);
        for(int i=0; i<1e6; i++)
        {
            double x = rng.uniform(-1.*lenx/2.,lenx/2.)*mm;
            double y = rng.uniform(-1.*leny/2.,leny/2.)*mm;
            double z = rng.uniform(transz,transz+lenz)*mm;
            cam.Fill(x,y,z,x_sensor,y_sensor);
        }
        cam.GetImage();
    }

    // step 4 : output data
    // cameras
    Camera cam2;
    for(int j=0; j<bin; j++) 
    {
        double xCam = minx+binSize*double(j)*mm;
        double yCam = xCam;
        double zCam = 0*mm;
        double translationCam[3] = {xCam,yCam,zCam};
        data.addACamera_NORotation(j,translationCam,cam2.GetFocalLength());
        //data.addACamera_NORotation_translationInversed(j,translationCam,cam2.GetFocalLength());
    }
    // writing a file
    ofstream write("output.txt");
    // corners
    for(int i=0;i<corners.size();i++)
    {
        double x=corners[i](0,0);
        double y=corners[i](1,0);
        double z=corners[i](2,0);
        cout<<i<<": "<<corners[i].transpose()<<endl;

        for(int j=0; j<bin; j++) 
        {
            double xCam = minx+binSize*double(j)*mm;
            double yCam = xCam;
            double zCam = 0*mm;
            cam2.Setlocation(xCam,yCam,zCam);
            cam2.Fill(x,y,z,x_sensor,y_sensor);

            double x_aperture=0;
            double y_aperture=0;
            cam2.GetPoint_SensorCoorSysToApertureCoorSys(x_sensor,y_sensor,x_aperture,y_aperture);
            cout<<j<<", "<<i<<": "<<x_sensor<<"   "<<y_sensor<<";   "<<x_aperture/mm<<"   "<<y_aperture/mm<<endl;
            data.addAnObservation(j,i,x_aperture,y_aperture);

            write<<"Camera "<<xCam<<" "<<yCam<<" "<<zCam<<" LandMark "<<x<<" "<<y<<" "<<z<<" "<<" observation "<<x_sensor<<"   "<<y_sensor<<endl;
        }
    }

    write.close();

    data.ShowCameras(); 

    /*
    cout<<data.observations.size()<<endl;
    data.write("outputTest.txt");
    */

    return 0;
}
