#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Eigen
#include <Eigen/Dense>

// Observation
#include "dataObservation.h"
#include "processTriangulation.h"

using namespace std;
using namespace Eigen;

const double FocalLength_ = 50; // mm
const int cameraNum_ = 30;
const int TotalObservations_ = 240;

// function : random number
double Gaussian(double miu, double sigma);

int main(int argc, char** argv) 
{
    cout<<"Hello"<<endl;

    //
    // step 1 : import data
    //
    string filename = "output.txt";
    ifstream read(filename.c_str());

    if(read.fail())
    {
        cout<<"File dose not exist"<<endl;
        return 0;
    }

    string name[3];
    double camera[9];
    double landmark[3];
    double observation[2];

    vector<ProcessTriangulation> ProcessTris;
    int size = TotalObservations_/cameraNum_;
    for(int i=0;i<size;i++)
    {
        ProcessTriangulation proTri_temp(i);
        ProcessTris.push_back(proTri_temp);
    }

    int counter = 0;
    while(!read.eof())
    {
        // import camera
        read>>name[0];
        for(int i=0;i<3;i++)
            read>>camera[i];

        // import landmark
        read>>name[1]>>landmark[0]>>landmark[1]>>landmark[2];

        // import observation
        read>>name[2]>>observation[0]>>observation[1];

        if(read.eof()) break;

        /*
        // debug
        cout<<name[0]<<" ";
        for(int i=0;i<3;i++)
            cout<<camera[i]<<" ";
        cout<<name[1]<<" "<<landmark[0]<<" "<<landmark[1]<<" "<<landmark[2]<<" ";
        cout<<name[2]<<" "<<observation[0]<<" "<<observation[1]<<endl;
        */

        // Gaussion Error
        double sigma = 10;
        double obGauss_x = Gaussian(observation[0], sigma);
        double obGauss_y = Gaussian(observation[1], sigma);

        DataObservation ob(counter);
        ob.SetCamera(camera[0],camera[1],camera[2],FocalLength_);
        ob.SetLandMark(landmark[0],landmark[1],landmark[2]);
        ob.SetObservation(obGauss_x, obGauss_y);
        ob.CalculateMatrices();
        //ob.ShowObservation();
        /*
        // No Error
        DataObservation ob(counter);
        ob.SetCamera(camera[0],camera[1],camera[2],FocalLength_);
        ob.SetLandMark(landmark[0],landmark[1],landmark[2]);
        ob.SetObservation(observation[0],observation[1]);
        ob.CalculateMatrices();
        //ob.ShowObservation();
        */

        //cout<<counter/cameraNum_<<endl;
        ProcessTris[counter/cameraNum_].AddObservation(ob);

        counter++;
    }

    read.close();

    /*
    // debug
    cout<<ProcessTris.size()<<endl;
    for(int i=0;i<ProcessTris.size();i++)
    {
        ProcessTris[i].ShowProcessTriangulation();
    }
    */
    /*
    cout<<"main Transformation 0: \n"<<ProcessTris[0].Observations_[0].Transformarion_<<endl<<endl;
    cout<<"main Transformation 1: \n"<<ProcessTris[0].Observations_[1].Transformarion_<<endl<<endl;

    cout<<"main intrinsicMatrix 0: \n"<<ProcessTris[0].Observations_[0].K_inHomo_<<endl<<endl;
    cout<<"main intrinsicMatrix 1: \n"<<ProcessTris[0].Observations_[1].K_inHomo_<<endl<<endl;

    cout<<"main projection matrix 0: \n"<<ProcessTris[0].Observations_[0].Projection_<<endl<<endl;
    cout<<"main projection matrix 1: \n"<<ProcessTris[0].Observations_[1].Projection_<<endl<<endl;

    cout<<"main parameter matrix 0: \n"<<ProcessTris[0].Observations_[0].MatrixForTriangulation_<<endl<<endl;
    cout<<"main parameter matrix 1: \n"<<ProcessTris[0].Observations_[1].MatrixForTriangulation_<<endl<<endl;
    */

    //
    // step 2 : do triangulation
    //
    for(int i=0;i<ProcessTris.size();i++)
    //for(int i=0;i<1;i++)
    {
        ProcessTris[i].DoTriangulate();
    }


    /*
    // test
    cout<<"Test~~~~~~~~~~~~~"<<endl;
    MatrixXd test(3,3);
    test<<MatrixXd::Zero(3,3);
    cout<<test<<endl;

    MatrixXd temp(2,3);
    temp<<1,2,3,4,5,6;
    test.row(1) = temp.row(0);
    test.row(2) = temp.row(1);
    cout<<test<<endl;
    */


    return 0;
}

double Gaussian(double miu, double sigma)
{
    double PI = 3.1415926;
    double U1 = (double)rand() / RAND_MAX;
    double U2 = (double)rand() / RAND_MAX;
    double Z = sqrt(-2.*log(U1))*sin(2.*PI*U2);
    double Y =  miu + Z*sigma;

    return Y;
}
