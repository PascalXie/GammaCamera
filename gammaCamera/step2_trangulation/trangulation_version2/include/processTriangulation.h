#ifndef PROCESSTRIANGULATION_H
#define PROCESSTRIANGULATION_H 1

#include <iostream>
#include <vector>

#include "dataObservation.h"

// Eigen
#include <Eigen/Dense> 

using namespace std;
using namespace Eigen;

class ProcessTriangulation
{
    public:
        ProcessTriangulation(int ID);
        ~ProcessTriangulation();
    public:
        void AddObservation(DataObservation observation);
        void DoTriangulate();
        void ShowProcessTriangulation();

    //private:
    public:
        int ID_;
        vector<DataObservation> Observations_;
        Matrix<double, 3, 1> LandMarkEstimated_;
};
#endif
