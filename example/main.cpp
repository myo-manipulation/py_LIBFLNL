//Compilation: g++ main.cpp -L lib -l FLNL -lpthread -o Server

#include <iostream>
#include <time.h>

#include "FLNL.h"

double timeval_to_sec(struct timespec *ts)
{
    return (double)(ts->tv_sec + ts->tv_nsec / 1000000000.0);
}

int main()
{
    server *monServer;
    monServer=new server(3, 2);

    if(monServer->Connect("192.168.1.100")!=0)
    {
        exit(-1);
    }



    double i[3];
    i[0]=0.1;i[1]=0;i[2]=0;
    double t=0;
    struct timespec ts;
    double a[2];


    while(!monServer->IsConnected())
    {
        monServer->Reconnect();
        usleep(1000);

        while(monServer->IsConnected())
        {
            clock_gettime(CLOCK_MONOTONIC, &ts);
            t = timeval_to_sec(&ts);

            i[0]=t;
            if(t>3)
                monServer->Send(i);

            if(monServer->IsReceivedValues())
            {
                monServer->GetReceivedValues(a);
                std::cout << t << " =? " << a[0] << " " << t-a[0] << std::endl;
            }
            usleep(100000);
        }
    }

    delete monServer;
}
