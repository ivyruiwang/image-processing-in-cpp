// Maqsood.Yaqub@amsterdamumc.nl
// version 20241031

#ifndef TOOLS_HPP_INCLUDED
#define TOOLS_HPP_INCLUDED

#include <iostream>
#include <cstring>
#include "bmpmini.hpp" // code taken from https://github.com/yangcha/bmpmini/blob/master/example.cpp, BSD-2 license
#include <cstdint>

//#include <fstream>
//#include <math.h>
//#include <algorithm>
//#include <float.h> // for microsoft
//#include <stdlib.h>

// PART OF CODE TAKEN FROM ANALYZE 7.5 EXAMPLE

struct header_key {
    int sizeof_hdr;
    char data_type[10];
    char db_name[18];
    int extents;
    short int session_error;
    char regular;
    char hkey_un0;
    }; // 40 bytes total


struct image_dimension {
    short int dim[8]; // [0]=number of dim, [1] = X dim, [2]=Y, [3]=Z, [4]= time
    char vox_units[4];
    char cal_units[8];
    short int unused1;
    short int datatype;
    short int bitpix;
    short int dim_un0;
    float pixdim[8]; //[1]=voxel width, 2=height, 3=slice distance etc 
    float vox_offset;
    float funused1;
    float funused2;
    float funused3;
    float cal_max;
    float cal_min;
    int compressed;
    int verified;
    int glmax,glmin;
    }; // 108 bytes total

struct data_history {
    char descrip[80];
    char aux_file[24];
    char orient;
    short int originator[5];
    char generated[10];
    char scannum[10];
    char patient_id[10];
    char exp_date[10];
    char exp_time[10];
    char hist_un0[3];
    int views;
    int vols_added;
    int start_field;
    int field_skip;
    int omax, omin;
    int smax, smin;
    };

struct dsr {
    struct header_key hk;
    struct image_dimension dime;
    struct data_history hist;
    }; // total of 348 bytes
	
	


int readAnalyzeHdr(char * analyzeHdrFile, struct dsr *);
void writeAnalyzeHdr(char * analyzeHdrFileOut, struct dsr *);
void HdrToBytes(unsigned char * Hbytes, struct dsr *hdr, int swap);
int BytesToHdr(unsigned char * Hbytes, struct dsr *hdr);

void swap_long(unsigned char *);
void swap_short(unsigned char *);
void swap_hdr(struct dsr *pntr);
int copyShortToCharA(int stpos, short int * in, unsigned char * Hbytes, int swap, int size);
int copyShortToCharA(int stpos, short int in, unsigned char * Hbytes, int swap);
int copyLongToCharA(int stpos, int * in, unsigned char * Hbytes, int swap, int size);
int copyLongToCharA(int stpos, int in, unsigned char * Hbytes, int swap);
int copyFloatToCharA(int stpos, float in, unsigned char * Hbytes, int swap);
int copyFloatToCharA(int stpos, float * in, unsigned char * Hbytes, int swap, int size);
int copyCharToCharA(int stpos, char * in, unsigned char * Hbytes, int size);
int copyCharToCharA(int stpos, char in, unsigned char * Hbytes);
int copyCharAToShort(int stpos, short int * in, unsigned char * Hbytes, int swap, int size);
int copyCharAToShort(int stpos, short int * in, unsigned char * Hbytes, int swap);
int copyCharAToLong(int stpos, int * in, unsigned char * Hbytes, int swap, int size);
int copyCharAToLong(int stpos, int * in, unsigned char * Hbytes, int swap);
int copyCharAToFloat(int stpos, float * in, unsigned char * Hbytes, int swap, int size);
int copyCharAToFloat(int stpos, float * in, unsigned char * Hbytes, int swap);
int copyCharAToChar(int stpos, char * in, unsigned char * Hbytes, int size);
int copyCharAToChar(int stpos, char * in, unsigned char * Hbytes);

void readFloatArray(char * analyzeImgFile, unsigned int endianSwap, long startByte, float * resultArray, long size, float scalefactor);
void writeFloatArray(char * analyzeImgFile, float * resultArray, long size);
void writeFloatArrayAdd(char * analyzeImgFile, float * resultArray, long size);
void readShortArray(char * analyzeImgFile, unsigned int endianSwap, long startByte, float * resultArray, long size, float scalefactor);
void writeByteArray(char * analyzeImgFile, unsigned char * resultArray, long size);
short ShortSwapEndian( short s );
int LongSwapEndian (int i);
float FloatSwapEndian( float f );
short ByteToShort(unsigned char * b);
void ShortToByte(short s, unsigned char * b, int swap);
int ByteToLong(unsigned char * b);
void LongToByte(int i, unsigned char * b, int swap);
float ByteToFloat(unsigned char * b);
void FloatToByte(float f, unsigned char * b, int swap);

float * allocateVector(unsigned int N);
void freeVector(float * vec);

struct analyzeDataSet{
	struct dsr hdr;
	float * imageData;
	};

void showHdr(const char *, struct dsr *);

analyzeDataSet read_analyze_image(const char * fnin);

void saveBMP_tools(int width, int height, const float* dataFLT, const char* fname);

struct imgUChar {
    float scalefactor;
    unsigned char * dataUchar;
    }; 
    
imgUChar floatImgToUChar(const float* dataFLT, long sizeofdata);

#endif // IMAGE_HPP_INCLUDED