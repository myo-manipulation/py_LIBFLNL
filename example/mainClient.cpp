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


    double i[2]={2, 3};
    float m=0;
    double t=0;
    struct timespec ts;
    double a[3];

    while(monClient->IsConnected())
    {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        t = timeval_to_sec(&ts);

		//m+=0.00001;
        i[0]=t;
        //i[2]=m*9.8;
        monClient->Send(i);

        if(monClient->IsReceivedValues())
        {
            monClient->GetReceivedValues(a);
            std::cout << t << " =? " << a[0] << " " << t-a[0] << std::endl;
        }
        usleep(10);
    }
    std::cout <<  "Closing..." << std::endl;

    delete monClient;

    return 0;
}
