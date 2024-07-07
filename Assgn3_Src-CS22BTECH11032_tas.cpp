#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<thread>
#include<pthread.h>
#include<sys/time.h>
#include<atomic>
#define inputFile "input.txt"
using namespace std;
int N=0;
int K=0;
int rowInc=0;
//the command variable that stores the current number of rows evaluated
int commonV=0;
vector<vector<int>> mat;
vector<vector<int>> square;
atomic_flag lock = ATOMIC_FLAG_INIT;


void* chunkMethod(void* arg) {
    do{
        //variable to store the row numbers the to be evaluated
        int rowNumber=0;
        while(lock.test_and_set());

        /* CRITICAL SECTION*/
            rowNumber=commonV;
            commonV+=rowInc;
        /* CRITICAL SECTION END*/

        lock.clear();
        /*REMAINDER SECTION*/
        int t = *static_cast<int*>(arg);
        int start = rowNumber;
        int end = rowNumber+rowInc;
        // taking care of the last chunk
        end = min(end, N);
        // Muiltiplying the matrix
        for (int i = start; i < end; i++) {
            for (int j = 0; j < N; j++) {
                // initializing the result matrix to 0
                (square)[i][j] = 0; 
                for (int k = 0; k < N; k++) {
                    (square)[i][j] += (mat)[i][k] * (mat)[k][j];
                }
            }
        }
        //checking if all the rows are evaluated
        if(commonV>=N) break;
    } while (commonV<N);
    // exiting the thread
    pthread_exit(0);
}


void printOutput(vector<vector<int>> square,int N,double time,string outFile){
    ofstream outfile(outFile);
    if(!outfile.is_open()){
        cout<<"Unable to open output file"<<endl;
        return ;
    }
    //printing the matrix
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            outfile<<square[i][j]<<" ";
        }
        outfile<<endl;
    }
    //printing time
    outfile<<"Time taken: "<<time<<" microseconds"<<endl;
    outfile.close();
}


int main(){
    ifstream file(inputFile);
    if(!file.is_open()){
        cout<<"Unable to open file"<<endl;
        return 0;
    }
    //reading n,k from the file
    file>>N>>K>>rowInc;
    
    //  Initialize mat and square with zeros
    mat=vector<vector<int>>(N,vector<int>(N,0));
    square=vector<vector<int>>(N,vector<int>(N,0));
    if(K<=0 || N<=0){
        cout<<"Invalid Input"<<endl;
        return 0;
    }
    // reading matrix from the file
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            file>>(mat)[i][j];
        }
    }
    file.close();

    //variablef for time calculation
    struct timeval start, end;
    
    //arrays to store tids and attributes
    vector<pthread_t> tid1(K);
    vector<pthread_attr_t> attr1(K);
    vector<int> ii(K);

    ////////////////////////////////////////////
    //--------------Chunk method--------------//
    ////////////////////////////////////////////

    //start time
    gettimeofday(&start, NULL);

    // Chunking method
    for(int i=0;i<K;i++){
        ii[i]=i;
        pthread_attr_init(&attr1[i]);
        pthread_create(&tid1[i], &attr1[i], chunkMethod, &ii[i]);
    }
    //joining all the threads
    for(int i=0;i<K;i++){
        pthread_join(tid1[i],NULL);
    }
    gettimeofday(&end, NULL);
    //end time
    //time taken
    long long time = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec) ;
    cout<<time<<endl;
    // printing output
    printOutput(square,N,time,"tasOut.txt");


}