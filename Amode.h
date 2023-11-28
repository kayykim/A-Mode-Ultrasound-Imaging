#ifndef AMODE_H
#define AMODE_H

// CREATE MATRIX
// input: row, col
// operations: make empty matrix
// return: RFData -> realRFData [][]

// variables:
// numElement: Number of desired elements
// numSample: Number of desired samples
float ** createDataMatrix(int numElement, int numSample);



// LOAD DATA
// input: Empty matrix, txt file
// operations: load realRFData.txt and imagRFData.txt file into empty matrix
// return: if loaded properly (0), error (-1)

// variables:
//      **RFData: Input pointer to 2D data array
//      *fileName: Input pointer to fileName array
//      numElement: Number of desired elements
//      numSample: Number of desired samples
int loadRFData(float **RFData, const char *fileName, int numElement, int numSample);




// SCANLINE LOCATION
// input: numPixel
// operation: Create an array containing the depth location (in z-direction) for each pixel on the scanline
// return: scanlineLocations -> scanlinePosition[]

// variables:
// &numPixel: Address location for number of pixels
float *genScanlineLocation(int &numPixel);



//ELEMENT LOCATION
// input: numElement
// operation: Create an array containing the element location (in x-direction) of the ultrasound transducer
// returns: eleLocation -> elementPosition[]

// variables:
//      numElement: Number of desired elements
//      PITCH: PITCH of transducer (spacing of elements)
float *genElementLocation(int numElement, float PITCH);



// CREATE SCAN LINE
// variables:
//      numPixel: Number of desired pixels

// input: all inputs nesscary for calculations
// operation: Beamform the A-mode scanline
// return: void

float *createScanline(int numPixel) ;


// BEAMFORM 
// input: numPixel
// operations: Allocate memory to store the beamformed scanline
// return: scanline (result)

//variables:
//      *scanline: Input pointer to scanline array
//      **realRFData: Input pointer to real RF data array
//      **imagRFData: Input pointer to iamg RF data array
//      *scanlinePosition: Input pointer to scanline position array
//      *elementPosition: Input pointer to scanline position array
//      numElement: Number of desired elements
//      numSample: Number of desired samples
//      numPixel: Number of desired pixels
//      FS: Number of desired pixels
//      SOS: Number of desired pixels
void beamform(float *scanline, float ** realRFData, float ** imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel, float FS, float SOS);


// OUTPUT SCANLINE
// input: file, scanlinePosition, scanline, numPixel
// operation: Write the scanline to a csv file
// return: if opened properly (0), error (-1)

// variables:
//      *fileName: Input pointer to filename character array
//      *scanlinePosition: Input pointer to scanline position array
//      *scanline: Input pointer to scanline array
//      numPixel: Number of desired pixels
int outputScanline(const char * fileName, float *scanlinePosition, float *scanline, int numPixel);

// DESTROY ALL ARRAYS
// input: all arrays and elements with a dynamical memory allocatino
// operation: destroy all arrays
// return: void

// variables:
//      *scanline: Input pointer to scanline array
//      **realRFData: Input pointer to real RF data array
//      **imagRFData: Input pointer to iamg RF data array
//      *scanlinePosition: Input pointer to scanline position array
//      *elementPosition: Input pointer to scanline position array
//      numElement: Number of desired elements
//      numSample: Number of desired samples
//      numPixel: Number of desired pixels
void destroyAllArrays(float *scanline, float **realRFData, float **imagRFData, float *scanlinePosition, float *elementPosition, int numElement, int numSample, int numPixel);

#endif