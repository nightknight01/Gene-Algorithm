//
//  main.c
//  DemoC
//
//  Created by CHIA-HUNG LEE on 2020/10/2.
//  Copyright © 2020 CHIEH-HUNG LEE. All rights reserved.
//
//#include <conio.h> only for MSDOS
// This is a comment adding test
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define M 4
#define N 10
#define reincarnation 1000

int farm[M][N];
int temp[2][N];
double a=0.0;
double b =32;
double x_value[M];
double f_value[N];
double x_temp[2];
double f_temp[2];

void setup() // 基因農場
{
    time_t t;
    int j, k;
    srand((unsigned)time(&t));
    for(j=0; j<M; j++){
        for(k=0; k<N; k++){
            farm[j][k]= rand()%2;  // random produce 0 or 1 產生基因pool
        }
    }
}
void compute_f_value(int i) {// count原始基因字串temp適應函數值
    int j,k;
    double m, x;
    m=0.0;
    for (j=0;j<N;j++){
        k=j;
        m= m+farm[i][N-j-1]*pow(2.0,k);
    }
    x_value[i] =a+m*(b-a)/(pow(2.0,N)-1.0);
    x= x_value[i];
    f_value[i] =x*x;
}
    void compute_f_temp(int i){  // count交配與突變後的基因字串temp適應函數值暫存
    int j,k;
    double m,x;
    m=0.0;
    for (j=0;j<N;j++){
        k=j;
        m=m+temp[i][N-j-1]*pow(2.0,k);
    }
        x_temp[i]=a+m*(b-a)/(pow(2.0,N)-1.0);
        x=x_temp[i];
        f_temp[i]=x*x;
}
    void crossing()  //基因交配
    {
        int r1, r2, r3, j;
        r1 =rand()%M; //挑選基因序
        r2 =rand()%M;
        while (r2==r1){
            r2=rand()%M;
        }
        for(j=0;j<N;j++){ // 講將選取到的2個基因字串copy至array中
            temp[0][j]= farm[r1][j];
            temp[1][j]= farm[r2][j];
        }
        r3 =rand()%(N-2)+1; // 隨機選擇欲交配的位置r3
        for (j=r3; j<N; j++){
            temp[0][j]= farm[r2][j];
            temp[1][j]= farm[r1][j];
        }
        compute_f_temp(0); //算交配後適應值
        compute_f_temp(1);
        if(f_temp[0]>f_value[r1]){ //比較突變後與原始適應值大小
            for(j=0;j<N;j++){
                farm[r1][j]=temp[0][j]; //保留適應值最大的基因序
            }
        }
        if(f_temp[1]>f_value[r2]){
            for (j=0;j<N;j++){
                farm[r2][j]=temp[1][j];
            }
        }
    }
void mutate()  //突變算法:單點突變
{
    int rn, rm;
    double a1, a2;
    rn= rand()%N;
    rm= rand()%M;
    a1 = f_value[rm]; //讀出目前基因序地適應值
    farm[rm][rn] =1-farm[rm][rn];
    compute_f_value(rm); // 計算單點突變後的適應值
    a2=f_value[rm]; //示計算適應值
    if(a1>a2) farm[rm][rn]=1-farm[rm][rn];
}

void print_farm() // 基因列隊
{
    int i,j;
    for(i=0;i<M;i++){
        printf("farm[%2d]=",i);
        for(j=0;j<N;j++){
            printf("%d", farm[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void print_value() //基因優劣值機算
{
    int i;
    for (i=0;i<M;i++){
        compute_f_value(i); //計算適應值
        printf("x_value[%2d]=%8.4f",i,x_value[i]); //計算基因序值
        printf("f_value[%2d]=%8.4f\n",i,f_value[i]); //計算
    }
    printf("\n");
}

void print_max()
{
    int i;
    double x_max, f_max;
    x_max =x_value[0];
    f_max= f_value[0];
    for (i=1;i<M;i++){
        if(f_value[i]>f_max){
        x_max= x_value[i];
        f_max= f_value[i];
        }
    }
    printf("x_max=%8.4f f_max=%8.4f\n\n", x_max, f_max);
}

int main(void)
{
    int i ;
    setup(); //基因農場
    print_farm();  // 基因列隊
    printf("===GA Run Before====\n");
    print_value(); //基因優劣值計算
    
    for(i=0; i< reincarnation; i++){
        crossing();
        mutate();
    }
    printf("===GA Run After ===\n");
    print_value();
    print_max();
    
   // getcha();
    return 0;
    
    
}



