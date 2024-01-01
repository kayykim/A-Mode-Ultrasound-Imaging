#include <iostream>
#include "Amode.h"

using namespace std;

int main () {

    // Initializations of Constants
    const int N = 128; // Number of channels 
    const int K = 3338; // Number of Samples
    const float PITCH = 3.048e-4; // This is the transducer pitch
    const float SOS = 1540; // Speed of sound variable
    const float FS = 40e6; // Sampling frequency variable
    const float TS = 1.0f/FS; // Sampling time variable

    // Initializations of Functions
    float **realRFData = createDataMatrix(N, K);
    float **imagRFData = createDataMatrix(N, K);

    int result = 0;

    // Load the data from the REAL txt file
    result = loadRFData(realRFData, "RealRFData_mystery.txt", N, K);
    
    // If loadRFD cannot open realRFData.txt file, return and error message
    if (result == -1) {
        cerr << "Cannot load from realRFData.txt, exiting program" << endl;
        return -1;
    }
    // Load the data from IMAGINARY txt file
    result = loadRFData(imagRFData, "ImagRFData_mystery.txt",N, K);

    // If loadRFD cannot open imagRFData.txt file, return an error message
    if (result == -1) {
        cerr << "Cannot load from imagRFData.txt, exiting program" << endl;
        return -2;
    }
    
    // Create imaging location array - scanlinePosition
    int numPixel = 256;
    float *scanlinePosition = genScanlineLocation(numPixel);

    // Create element locations - elementPosition
    float* elementPosition; 
    elementPosition = genElementLocation(N,PITCH);

    // Perform A-mode beamforming - scanline
    float *scanline;
    scanline = createScanline(numPixel);
    beamform(scanline, realRFData, imagRFData, scanlinePosition, elementPosition, N, K, numPixel, FS, SOS);
}
   // Output data into a .csv file
        // Note: Make sure to seperate columns with commas and
        // use endl to separate the rows.
    result = outputScanline("output.csv", scanlinePosition, scanline, numPixel);
    
        // if error writing into another file, return an error message
    if (result == -1) {
        cerr << "Cannot write scanline to output.csv, exiting program" << endl;
        return -3;
    }
