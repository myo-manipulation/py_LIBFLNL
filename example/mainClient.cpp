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
    monClient=new client(3, 6);
    if(monClient->Connect("192.168.6.2")!=0)
    {
        exit(-1);
    }

    double i[3]={0,0, 0};
    float m=0;
    double t=0;
    struct timespec ts;
    double a[6];

    while(monClient->IsConnected())
    {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        t = timeval_to_sec(&ts);

		m+=0.00001;
        i[2]=m*9.8;
        monClient->Send(i);

        if(monClient->IsReceivedValues())
        {
            monClient->GetReceivedValues(a);
            //std::cout << t << " =? " << a[0] << " " << t-a[0] << std::endl;
            for(int k=0; k<6; k++)
                std::cout << a[k] << "\t";
            std::cout << std::endl;
        }
        usleep(10);
    }
    std::cout <<  "Closing..." << std::endl;

    delete monClient;

    return 0;
}
