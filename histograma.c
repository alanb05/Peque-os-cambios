#include <stdio.h>
#include <stdlib.h>

void GeneradorAleatorio(double *Numaleat,int a,int b,int N)
{

    /* Generacion de N numeros random en el intervalo [a,b)*/

    int i;
    for(i=0; i<N; i++)
    {

        Numaleat[i]=a+(b-a)*(rand()/((double)RAND_MAX+1)); /*Pq me sale bien solo si quito el +1??*/
    }
}


void Histogram(double *data, double *Hist, int N_data, int N_intervalos, double *d, double *m, double *M)
{

    int i, Indice;
    double min,max,delta, Norm;
    min=1000000;
    max=-1000000;
    for(i=0; i<N_intervalos; i++)Hist[i]=0;
    for(i=0; i<N_data; i++)
    {
        if(data[i]<min)min=data[i];
        if(max<data[i])max=data[i];
    }
    delta=(max-min)/N_intervalos;


    if (delta==0)printf("Error: No se pueden calcular los intervalos; Max=%lf, Min=%lf\n",max,min);

    for(i=0; i<N_data; i++)
    {

        Indice=(data[i]-min)/delta;
        if(Indice==N_intervalos)Indice=N_intervalos-1;
        Hist[Indice]++;
    }

    *d=delta;
    *m=min;
    *M=max;

    Norm=1.0/(N_data*delta);
    for(i=0; i<N_intervalos; i++)Hist[i]*=Norm;
}


int main ()
{
   /* int N=10000,i;
    double data[N],min,max,delta;
    GeneradorAleatorio(data,3,10,N);

    int N_intervalos=100;
    double Histograma[N_intervalos];
    Histogram(data,Histograma,N,N_intervalos,&delta,&min,&max);

    FILE*f=fopen("histogr.txt","w");
    for (i=0; i<N_intervalos; i++)
    {
        fprintf(f,"%lf %lf\n ",min+delta*i,Histograma[i]);
    }

    fclose(f);
    return 0;*/

    /*Pequeños cambiossss*/
    int N=10000,i;
    double data[N],min=3,max=10,delta,nombre,epsilon=0.1,cambio,x0;
    x0=min+(max-min)*(rand()/((double)RAND_MAX+1));
    data[0]=x0;

    int N_intervalos=100;
    double Histograma[N_intervalos];
    FILE*f=fopen("hist.txt","w");

    for(i=1;i<N;i++){
        cambio=epsilon*2*(rand()/((double)RAND_MAX+1));
        data[i]=data[i-1]+cambio;
        if(data[i]>max)data[i]=data[i]-(max-min);
        if(data[i]<min)data[i]=data[i]+(max-min);
    }
    Histogram(data,Histograma,N,N_intervalos,&delta,&min,&max);
     for (i=0; i<N_intervalos; i++)
    {
        fprintf(f,"%lf %lf\n ",min+delta*i,Histograma[i]);
    }

    fclose(f);
    return 0;
    
    /*GNUPLOTTTT
    a=3
    b=10
    set yrange[0:1]
    plot "hist.txt" u 1:2 w boxes, 1.0/(b-a)
    */
}

