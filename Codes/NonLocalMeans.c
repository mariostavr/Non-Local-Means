#include <stdio.h>
#include <stdlib.h>
#include <math.h>


FILE *inFile, *outFile;

int i, j, x, y, p, w; // "FOR" Counters

int var1, rSize, counterP=0; // Variables for "SIZES"

float filterSigma = 0.02;

int piSize=64, paSize=3; //piSize -> PictureSize, paSize -> PatchSize


//==================== Function Gaussian filter ====================
void FilterCreation(double *GKernel){
    double patchSigma = 1.6;
    double r, s = 2.0 * patchSigma * patchSigma;
    double sum = 0.0;
    var1 = (paSize-1)/2;

    for (x=-var1; x<=var1; x++) {
        for (y=-var1; y<=var1; y++) {
            r = sqrt(x*x+y*y);
            *(GKernel+(x+var1)*paSize+(y+var1)) = (exp(-(r*r)/s)) / (M_PI*s);
            sum += *(GKernel+(x+var1)*paSize+(y+var1));
        }
    }
    for (i=0; i<paSize; ++i)
        for (j=0; j<paSize; ++j)
            *(GKernel+i*paSize+j) /= sum;
}//==================================================================

//=========================== Input Image ===========================
void loadInputImage(float *image){
    printf("Original Image is Loading...\n");
    inFile = fopen("House_64.txt","r");
    for(i=0; i<piSize; i++)
        for(j=0; j<piSize; j++)
            fscanf(inFile, "%f", (image + i*piSize+j));
    fclose(inFile);
    printf("Original Image Loaded!\n");
}//==================================================================

//======================== NON LOCAL MEANS ==========================
void non_local_means(float *image){
    //=============================================================== Resizing the image
    rSize = piSize + (paSize-1); var1 = (paSize-1)/2;
    float *resizedImage = (float *)malloc(rSize*rSize*sizeof(float));
    printf("Resizing the Image...\n");
    float upSide=0, downSide=0, leftSide=0, rightSide=0;
    for(i=0; i<piSize; i++){
        upSide += *(image+0*piSize+i);
        downSide += *(image+(piSize-1)*piSize+i);
        leftSide += *(image+i*piSize+0);
        rightSide += *(image+(piSize-1)*piSize+i);
    }
    for(i=0; i<var1; i++)
        for(j=0; j<rSize; j++){
            *(resizedImage+i*rSize+j) = upSide/piSize;
            *(resizedImage+(piSize+var1+i)*rSize+j) = downSide/piSize;
            *(resizedImage+j*rSize+i) = leftSide/piSize;
            *(resizedImage+j*rSize+(piSize+var1+i)) = rightSide/piSize;
        }
    for(i=var1; i<rSize-var1; i++)
        for(j=var1; j<rSize-var1; j++)
            *(resizedImage+i*rSize+j) = *(image+(i-var1)*piSize+(j-var1));

    outFile = fopen("Resized Image.txt", "w");
    if(outFile == NULL){
      printf("Error!");
      exit(1);
   }
    for(i=0; i<rSize; i++)
        for(j=0; j<rSize; j++)
            fprintf(outFile,"%f ",*(resizedImage+i*rSize+j));
    fclose(outFile);
    printf("Resized Image!\n");

    //=============================================================== Loading Patches
    printf("Initializing Patches...\n");
    var1 = (paSize-1)/2; int wSize = piSize*piSize; int elements = paSize*paSize;
    float *patches = (float *)malloc(wSize*elements*sizeof(float));
    float patch[elements];
    for(i=var1; i<rSize-var1; i++){
        for(j=var1; j<rSize-var1; j++){
            int row = i-var1, co, ct;
            for (co=0; co<paSize; co++){
                int col = j-var1;
                for (ct=0; ct<paSize; ct++){
                    *(patch+co*paSize+ct) = *(resizedImage+row*rSize+col);
                    col++;
                }
                row++;
            }
            for(p=0; p<elements; p++)
                *(patches + counterP*elements + p) = patch[p];
            counterP++;
        }
    }
    printf("Patches Initialized!\n");

    printf("Initializing Gaussian Filter...\n");
    double *GKernel = (double *)malloc(paSize*paSize*sizeof(double));
    FilterCreation(GKernel);

    printf("Gaussian Filter Initialized\n");

    printf("Applying Gaussian Filter on Patches...\n");
    for (i=0; i<wSize; i++)
        for (j=0; j<elements; j++)
                *(patches+i*elements+j) = *(patches+i*elements+j) * GKernel[j];
    printf("Gaussian Filter Applied!\n");

    //============================================================== Calculating Weights
    printf("Calculating Weights...\n");
    float *weight = (float *)malloc(wSize*wSize*sizeof(float));
    for (i=0; i<wSize; i++)
        for (j=0; j<wSize; j++)
            *(weight + i*wSize + j) = 0;

    for (i=0; i<wSize; i++){
        for (j=0; j<wSize; j++){
            if (i<j)
                for (w=0; w<paSize*paSize; w++)
                    *(weight+i*wSize+j) += pow((*(patches+i*elements+w)- *(patches+j*elements+w)),2);
                *(weight+j*wSize+i) = *(weight+i*wSize+j);
        }
    }
    for (i=0; i<wSize; i++)
        for (j=0; j<wSize; j++)
            *(weight+i*wSize+j) = exp(-((*(weight+i*wSize+j))/filterSigma));

    float sum[wSize];
    for (i=0; i<wSize; i++)
        sum[i] = 0;

    for (i=0; i<wSize; i++)
        for (j=0; j<wSize; j++)
            sum[i] += *(weight+i*wSize+j);

    printf("Weights Calculated!\n");


    //============================================================== Creating Filtered Image
    printf("Creating Filtered Image...\n");
    float *imageF = (float *)malloc(piSize*piSize*sizeof(float));
    for (i=0; i<wSize; i++){
        for (j=0; j<wSize; j++)
            imageF[i] += (*(weight+i*wSize+j) * image[j]);
        imageF[i] = imageF[i] / sum[i];
    }
    outFile = fopen("Filtered Image.txt", "w");
    for(i=0; i<piSize; i++) {
        for(j=0; j<piSize; j++)
             fprintf(outFile,"%f ",*(imageF+i*piSize+j));
        fprintf(outFile, "\n");
    }
    fclose(outFile);
    printf("Filtered Image Created!\n");
}//==================================================================


int main(){

    float *image = (float *)malloc(piSize*piSize*sizeof(float));
    loadInputImage(image);

    non_local_means(image);

    return 0;
}
