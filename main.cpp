#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <cstring>
#include "Terminal.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "Hola, Senior" << std::endl;

//    cout << "argc: " << argc <<endl;
//    for (int i=0;i<argc;i++) {
//        cout << i << ": " << argv[i] <<endl;
//    }

    Terminal terminal(argc,argv);
    return terminal.start();

    cout << "end Program" << endl;
    return 0;
}

