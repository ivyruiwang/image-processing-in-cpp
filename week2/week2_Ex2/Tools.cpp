// Tools
// Maqsood.Yaqub@amsterdamumc.nl
// version 20241031

#include "Tools.hpp"


analyzeDataSet read_analyze_image(const char * fnin){
	char * analyzeHdrFile = new char[strlen(fnin)+1];
	char * analyzeImgFile = new char[strlen(fnin)+1];
	strcpy(analyzeHdrFile, fnin);
    strcpy(analyzeImgFile, fnin);
	
    analyzeHdrFile[strlen(analyzeHdrFile)-3] = 'h';
    analyzeHdrFile[strlen(analyzeHdrFile)-2] = 'd';
    analyzeHdrFile[strlen(analyzeHdrFile)-1] = 'r'; 

    std::cout << "Input filename image (.hdr): " << analyzeHdrFile<< std::endl;      
    analyzeImgFile[strlen(analyzeImgFile)-3] = 'i';
    analyzeImgFile[strlen(analyzeImgFile)-2] = 'm';
    analyzeImgFile[strlen(analyzeImgFile)-1] = 'g';
    std::cout << "Input filename image (.img): " << analyzeImgFile<< std::endl;

	
	struct dsr hdr;
	std::cout << "Loading file (.hdr): " << analyzeHdrFile<< std::endl;
	unsigned int endianSwap = readAnalyzeHdr(analyzeHdrFile, &hdr);
	//ShowHdr(analyzeHdrFile, &hdr);
	
    int xDim = hdr.dime.dim[1];
	int yDim = hdr.dime.dim[2];
	int zDim = hdr.dime.dim[3];
//	int nr_frames=hdr.dime.dim[4];
//	float x_sz = hdr.dime.pixdim[1];
//	float y_sz = hdr.dime.pixdim[2];
//	float z_sz = hdr.dime.pixdim[3];
	long size = xDim*yDim*zDim;
	float * resultArraytmp = allocateVector(size);
	float scalefactor = hdr.dime.funused1;
	short int datatype = hdr.dime.datatype; // int i=1 2 3 4 5 6 7 8, datatype = (1<<(i-1))
	short int bitpix = hdr.dime.bitpix; //  0 1 8 16 32 32 64 64 24
	
	
	if(datatype == 16 && bitpix == 32)
		readFloatArray(analyzeImgFile, endianSwap, 0, resultArraytmp, size, scalefactor);
		
	if(datatype == 4 && bitpix == 16)
		readShortArray(analyzeImgFile, endianSwap, 0, resultArraytmp, size, scalefactor);
		
    // need to check for if not met with required datatype
 	analyzeDataSet tmpDataSet = {hdr, resultArraytmp}; 
    
	return tmpDataSet;
	}

int readAnalyzeHdr(char * analyzeHdrFile, struct dsr * hdr){
      unsigned char Hbytes[348];
      FILE *fpin;
      fpin=fopen(analyzeHdrFile, "rb");
      if(fpin==NULL) {
        printf("unable to open file\n");
      } else {
        fread(Hbytes,1,348,fpin);
        fclose(fpin);
      }
      int swap = BytesToHdr(Hbytes, hdr);
      return swap;
    }

void writeAnalyzeHdr(char * analyzeHdrFileOut, struct dsr * hdr){
     int swap = 0; // swapping endian for saving
     unsigned char HbytesOut[348];
     HdrToBytes(HbytesOut, hdr, swap);
     FILE *fp;
     fp=fopen(analyzeHdrFileOut, "wb");
    if(fp==NULL) {
        std::cout<<"unable to create file"<<"\n";
    } else {
        fwrite(HbytesOut,348,1,fp);
        fclose(fp);
    }
    }
	
	void HdrToBytes(unsigned char * Hbytes, struct dsr *hdr, int swap){
    int stpos = 0;
    
    stpos = copyLongToCharA(stpos, hdr->hk.sizeof_hdr, Hbytes, swap);
    stpos = copyCharToCharA(stpos, hdr->hk.data_type, Hbytes, 10);
    stpos = copyCharToCharA(stpos, hdr->hk.db_name, Hbytes, 18);
    stpos = copyLongToCharA(stpos, hdr->hk.extents, Hbytes, swap);
    stpos = copyShortToCharA(stpos, hdr->hk.session_error, Hbytes, swap);
    stpos = copyCharToCharA(stpos, hdr->hk.regular, Hbytes);    
    stpos = copyCharToCharA(stpos, hdr->hk.hkey_un0, Hbytes);

    stpos = copyShortToCharA(stpos, hdr->dime.dim, Hbytes, swap, 8);
    stpos = copyCharToCharA(stpos, hdr->dime.vox_units, Hbytes, 4);
    stpos = copyCharToCharA(stpos, hdr->dime.cal_units, Hbytes, 8);
    stpos = copyShortToCharA(stpos, hdr->dime.unused1, Hbytes, swap);
    stpos = copyShortToCharA(stpos, hdr->dime.datatype, Hbytes, swap);
    stpos = copyShortToCharA(stpos, hdr->dime.bitpix, Hbytes, swap);
    stpos = copyShortToCharA(stpos, hdr->dime.dim_un0, Hbytes, swap);
    stpos = copyFloatToCharA(stpos, hdr->dime.pixdim, Hbytes, swap,8);
    stpos = copyFloatToCharA(stpos, hdr->dime.vox_offset, Hbytes, swap);
    stpos = copyFloatToCharA(stpos, hdr->dime.funused1, Hbytes, swap);
    stpos = copyFloatToCharA(stpos, hdr->dime.funused2, Hbytes, swap);
    stpos = copyFloatToCharA(stpos, hdr->dime.funused3, Hbytes, swap);
    stpos = copyFloatToCharA(stpos, hdr->dime.cal_max, Hbytes, swap);
    stpos = copyFloatToCharA(stpos, hdr->dime.cal_min, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->dime.compressed, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->dime.verified, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->dime.glmax, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->dime.glmin, Hbytes, swap);

    stpos = copyCharToCharA(stpos, hdr->hist.descrip, Hbytes, 80);
    stpos = copyCharToCharA(stpos, hdr->hist.aux_file, Hbytes, 24);
    stpos = copyCharToCharA(stpos, hdr->hist.orient, Hbytes);
    stpos = copyShortToCharA(stpos, hdr->hist.originator, Hbytes, swap, 5);
    stpos = copyCharToCharA(stpos, hdr->hist.generated, Hbytes, 10);
    stpos = copyCharToCharA(stpos, hdr->hist.scannum, Hbytes, 10);
    stpos = copyCharToCharA(stpos, hdr->hist.patient_id, Hbytes, 10);
    stpos = copyCharToCharA(stpos, hdr->hist.exp_date, Hbytes, 10);
    stpos = copyCharToCharA(stpos, hdr->hist.exp_time, Hbytes, 10);
    stpos = copyCharToCharA(stpos, hdr->hist.hist_un0, Hbytes, 3);
    stpos = copyLongToCharA(stpos, hdr->hist.views, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->hist.vols_added, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->hist.start_field, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->hist.field_skip, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->hist.omax, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->hist.omin, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->hist.smax, Hbytes, swap);
    stpos = copyLongToCharA(stpos, hdr->hist.smin, Hbytes, swap);
    }

int BytesToHdr(unsigned char * Hbytes, struct dsr *hdr){
    int stpos = 0;
    int swap = 0; // swapping endian for opening

    stpos = copyCharAToLong(stpos, &hdr->hk.sizeof_hdr, Hbytes, swap);
    //cout << hdr->hk.sizeof_hdr<<"\n";
   
    if (hdr->hk.sizeof_hdr!=348){
    swap =1;
    stpos = 0;
    stpos = copyCharAToLong(stpos, &hdr->hk.sizeof_hdr, Hbytes, swap);
    std::cout << "Bytes swapped, "<< hdr->hk.sizeof_hdr<<"\n";
    }
    
    stpos = copyCharAToChar(stpos, &hdr->hk.data_type[0], Hbytes, 10);
    stpos = copyCharAToChar(stpos, &hdr->hk.db_name[0], Hbytes, 18);
    stpos = copyCharAToLong(stpos, &hdr->hk.extents, Hbytes, swap);
    stpos = copyCharAToShort(stpos, &hdr->hk.session_error, Hbytes, swap);
    stpos = copyCharAToChar(stpos, &hdr->hk.regular, Hbytes);
    stpos = copyCharAToChar(stpos, &hdr->hk.hkey_un0, Hbytes);

    stpos = copyCharAToShort(stpos, &hdr->dime.dim[0], Hbytes, swap, 8);
    stpos = copyCharAToChar(stpos, &hdr->dime.vox_units[0], Hbytes, 4);
    stpos = copyCharAToChar(stpos, &hdr->dime.cal_units[0], Hbytes, 8);
    stpos = copyCharAToShort(stpos, &hdr->dime.unused1, Hbytes, swap);
    stpos = copyCharAToShort(stpos, &hdr->dime.datatype, Hbytes, swap);
    stpos = copyCharAToShort(stpos, &hdr->dime.bitpix, Hbytes, swap);
    stpos = copyCharAToShort(stpos, &hdr->dime.dim_un0, Hbytes, swap);
    stpos = copyCharAToFloat(stpos, &hdr->dime.pixdim[0], Hbytes, swap,8);
    stpos = copyCharAToFloat(stpos, &hdr->dime.vox_offset, Hbytes, swap);
    stpos = copyCharAToFloat(stpos, &hdr->dime.funused1, Hbytes, swap);
    stpos = copyCharAToFloat(stpos, &hdr->dime.funused2, Hbytes, swap);
    stpos = copyCharAToFloat(stpos, &hdr->dime.funused3, Hbytes, swap);
    stpos = copyCharAToFloat(stpos, &hdr->dime.cal_max, Hbytes, swap);
    stpos = copyCharAToFloat(stpos, &hdr->dime.cal_min, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->dime.compressed, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->dime.verified, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->dime.glmax, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->dime.glmin, Hbytes, swap);

    stpos = copyCharAToChar(stpos, &hdr->hist.descrip[0], Hbytes, 80);
    stpos = copyCharAToChar(stpos, &hdr->hist.aux_file[0], Hbytes, 24);
    stpos = copyCharAToChar(stpos, &hdr->hist.orient, Hbytes);
    stpos = copyCharAToShort(stpos, &hdr->hist.originator[0], Hbytes, swap, 5);
    stpos = copyCharAToChar(stpos, &hdr->hist.generated[0], Hbytes, 10);
    stpos = copyCharAToChar(stpos, &hdr->hist.scannum[0], Hbytes, 10);
    stpos = copyCharAToChar(stpos, &hdr->hist.patient_id[0], Hbytes, 10);
    stpos = copyCharAToChar(stpos, &hdr->hist.exp_date[0], Hbytes, 10);
    stpos = copyCharAToChar(stpos, &hdr->hist.exp_time[0], Hbytes, 10);
    stpos = copyCharAToChar(stpos, &hdr->hist.hist_un0[0], Hbytes, 3);
    stpos = copyCharAToLong(stpos, &hdr->hist.views, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->hist.vols_added, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->hist.start_field, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->hist.field_skip, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->hist.omax, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->hist.omin, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->hist.smax, Hbytes, swap);
    stpos = copyCharAToLong(stpos, &hdr->hist.smin, Hbytes, swap);
    return swap;
    }
	
	int copyShortToCharA(int stpos, short int * in, unsigned char * Hbytes, int swap, int size){
    for(int i=0;i<size;i++){
        stpos = copyShortToCharA(stpos, in[i], Hbytes, swap);
        }
    return stpos;
    }
//
int copyCharAToShort(int stpos, short int * in, unsigned char * Hbytes, int swap, int size){
    for(int i=0;i<size;i++){
        stpos = copyCharAToShort(stpos, &in[i], Hbytes, swap);
        }
    return stpos;
    }

int copyShortToCharA(int stpos, short int in, unsigned char * Hbytes, int swap){
    unsigned char b[2];
    ShortToByte(in, &b[0], swap);
    Hbytes[stpos+0] = b[0];
    Hbytes[stpos+1] = b[1];
    return stpos + 2;
    }

//
int copyCharAToShort(int stpos, short int * in, unsigned char * Hbytes, int swap){
    if(swap == 1){
        *in = ShortSwapEndian(ByteToShort(&Hbytes[stpos+0]));
    }else{
        *in = ByteToShort(&Hbytes[stpos+0]);
    }
    return stpos + 2;
    }

int copyLongToCharA(int stpos, int * in, unsigned char * Hbytes, int swap, int size){
    for(int i=0;i<size;i++){
        stpos = copyLongToCharA(stpos, in[i], Hbytes, swap);
        }
    return stpos;
    }

//
int copyCharAToLong(int stpos, int * in, unsigned char * Hbytes, int swap, int size){
    for(int i=0;i<size;i++){
        stpos = copyCharAToLong(stpos, &in[i], Hbytes, swap);
        }
    return stpos;
    }


int copyLongToCharA(int stpos, int in, unsigned char * Hbytes, int swap){
    unsigned char b[4];
    LongToByte(in, &b[0], swap);
    Hbytes[stpos+0] = b[0];
    Hbytes[stpos+1] = b[1];
    Hbytes[stpos+2] = b[2];
    Hbytes[stpos+3] = b[3];
    return stpos + 4;
    }

//
int copyCharAToLong(int stpos, int * in, unsigned char * Hbytes, int swap){
    if(swap == 1) {
    *in = LongSwapEndian(ByteToLong(&Hbytes[stpos+0]));
    }else{
    *in = ByteToLong(&Hbytes[stpos+0]);
    }
    return stpos + 4;
    }


int copyFloatToCharA(int stpos, float * in, unsigned char * Hbytes, int swap, int size){

    for(int i=0;i<size;i++){
        //cout << stpos << ", ";
        stpos = copyFloatToCharA(stpos, in[i], &Hbytes[0], swap);
        //cout << stpos << "\n";
        } 
    return stpos;       
    }

//
int copyCharAToFloat(int stpos, float * in, unsigned char * Hbytes, int swap, int size){
    for(int i=0;i<size;i++){
        //cout << stpos << ", ";
        stpos = copyCharAToFloat(stpos, &in[i], &Hbytes[0], swap);
        //cout << stpos << "\n";
        }
    return stpos;
    }

int copyFloatToCharA(int stpos, float in, unsigned char * Hbytes, int swap){
    unsigned char b[4];
    FloatToByte(in, &b[0], swap);
    Hbytes[stpos+0] = b[0];
    Hbytes[stpos+1] = b[1];
    Hbytes[stpos+2] = b[2];
    Hbytes[stpos+3] = b[3];
    return stpos + 4;
    }

//
int copyCharAToFloat(int stpos, float * in, unsigned char * Hbytes, int swap){
    if(swap == 1) {
    *in = FloatSwapEndian( ByteToFloat(&Hbytes[stpos+0]) );
    } else {
    *in = ByteToFloat(&Hbytes[stpos+0]);
    }
    return stpos + 4;
    }


int copyCharToCharA(int stpos, char * in, unsigned char * Hbytes, int size){
    for(int i = 0; i < size; i++){
        Hbytes[stpos+i] = in[i];
    } 
    return stpos + size;
    }

//
int copyCharAToChar(int stpos, char * in, unsigned char * Hbytes, int size){
    for(int i = 0; i < size; i++){
        in[i] = Hbytes[stpos+i];
    }
    return stpos + size;
    }

int copyCharToCharA(int stpos, char in, unsigned char * Hbytes){
    Hbytes[stpos] = in;
    return stpos + 1;
    }

//
int copyCharAToChar(int stpos, char * in, unsigned char * Hbytes){
    *in = Hbytes[stpos];
    return stpos + 1;
    }
	
short ByteToShort(unsigned char * b){
    return (b[1] << 8) + b[0];
    }

void ShortToByte(short s, unsigned char * b, int swap){
    if (swap == 1){
        s = ShortSwapEndian(s);
        }
    b[0] = s & 255; // bitwise AND, take the first byte
    b[1] = (s >> 8) & 255; // bitwise right shift data (>>)
    }

short ShortSwapEndian( short s ){ // from gamedev
  unsigned char b1, b2;
  b1 = s & 255;
  b2 = (s >> 8) & 255;
  return (b1 << 8) + b2;
}


int ByteToLong(unsigned char * b){
    return ((int)b[3] << 24) + ((int)b[2] << 16) + ((int)b[1] << 8) + b[0];
    }

void LongToByte(int i, unsigned char * b, int swap){
    if (swap == 1){
        i = LongSwapEndian(i);
        }
      b[0] = i & 255;
      b[1] = (i >> 8) & 255;
      b[2] = (i >> 16) & 255;
      b[3] = (i >> 24) & 255;    
    }


int LongSwapEndian (int i){ // from gamedev
  unsigned char b1, b2, b3, b4;

  b1 = i & 255;
  b2 = ( i >> 8 ) & 255;
  b3 = ( i>>16 ) & 255;
  b4 = ( i>>24 ) & 255;

  return ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
}

float ByteToFloat(unsigned char * b){
    union {
    float f;
    unsigned char bb[4];
    } dat1;
    dat1.bb[0] = b[0];
    dat1.bb[1] = b[1];
    dat1.bb[2] = b[2];
    dat1.bb[3] = b[3];
    return dat1.f;
    }

void FloatToByte(float f, unsigned char * b, int swap){
    if (swap == 1){
        f = FloatSwapEndian(f);
        }
    union {
    float f;
    unsigned char bb[4];
    } dat1;
    dat1.f = f;
    b[0] = dat1.bb[0];
    b[1] = dat1.bb[1];
    b[2] = dat1.bb[2];
    b[3] = dat1.bb[3];
    }

float FloatSwapEndian( float f ){
  union // from gamedev
  {
    float f;
    unsigned char b[4];
  } dat1, dat2;

  dat1.f = f;
  dat2.b[0] = dat1.b[3];
  dat2.b[1] = dat1.b[2];
  dat2.b[2] = dat1.b[1];
  dat2.b[3] = dat1.b[0];
  return dat2.f;
}


void readFloatArray(char * analyzeImgFile, unsigned int endianSwap, long startByte, float * resultArray, long size, float scalefactor){
    // endianSwap == 1 then swap
    short nrBytesPerType = 4; // floats
    long nrBytes = size*nrBytesPerType;
    unsigned char * memblock = new unsigned char[nrBytes]; // for reading unsigned bytes
    FILE * pFile;
 //   size_t result;
    pFile = fopen ( analyzeImgFile , "rb" );
    if (pFile!=NULL){
        fseek (pFile , startByte , SEEK_SET);
//        size_t result = fread (memblock,1,nrBytes,pFile);
        fread (memblock,1,nrBytes,pFile);
        fclose (pFile);
 	    union{
            float f; // floats
            unsigned char b[4];//floats
        } tmp;
 	    long j = 0;
        for(long i = 0; i < size; i++){
            if(endianSwap == 0) {
                tmp.b[0] =  memblock[j];
                tmp.b[1] =  memblock[j+1];
                tmp.b[2] =  memblock[j+2];
                tmp.b[3] =  memblock[j+3];
            } else {
                tmp.b[3] =  memblock[j];
                tmp.b[2] =  memblock[j+1];
                tmp.b[1] =  memblock[j+2];
                tmp.b[0] =  memblock[j+3];
            }
            j = j + nrBytesPerType;
    	   resultArray[i] = tmp.f*scalefactor;
	    }
  //  cout << "It worked so far\n";
    } else {
        std::cout << "Unable to open file"<<"\n";
    }
    delete[] memblock;
}

void readShortArray(char * analyzeImgFile, unsigned int endianSwap, long startByte, float * resultArray, long size, float scalefactor){
    
    // endianSwap == 1 then swap
    short nrBytesPerType = 2; // shorts
    long nrBytes = size*nrBytesPerType;
    unsigned char * memblock = new unsigned char[nrBytes]; // for reading unsigned bytes 
    FILE * pFile;
 //   size_t result;
    pFile = fopen ( analyzeImgFile , "rb" );
    if (pFile!=NULL){
        fseek (pFile , startByte , SEEK_SET);
//        size_t result = fread (memblock,1,nrBytes,pFile);
        fread (memblock,1,nrBytes,pFile);
        fclose (pFile);
        unsigned char b1, b2;
        short tmp;
     	long j = 0;
        for(long i = 0; i < size; i++){
            if(endianSwap == 0) {
                b1 = memblock[j];
                b2 = memblock[j+1];
            } else {
                b2 = memblock[j];
                b1 = memblock[j+1];
            }
            tmp = (short)((b2 << 8) + b1); // making signed short
            j = j + nrBytesPerType;
    	   resultArray[i] = tmp*scalefactor;
	       }
  //  cout << "It worked so far\n";
    } else {
        std::cout << "Unable to open file"<<"\n";
    }
    delete[] memblock;
}

void writeFloatArray(char * analyzeImgFile, float * resultArray, long size){
    short nrBytesPerType = 4; // floats
    long nrBytes = size*nrBytesPerType;
    FILE * pFile;
 //   size_t result;
    pFile = fopen ( analyzeImgFile , "wb" );
    if (pFile!=NULL){
        fwrite (resultArray,1,nrBytes,pFile);
        fclose (pFile);
    } else {
        std::cout << "Unable to open file"<<"\n";
    }
}

void writeFloatArrayAdd(char * analyzeImgFile, float * resultArray, long size){
    short nrBytesPerType = 4; // floats
    long nrBytes = size*nrBytesPerType;
    FILE * pFile;
 //   size_t result;
    pFile = fopen ( analyzeImgFile , "ab" );
    if (pFile!=NULL){
        fwrite (resultArray,1,nrBytes,pFile);
        fclose (pFile);
    } else {
        std::cout << "Unable to open file"<<"\n";
    }
}



void writeByteArray(char * analyzeImgFile, unsigned char * resultArray, long size){
    short nrBytesPerType = 1; // floats
    long nrBytes = size*nrBytesPerType;
    FILE * pFile;
//    size_t result;
    pFile = fopen ( analyzeImgFile , "wb" );
    if (pFile!=NULL){
        fwrite (resultArray,1,nrBytes,pFile);
        fclose (pFile);
    } else {
        std::cout << "Unable to open file"<<"\n";
    }
}

void swap_long(unsigned char *pntr) {
unsigned char b0, b1, b2, b3;
b0 = *pntr;
b1 = *(pntr+1);
b2 = *(pntr+2);
b3 = *(pntr+3);
*pntr = b3;
*(pntr+1) = b2;
*(pntr+2) = b1;
*(pntr+3) = b0;
}

void swap_short(unsigned char *pntr) {
unsigned char b0, b1;
b0 = *pntr;
b1 = *(pntr+1);
*pntr = b1;
*(pntr+1) = b0;
}

float * allocateVector(unsigned int N){
     if(N==0){
              std::cout<<"\n"<<" Error allocating vector, N = 0!!!"<<"\n";
              }
     return new float[N];
     }

void freeVector(float *vec){
     if(vec == NULL){
//          printf("\n Error freeing vector, vector is NULL pointer!!!\n");
     } else {
        delete [] vec;
        vec = 0;
     }
     }
	 
void showHdr(const char *fileName,struct dsr * hdr) {
int i;
char string[128];
printf("Analyze Header Dump of: <%s> \n", fileName);
/* Header Key */
printf("sizeof_hdr: %d \n", hdr->hk.sizeof_hdr);
printf("data_type: %s \n", hdr->hk.data_type);
printf("db_name: %s \n", hdr->hk.db_name);
printf("extents: %d \n", hdr->hk.extents);
printf("session_error: %d \n", hdr->hk.session_error);
printf("regular: %c \n", hdr->hk.regular);
printf("hkey_un0: %c \n", hdr->hk.hkey_un0);
/* Image Dimension */
for(i=0;i<8;i++)
printf("dim[%d]: %d \n", i, hdr->dime.dim[i]);
strncpy(string,hdr->dime.vox_units,4);
printf("vox_units: %s \n", string);

strncpy(string,hdr->dime.cal_units,8);
printf("cal_units: %s \n", string);
printf("unused1: %d \n", hdr->dime.unused1);
printf("datatype: %d \n", hdr->dime.datatype);
printf("bitpix: %d \n", hdr->dime.bitpix);
for(i=0;i<8;i++)
printf("pixdim[%d]: %6.4f \n",i, hdr->dime.pixdim[i]);
printf("vox_offset: %6.4f \n", hdr->dime.vox_offset);
printf("funused1: %6.4f \n", hdr->dime.funused1);
printf("funused2: %6.4f \n", hdr->dime.funused2);
printf("funused3: %6.4f \n", hdr->dime.funused3);
printf("cal_max: %6.4f \n", hdr->dime.cal_max);
printf("cal_min: %6.4f \n", hdr->dime.cal_min);
printf("compressed: %d \n", hdr->dime.compressed);
printf("verified: %d \n", hdr->dime.verified);
printf("glmax: %d \n", hdr->dime.glmax);
printf("glmin: %d \n", hdr->dime.glmin);
/* Data History */
strncpy(string,hdr->hist.descrip,80);
printf("descrip: %s \n", string);
strncpy(string,hdr->hist.aux_file,24);
printf("aux_file: %s \n", string);
printf("orient: %c \n", hdr->hist.orient);

//printf("originator: %s \n", hdr->hist.originator);
strncpy(string,hdr->hist.generated,10);
printf("generated: %s \n", string);
strncpy(string,hdr->hist.scannum,10);
printf("scannum: %s \n", string);
strncpy(string,hdr->hist.patient_id,10);
printf("patient_id: %s \n", string);
strncpy(string,hdr->hist.exp_date,10);
printf("exp_date: %s \n", string);
strncpy(string,hdr->hist.exp_time,10);
printf("exp_time: %s \n", string);
strncpy(string,hdr->hist.hist_un0,10);
printf("hist_un0: %s \n", string);
printf("views: %d \n", hdr->hist.views);
printf("vols_added: %d \n", hdr->hist.vols_added);
printf("start_field:%d \n", hdr->hist.start_field);
printf("field_skip: %d \n", hdr->hist.field_skip);
printf("omax: %d \n", hdr->hist.omax);
printf("omin: %d \n", hdr->hist.omin);
printf("smin: %d \n", hdr->hist.smax);
printf("smin: %d \n", hdr->hist.smin);
}

void saveBMP_tools(int width, int height, const float* dataFLT, const char* fname){
	
	uint8_t * data = new uint8_t[width*height];
	float minvalue=10000000;
	float maxvalue=-10000000;
	for(int i=0;i<width*height;i++){
			if(minvalue> dataFLT[i])
				minvalue= dataFLT[i];
			if(maxvalue< dataFLT[i])
				maxvalue= dataFLT[i];
		}
//	std::cout << "minvalue: "<< minvalue << "\n";
//	std::cout << "maxvalue: "<< maxvalue << "\n";
	float scalefactor = (maxvalue - minvalue) / 256.0;
	std::cout << "scalefactor: "<< scalefactor << "\n";
	for(int i=0;i<width*height;i++){
			data[i] = (uint8_t)((dataFLT[i] - minvalue)/scalefactor);
		}

	using namespace image;
	ImageView tmp((int)width,(int)height,1,data);
	
    BMPMini bmp;
    try {
        bmp.write(tmp, fname);
		}
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        }
		delete[] data;
	}

    imgUChar floatImgToUChar(const float* dataFLT, long sizeofdata){
        
            uint8_t * data = new uint8_t[sizeofdata];
            
            float minvalue=10000000;
            float maxvalue=-10000000;
            for(int i=0;i<sizeofdata;i++){
            if(minvalue> dataFLT[i])
            minvalue= dataFLT[i];
            if(maxvalue< dataFLT[i])
            maxvalue= dataFLT[i];
            }
            //	std::cout << "minvalue: "<< minvalue << "\n";
            //	std::cout << "maxvalue: "<< maxvalue << "\n";
            float scalefactor = (maxvalue - minvalue) / 256.0;
            std::cout << "scalefactor: "<< scalefactor << "\n";
            
            for(int i=0;i<sizeofdata;i++)
                data[i] = (uint8_t)((dataFLT[i] - minvalue)/scalefactor);
            
            
            
            return imgUChar{scalefactor, data};
            
        }