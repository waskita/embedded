#include <stdio.h>
#include <stdlib.h>

// inisialisasi filter digital

void filter_init(float *xn1,float *yn1)
{
    *yn1=0;
    *xn1=0;
}

// hitung output filter digital filter digital
// delayed variabel diberikan sebagai parameter
float filter_run(float *xn,float *xn1,float *yn1)
{
    float y;
    y=0.04676 * *xn + 0.0476 * *xn1 + 0.9048 * *yn1;
    *yn1=y;
    *xn1=*xn;
    return y;
}

int main()
{
    FILE * fp;
    float y,xn,xn1,yn1;
    int i;
    float t;
    float period;
    t=-1;
    period=0.01;


    fp = fopen ("win10-filter.csv", "w+");
    fprintf(fp,"t,xn,yn\n",t,xn,y);

    filter_init(&xn1,&yn1);

    for (i=0; i<200; i++)
    {
        t=t+period;
        if(t<0)
        {
            xn=0;
        }
        else
        {
            xn=1;
        }
        y=filter_run(&xn,&xn1,&yn1);
        fprintf(fp,"%f,%f,%f\n",t,xn,y);
    }
    fclose(fp);
    return 0;
}
