#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm> 
using namespace std;

// input: row, col
// operations: make empty matrix
// return: RFData -> realRFData [][]
float **createDataMatrix(int numElement, int numSample)
{
    // Create a 2D data matrix of size numElement x numSample
    float **RFData = new float*[numElement * numSample]; // dynamic memory allocation
        for (int i = 0; i < numElement; i++) {
            RFData[i] = new float[numSample];
                for (int j = 0; j < numSample; j++) 
                    RFData[i][j] = 0;
        }

    return RFData;
}

// input: Empty matrix, txt file
// operations: load realRFData.txt and imagRFData.txt file into empty matrix
// return: if loaded properly (0), error (-1)
int loadRFData(float **RFData, const char *fileName, int numElement, int numSample)
{
    // Open the text file fileName, read the data and store into RFData
    ifstream file_info(fileName);
    
    // return -1 if the function fails to open the file specififed in fileName
    if (file_info.fail()) {
        cerr << "Error: file not open.\n";
        return -1; // result = -1
    }

    string line;

    for (int i = 0; i < numElement; i++){ // repeat row times
        for (int j = 0; j < numSample; j++) { // repeats col times
            getline(file_info, line);

            istringstream changed_num(line);
            changed_num >> RFData[i][j];
            // RFData is loaded
        }
    }
    return 0;
}

// input: numPixel
// operation: Create an array containing the depth location (in z-direction) for each pixel on the scanline
// return: scanlineLocations -> scanlinePosition[]
float *genScanlineLocation(int &numPixel)
{
    float depth;
    float depth_value = 0; // has the value of elements in the array (start at 0m)

    // Prompt the user for how deep the scanline would be
    cout << "How deep is the scanline? ";
    cin >> depth;
    cout << "Num Pixel: ";
    cin >> numPixel;

    float spacing = depth/(numPixel-1); // spacing of depth based on numPixels

    // Array contains scanline location based on desired depth (z-direction)
    float* scanlineLocations = new float[numPixel];

    // Load scanlineLocation[n] array
    for (int i = 0; i < numPixel; i ++ ){
        scanlineLocations[i] = depth_value;

        // update depth value so it adds spacing to the next iteration
        depth_value += spacing;
    }
    return scanlineLocations;
}
