//Compilation: g++ mainClient.cpp -L lib -l FLNL -lpthread -o Client
#include <iostream>
#include <time.h>

#include "FLNL.h"

double timeval_to_sec(struct timespec *ts)
{
    return (double)(ts->tv_sec + ts->tv_nsec / 1000000000.0);
}


int main()
{
	usleep(2000000);
    client *monClient;
    monClient=new client(2, 3);
    if(monClient->Connect("192.168.1.100")!=0)
    {
        exit(-1);
    }

    double i[3]={0,0,0};
    float m=0;
    double t=0;
    struct timespec ts;
    double a[6];

    while(monClient->IsConnected())
    {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        t = timeval_to_sec(&ts);
        i[0]=t;

        if(monClient->IsReceivedValues())
        {
            monClient->GetReceivedValues(a);
            std::cout << t << " =? " << a[0] << " " << t-a[0] << std::endl;
            /*for(int k=0; k<6; k++)
                std::cout << a[k] << "\t";
            std::cout << std::endl;*/
        }
        m+=0.00;
        i[2]=-4.*a[5];
        monClient->Send(i);

        if(monClient->IsReceivedCmd())
        {
            char ss[255];
            monClient->GetReceivedCmd(ss);
            printf("%s\n", ss);
        }

        if(rand()%1000==1)
            monClient->Send("magic_cmd");

        usleep(10);
    }
    std::cout <<  "Closing..." << std::endl;

    delete monClient;

    return 0;
}
