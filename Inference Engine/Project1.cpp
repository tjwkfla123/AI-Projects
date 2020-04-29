#include <string>
#include <stdio.h>
#include <iostream>
#include "Backwardchain.cpp"
#include "Forwardchain.cpp"

using namespace std;

int main () 
{
  cout<<"***WELCOME TO OUR MENTAL DISORDER DATABASE***"<<endl;
  cout<<"We are going to be asking series of questions and \nprovide you with the disorder as well as the treatment\n";
  cout<<"However, we might not have the disorder in our database\n";
  cout<<"Be sure to answer all the questions in CAPITAL LETTERS\n\n";

  for (int i = 1; i < 6; i++) {
    printf("Patient#%d, please answer the quetions.\n", i); 
    string disorder = Backwardchaining();
    cout<<endl;
    Forwardchaining("MENTAL DISORDER", disorder);
    cout<<endl;
  }

  return 0;
}

