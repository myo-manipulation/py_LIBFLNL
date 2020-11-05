//Compilation: g++ main.cpp -L lib -l FLNL -lpthread -o Server

#include <iostream>
#include <chrono>

#include "FLNL.h"


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
    double a[2];

    while(!monServer->IsConnected())
    {
        monServer->Reconnect();
        usleep(1000);

        auto t0 = std::chrono::steady_clock::now();
        while(monServer->IsConnected())
        {
            auto t1 = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> t_ms = t1-t0;
            t = t_ms.count()/1000.;
            i[0]=t;

            if(t>3)
                monServer->Send(i);

            if(monServer->IsReceivedValues())
            {
                monServer->GetReceivedValues(a);
                std::cout << t << " =? " << a[0] << " " << t-a[0] << std::endl;
            }
            if(monServer->IsReceivedCmd())
            {
                char ss[255];
                monServer->GetReceivedCmd(ss);
                printf("%s\n", ss);
                if(strcmp(ss, "magic_cmd")==0)
                {
                    monServer->Send("OK");
                }
            }
            usleep(100000);
        }
    }

    delete monServer;
}
