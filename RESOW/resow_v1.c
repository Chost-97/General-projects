#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>



void createdataset(long  Datasetsize,char * filename);
void loadDataset (long  DataSetSize, char *filename, int buffersize, float *v);
void swap(float *xp, float *yp);
void selectionSort(float *arr,long  n);
void writeDataset (long  DataSetSize, char *filename, float *v, int buffersize,float avg, float max, float min);
float max(long  datasetsize, float v[]);
float min(long  datasetsize, float v[]);
void mergeSort(float *arr, long l, long r);
void merge(float *arr, long l, long m, long r);

void main()  
{ 
    char ch;
    FILE *fp;
    int bs;
    char filein[50], fileout[50];
    char *fi=filein, *fo=fileout;
    long  datasetsize;
    char ds;
    float mini,maxi,avg;
    double sum,l, s, w;
    clock_t l1,l2,s1,s2,w1,w2;
    

    
    printf("Enter the size of the datasetsize and buffer size: ");
    scanf("%ld %d",&datasetsize,&bs); 
    printf("Enter input file name: ");
    scanf("%s",filein);
    printf("%s\n",filein);
    printf("Enter output file name: ");
    scanf("%s",fileout);
    printf("%s\n",fileout);
     
    // for(int i=1; i<2;i++)
    // {
        printf("%ld\n",datasetsize);
        float *v = malloc(datasetsize * sizeof(float));

printf("test1");

    createdataset(datasetsize,fi);

printf("test2");

    //Loading the dataset from the file 
    l1=clock();
    loadDataset(datasetsize, fi, bs, v);


    //Finding avg, max and min value of dataset
    for(long  i=0;i<datasetsize;i++)
        sum+=v[i]; 
    avg=(float)sum/datasetsize;
    maxi=max(datasetsize,v);
    mini=min(datasetsize,v);
    l2=clock();
    l= ((double) (l2-l1));

printf("test3");

    s1=clock();
    //selectionSort(v,datasetsize);
    mergeSort(v,0,datasetsize-1);
    s2=clock();
    s= ((double) (s2-s1)) ;

printf("test4");

    w1=clock();
    writeDataset(datasetsize,fo,v,bs,avg,mini,maxi);
    w2=clock();
    w= ((double) (w2-w1)) ;

printf("test5");


    
    // printf("\n Sorting starts\n");
    // for(long i=0;i<datasetsize;i++)
    //     printf("\t%f\t",v[i]);
    printf("\n");
    printf("\t%lf\t,%lf\t,%lf\t\n",l,s,w);
    free(v);

    

}

void createdataset(long  Datasetsize,char * filename)
{
    FILE *f;
printf("test11");
    float *v = malloc(Datasetsize * sizeof(float));
printf("test12");
    //create a floating point random number between 1 and 100
    srand((unsigned int)time(NULL));
printf("test121");
    for(long i = 0; i<Datasetsize;i++){ 
    printf("test122");
    v[i]=((float)rand()/(float)(RAND_MAX)) * 100;
    }
printf("test13");
    // opening the file in binary format for writing 
  
    f=fopen(filename,"wb");
printf("test14");
    fwrite(v ,sizeof(float) , Datasetsize , f);
printf("test15");
    fclose(f);
    free(v);
}

void loadDataset (long  DataSetSize, char *filename, int buffersize, float *v) 
{
    FILE *fp;
printf("test31");
    // int bs;
    // float v[DataSetSize];
    char buff[buffersize];
    int s;

printf("test32");

    // opening file in binary format for reading
    fp = fopen( filename , "rb" );
    if( fp==NULL) 
        printf("File cant be opened");

printf("test33");

    // setting up buffer
    memset(buff,'\0',buffersize*sizeof(char));
    if(setvbuf(fp, buff, _IOFBF, buffersize)!=0)
        printf("Unsucessful buffer\n");

printf("test34");

    if(fread(v , sizeof(float), DataSetSize, fp )!= DataSetSize)
        printf("UnSuccessful reading\n");


// for(long i=0;i<DataSetSize;i++)
//     printf("%f\t",v[i]);

printf("test35");

    fflush(fp);
    fclose(fp);
}

void swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}


float max(long  datasetsize, float v[])
{
    float temp=0;
    for(long i=0;i<datasetsize;i++)
    {
      if(temp<v[i])
        temp=v[i];
    }
    return(temp);
}


float min(long  datasetsize, float v[])
{
    float temp=100;
    for(long  i=0;i<datasetsize;i++)
    {
      if(temp>v[i])
        temp=v[i];
    }
    return(temp);
}

//sorting of elements
void selectionSort(float *arr,long  n)
{
   long  i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)  
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            {   
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            }
        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}


// write dataset into the file
void writeDataset (long  DataSetSize, char *filename, float *v, int buffersize, float avg, float max, float min)
{

    FILE *fp;
    char buff[buffersize];


    fp = fopen( filename , "wb" );
    if( fp==NULL) 
        printf("File cant be opened");

    //setting up buffer for writing stream
    memset(buff,'\0',(buffersize+3)*sizeof(char));
    if(setvbuf(fp, buff, _IOFBF, buffersize)!=0)
        printf("unsuccessful buffer");

    
    //writing the sorted elements into the output file
    fwrite(&avg,  sizeof(float), 1  , fp );
    fwrite(&max,  sizeof(float), 1  , fp );
    fwrite(&min,  sizeof(float), 1  , fp );

    fwrite(v , sizeof(float) , DataSetSize , fp );

    fclose(fp);
}

void merge(float *arr, long l, long m, long r) 
{ 
    long i, j, k; 
    long n1 = m - l + 1; 
    long n2 = r - m; 
    float *L=malloc(n1 * sizeof(float));
    float *R=malloc(n2 * sizeof(float)); 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    /* Merge the temp arrays back longo arr[l..r]*/
    i = 0;  
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
free(L);
free(R);
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(float *arr, long l, long r) 
{ 
    if (l < r) { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        long m = l + (r - l) / 2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m + 1, r); 
        merge(arr, l, m, r); 
    } 
} 
  























