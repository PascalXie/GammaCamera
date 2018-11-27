#ifndef DATACAMERASANDPOINTS_H
#define DATACAMERASANDPOINTS_H 1
#include <iostream>
#include <fstream>
#include <vector>

// data
#include "dataLandMark.h"
#include "dataObservation.h"
#include "dataCamera.h"

// units
#include "units.h"



using namespace std;

class DatabaseCamerasAndPoints
{
    public:
        DatabaseCamerasAndPoints();
        ~DatabaseCamerasAndPoints();

    public:
        void addACamera_NORotation_translationInversed(int IDCamera, double translation[3], double focalLength);
        void addACamera_NORotation(int IDCamera, double translation[3], double focalLength);
        void addALandMark(int IDLandMark, double x, double y, double z);
        void addAnObservation(int IDCamera, int IDLandMark, double x, double y);

        void write(string filename);
    
        void ShowCameras();
        void ShowLandMarkers();
    
    public:
        // LandMarks 3D
        vector<DataLandMark> landMarks;

        // Observations 2D
        vector<DataObservation> observations;

        // Cameras
        vector<DataCamera> cameras;
    
    
};

#endif
