//Compilation: g++ mainClient.cpp -L lib -l FLNL -lpthread -o Client
#include <iostream>
#include <chrono>

#include "FLNL.h"


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
    double a[6];
    double t;
    auto t0 = std::chrono::steady_clock::now();

    while(monClient->IsConnected())
    {
        auto t1 = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> t_ms = t1-t0;
        t = t_ms.count()/1000.;
        i[0] = t;

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
