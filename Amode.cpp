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

// input: numElement
// operation: Create an array containing the element location (in x-direction) of the ultrasound transducer
// returns: eleLocation -> elementPosition[]
float *genElementLocation(int numElement, float PITCH)
{
    // Array contains the element location (x-direction)
    float* eleLocation = new float[numElement];

    // Load eleLocation[n] array
    for (int n = 0; n <= numElement-1; n ++) {
        eleLocation[n] = (n - ((float)numElement-1)/2) * PITCH;
    }
    return eleLocation;
}

// input: all inputs nesscary for calculations
// operation: Beamform the A-mode scanline
// return: void
void beamform(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel, float FS, float SoS)
{   
    // Repeat for each scanline location first
    for (int i = 0; i < numPixel; i++) {
        // tforward: time it takes for transducer to transmit signals
        float tforward = scanlinePosition[i] / SoS;
    
        // set p_real, p_imag to 0
        float p_real = 0.0 ; // accumulation of all real
        float p_imag = 0.0; // accumulation of all imag 

        // Repeat for each element location next
        for (int k = 0; k < numElement; k++) {
            // tbackward: time it takes for signal to be recieved to transducer
            float tbackward = sqrt (pow(scanlinePosition[i], 2) + pow(elementPosition[k], 2))/SoS;
            // ttotal: total time of signal transmitting and recieving
            float ttotal = tforward + tbackward;
            // sample: ????
            int sample = floor(ttotal * FS);

            // Accumulate data from text file in kth and sample position of text files
            p_real += realRFData[k][sample];
            p_imag += imagRFData[k][sample];
        }
        // calculate scanline (result)
     scanline[i] = sqrt(pow (p_real, 2) + pow (p_imag, 2));
        
    }
}

// input: file, scanlinePosition, scanline, numPixel
// operation: Write the scanline to a csv file
// return: if opened properly (0), error (-1)
int outputScanline(const char *fileName, float *scanlinePosition, float *scanline, int numPixel)
{
    // Open file
    ofstream outputFile;
    outputFile.open(fileName);
    
    // Check if file can be opened
    if (outputFile.fail()){
        return -1;
    }
    // Iterate through numPixel (128) times
    for (int i = 0; i < numPixel; i++) {
        outputFile << scanlinePosition[i] << "," << scanline[i] << endl;
    }
    return 0 ;
}

