#include <iostream>
#include <string>
#include "MathUtils.h"
#include <vector>

using namespace std;

//
// Created by Abdo Mohamed on 2021-05-05
// An integration calculator to find the best MCQ solution
// Work Idea :  ddx(int( f(x) dx )) = f(x)
//

static const string ANSI_YELLOW = "\u001B[33m";
static const string ANSI_RED = "\u001B[31m";
static const string ANSI_GREEN = "\u001B[32m";
static const string ANSI_RESET = "\u001B[0m";
static const string ANSI_WHITE = "\u001B[37m";
static const string ANSI_BOLD = "\u001b[1m";
static const string ANSI_CYAN = "\u001B[36m";

void println(const string& str){
    cout << str << ANSI_RESET << endl;
}

void print(const string& str){
    cout << str << ANSI_RESET;
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {
    MathInit();
    char in[250];

    vector<string> functions;
    vector<long double> values; //accuracy is critical !!

    long double x;

    long double v0;

    long double base_function_value;

    long double dx = 1E-10;

    long double max_green    = 1E-2;
    long double max_yellow   = 1E-1;

    //print(to_string(eval("2 (PI) ")));  //TEST

    //if (true)
    //    return 0;

    int line_size = 80;

    println(ANSI_YELLOW + "Leave a blank line to exit or to finish adding choices");
    println("");
    println(ANSI_CYAN + "1-Enter a value of x in the domain of f(x) to substitute with");
    println(ANSI_CYAN + "2-Enter the function which should be integrated");
    println(ANSI_CYAN + "3-Enter the MCQ choices");
    println("");
    println(ANSI_GREEN + "Right Answer   " + ANSI_YELLOW + "Close Answer   " + ANSI_RED + "Wrong Answer");
    println("");
    println(ANSI_BOLD + ANSI_GREEN + "coded by Abdo Mohamed :)");
    println("-------------------------------------------------------------------");


    while(true){
        functions.clear();
        values.clear();

        cin.clear();

        print(ANSI_BOLD + ANSI_WHITE + "Substitute: x = ");
        cin.getline(in , 250);
        if (cin.gcount() == 1)
            break;
        x = eval(in , (int) cin.gcount() - 1);


        print(ANSI_CYAN + ANSI_BOLD + "Function to Integrate: F(x) = ");
        cin.getline(in , 250);
        if (cin.gcount() == 1)
            break;
        setVariable("x" , x);
        base_function_value = eval(in , (int) cin.gcount() - 1);

        int index = 1;
        for (;;){
            print(ANSI_BOLD + "Choice#" + to_string(index) + ": F(x) = ");
            cin.getline(in , 250);

            if (cin.gcount() == 1) //blank line
                break;

            setVariable("x" , x);
            v0 = eval(in , (int) cin.gcount() - 1);
            setVariable("x" , x + dx);
            v0 = (eval(in , (int) cin.gcount() - 1) - v0) / dx;
            //println("F'(x) = " + to_string(v0));
            values.emplace_back(v0);
            functions.emplace_back(string(in , 0 , cin.gcount()));

            index ++;
        }
        println(ANSI_BOLD + "========================FINDING BEST ANSWER========================");

        for (int i = 0; i < values.size(); ++i) {
            if (abs(values[i] - base_function_value) <= max_green){
                println(ANSI_GREEN + functions[i]);
                continue;
            }

            if (abs(values[i] - base_function_value) <= max_yellow){
                println(ANSI_YELLOW + functions[i]);
                continue;
            }

            print(ANSI_RED + functions[i]);

            int s = line_size - (int) functions[i].length();
            for (int j = 0; j < s; ++j) {
                std::cout << " ";
            }
            println( ANSI_BOLD + " offset=" + to_string(values[i] - base_function_value));

        }

        println(ANSI_BOLD + "===================================================================");

    }

    return 0;
}
#pragma clang diagnostic pop
