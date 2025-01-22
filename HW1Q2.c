#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int get_n(){
    FILE*fptr;
    //enter input file here
    fptr=fopen("input.in","r");
    if(fptr==NULL){
        printf("Unable to open input file");
        return 0;
    }
    int n;
    fscanf(fptr,"%d",&n);
    fclose(fptr);
    return n;
}

double**get_matrix(int n){
    double** matrix=(double**)(malloc(n*sizeof(double*)));
    int i;
    for(i=0;i<n;i++){
        matrix[i]=(double*)(malloc(n*sizeof(double)));
    }
    return matrix;
}

void free_matrix(double** matrix,int n){
    int i;
    for(i=0;i<n;i++){
        free(matrix[i]);
    }
    free(matrix);
    return;
}

void read_from_matrix_file(const char*filename,double**matrix,int n){
    //printf("Matrix filename: %s\n",filename);
    FILE*fptr;
    fptr=fopen(filename,"r");
    if(fptr==NULL){
        printf("Unable to open matrix file!");
        exit(EXIT_FAILURE);
    }
    int i,j;
    for(i=0;i<n;i++){
        char a;
        for(j=0;j<n;j++){
            if(j==(n-1)){
                fscanf(fptr,"%le",&matrix[i][j]);
                //printf("%.15e ",matrix[i][j]);
            }
            else{
                fscanf(fptr,"%le,",&matrix[i][j]);
                //printf("%.15e ",matrix[i][j]);
            }
        }
        //printf("\n");
        fscanf(fptr,"%c",a);
    }
    fclose(fptr);
    return;
}

void read_from_vector_file(const char*filename,double*vector,int n){
    FILE*fptr;
    fptr=fopen(filename,"r");
    if(fptr==NULL){
        printf("Unable to open vector file");
        exit(EXIT_FAILURE);
    }
    int i;
    for(i=0;i<n;i++){
        if(i==n-1){
            fscanf(fptr,"%le",&vector[i]);
            //printf("%.15e ",vector[i]);
        }
        else{
            fscanf(fptr,"%le,",&vector[i]);
            //printf("%.15e ",vector[i]);
        }
    }
    //printf("\n");
    fclose(fptr);
    return;
}

int is_eigenvector(double** matrix,double*vector,int n, double*eigenvalue){
    double*res_vec=(double*)(malloc(n*sizeof(double)));
    int i,j;
    for(i=0;i<n;i++){
        res_vec[i]=0;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            res_vec[i]+=matrix[i][j]*vector[j];
        }
    }
    int first_nonzero=-1;
    for(i=0;i<n;i++){
        if(fabs(vector[i])>1e-12){
            first_nonzero=i;
            *eigenvalue=res_vec[i]/vector[i];
            break;
        }
    }
    if(first_nonzero==-1){
        //zero vec
        free(res_vec);
        return 0;
    }
    for(i=0;i<n;i++){
        if(fabs(vector[i])>1e-12){
            double ratio=res_vec[i]/vector[i];
            if(fabs(ratio-*eigenvalue)>1e-12){
                free(res_vec);
                return 0;
            }
        }
        else{
            if(fabs(res_vec[i])>1e-12){
                free(res_vec);
                return 0;
            }
        }
    }
    free(res_vec);
    return 1;
}

void append_to_vector_file(const char *filename,double eigenvalue){
    FILE*fptr=fopen(filename,"a");
    fprintf(fptr,"\n%.15e",eigenvalue);
    //printf("Appended!\n");
    fclose(fptr);
    return;
}

int main(){
    int n=get_n();
    double** A=get_matrix(n);
    char filename[50];
    snprintf(filename,sizeof(filename),"inputfiles/mat_%06d.in",n);
    //printf("%s\n",filename);
    read_from_matrix_file(filename,A,n);
    int vecnum=1;
    while(1){
        char vec_filename[50];
        snprintf(vec_filename,sizeof(vec_filename),"inputfiles/vec_%06d_%06d.in",n,vecnum);
        FILE*vec=fopen(vec_filename,"r");
        if(!vec){
            break;
        }
        fclose(vec);
        double*vector=(double*)(malloc(n*sizeof(double)));
        read_from_vector_file(vec_filename,vector,n);

        double eigenvalue;
        if(is_eigenvector(A,vector,n,&eigenvalue)){
            printf("vec_%06d_%06d.in : Yes :%.15e\n",n,vecnum,eigenvalue);
            append_to_vector_file(vec_filename,eigenvalue);
        }
        else{
            printf("vec_%06d_%06d.in : Not an eigenvector\n",n,vecnum);
        }
        free(vector);
        vecnum++;
    }
    free_matrix(A,n);
    return 0;
}
