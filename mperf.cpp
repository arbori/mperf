#include <iostream>

#include "application.hpp"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cout << "Usage: mperf <avaliation_limit> <interation_limit> \n";
    }
    else 
    {
        mperf::application_context app(argc, argv);

        app.start();
    }

    return 0;
}
