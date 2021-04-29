/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Tim
 *
 * Created on 15 October 2016, 22:55
 */

#include <cstdlib>
#include <iostream>
#include <thread>

using namespace std;

/*
 * 
 */

void message() {
    
    cout << "Hello from a thread..." << endl;
}

int main() {
    thread t1{message};
    
    t1.join();

    return 0;
}

