// #simulasi kendali PID
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
    //y=0.04676 * *xn + 0.0476 * *xn1 + 0.9048 * *yn1;
    y=0.00498 * *xn + 0.00498 * *xn1 + 0.99005 * *yn1;
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
    float setpoint=0.5;
    float error;
    float Kp;
    float posisi=0;
    Kp=0.01;
    y=0;
    t=-1;
    period=0.01;

    fp = fopen ("win10-filter.csv", "w+");
    fprintf(fp,"t,xn,yn,posisi\n",t,xn,y);

    filter_init(&xn1,&yn1);

    for (i=0; i<2000; i++)
    {
        t=t+period;

        if(t<0)
            setpoint=0;
        else
            setpoint=1;

        error=setpoint-posisi;
        xn=Kp*error;

        y=filter_run(&xn,&xn1,&yn1);
        posisi=posisi+y;
        fprintf(fp,"%f,%f,%f,%f\n",t,xn,y,posisi);
    }
    fclose(fp);
    return 0;
}
