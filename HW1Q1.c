#include<stdio.h>
#include<stdlib.h>

void print_to_file(int**A,int n,int format_flag){
    char filename[30];
    FILE*fptr;
    int i,j;
    if (format_flag==0){
        snprintf(filename,sizeof(filename),"array_%06d_asc.out",n);
        fptr=fopen(filename,"w");
        if(fptr==NULL){
            printf("Unable to create file\n");
            return;
        }
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                fprintf(fptr,"%.15f ",(double)A[i][j]);
            }
            fprintf(fptr,"\n");
        }
    }
    else if(format_flag==1){
        snprintf(filename,sizeof(filename),"array_%06d_bin.out",n);
        fptr=fopen(filename,"wb");
        if(fptr==NULL){
            printf("Unable to create file\n");
            return;
        }
        for(i=0;i<n;i++){
          fwrite(A[i],sizeof(double),n,fptr);
        }

    }
    else{
        printf("Invalid format_flag!");
        return;
    }
    fclose(fptr);
    return;
}


int main(){
    FILE* fptr;
    fptr=fopen("input.in","r");
    if(fptr==NULL){
        printf("This file can't be opened!");
        return 0;
    }
    //printf("File created successfully!\n");
    int n;
    
    
    //change
    int format_flag=1;
    
    
    fscanf(fptr,"%d",&n);
    //printf("n is %d\n",n);
    fclose(fptr);
    int**A=(int**)(malloc(n*sizeof(int*)));
    int i,j;
    for(i=0;i<n;i++){
        A[i]=(int*)(malloc(n*sizeof(int)));
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            A[i][j]=i+j+2;
        }
    }
    print_to_file(A,n,format_flag);
    return 0;
}