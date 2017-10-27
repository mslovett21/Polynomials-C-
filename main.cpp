/*******************************************************************************
  Title          : main.cpp
  Author         : Patrycja Krawczuk
  Created on     : February 10th, 2017
  Description    : Main for the program
  Purpose        : This program : multiplies polynomials with integer coefficients,
                   evaluates the polynomials, prints stored data. 
  Usage          : Multiplying polynomials, provide file with commands as argument
  Build with     : makefile, (g++ -std=c++11)
  Modifications  : March 16th, 2017 Added :delete_whitespace function to correct parsing,
                   additional if statements to avoid seg fault if user tries to access arguments out of range of the vector

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <locale>
using namespace std;

#include "polynomial.h"


/** check_the_vector_size(int a, int b, int c, int size) 
* Finds the biggest number among three provided indices and current vector size.
*   @param  int   [in]  a  - index of vector for storing or accessing a polynomial
*           int   [in]  b  - index of vector for storing or accessing a polynomial
*           int   [in]  c  - index of vector for stroing or accessing a polynomial
*           int   [in]  size - current of vector poly
* @pre    provided arguments are positive integers
* @post   the highest number amongst the three is found
* @returns the higest number plus 1
*/
int check_the_vector_size(int a, int b, int c, int size);

/** delete_whitespace(string line_from_file, vector<string>& v);
* Finds the biggest number among three provided indices and current vector size.
*   @param  string            [in]  line_from_file  - string retrived from the input file via getline (data separeted by whitespace)
*           vector<string>&   [inout]  v -stores content of line_from_file after deletion of whitespace  
* @pre    an empty vector v was created
* @post   v consist of content of the single line of the file after deleleting whitespaces.
*/
void delete_whitespace(string line_from_file, vector<string>& v);

int main(int argc, char* argv[])
{

// Check the number of parameters
  if (argc < 2) 
  {   // Tell the user how to run the program- The program needs 2 arguments: name_of_program, commands_file
        cerr << "Usage (2 arguments): " << argv[0] << " command_file "<<endl;
  return 1;
  }
   
  ifstream data_file (argv[1]);
  //check if command file opens succesfully;
  if (data_file.is_open())
     {  } 
  else
  {
    cerr<<"File 1 "<<argv[1]<<" cannot be opened!"<<endl;
    return 1;
  }
  
  cout<<"The results of the calculations are as follow: "<<endl;
  vector<Polynomial> poly;

  for (int i=0; i<100; i++)
  {
    poly.push_back(Polynomial(0,0));
  }

 
  istringstream myiss;
  string temp_line;
  string temp_string, no_whitepace_string;
  vector<string> temp_vector;
  int position;

  //*********************************************************
  //* READ IN DATA FROM THE FILE                            *
  //*********************************************************
  while(getline(data_file, temp_line))
  {

         delete_whitespace(temp_line, temp_vector);

         if (temp_vector[0] == "print")
         {
           int x=stoi(temp_vector[1]);
           if (x<poly.size())
            {
            cout<<"Poly["<<x<<"] =";
            cout<<poly[x]<<endl;
            }
            else
            {
              cerr<<"You cannot access indices higher than current size of the vector minus one (default size 100)."<<endl;
              cerr<<"If you want to resize the vector you neeed to first allocate data in the new max index of the vector by means of multiplication operation"<<endl;
            }

         }
         else if (temp_vector[0] == "eval")
         {
           double result;
           position=stoi(temp_vector[1]);
           double y=stod(temp_vector[3]);
           if (position< poly.size())
           {
           result=poly[position].eval(y);
           cout<<"Polynomial["<<position<<"] ("<<y<<") ="<<fixed<<setprecision(2)<<result<<endl;
           }
           else
           {
            cerr<<"You cannot access indices higher than current size of the vector minus one (default size 100)."<<endl;
           }
         }
         else if (temp_vector[1] == ":")
         {

          position=stoi(temp_vector[0]);
          if(position<poly.size())
          { 
          Polynomial new_poly(temp_vector);
          poly[position]=new_poly;
          }
          else
          {
            cerr<<"You cannot access indices higher than current size of the vector minus one (default size 100)."<<endl;
          }

         }
         else if(temp_vector[1] == "=")
         {
          position=stoi(temp_vector[0]);
          int positionA=stoi(temp_vector[2]);
          int positionB=stoi(temp_vector[4]);
          int current_size=poly.size();
          int new_size=check_the_vector_size(position, positionA, positionB, current_size);
     
              if (new_size != current_size)
              {
                  try
                  { 
                    poly.resize(new_size, Polynomial(0,0));
                  }
                  catch (bad_alloc &e)
                  {
                    cout<<"Failed to allocate vector of size"<<new_size<<endl;
                    cout<<"Exception: "<<e.what()<< "\n";
                    break;
                  }
                  poly.at(position)=poly.at(positionA) * poly.at(positionB);
              }
              else
              {
              
                 poly.at(position)=poly.at(positionA) * poly.at(positionB);
              }
          }
         else
         {
          cout<<"Undefined instruction. Proceeding to the next instruction."<<endl;
         }
      
         temp_vector.clear();
        
    }

   data_file.close();
  
	return 0;
}


int check_the_vector_size(int a, int b, int c, int current_size)
{
  int v_size=current_size;
  int new_size=current_size;
//Find max
  if ((a>v_size) || (b>v_size) || (c>v_size))
  {
    if (a>b)
    {
      if(a>c)
        new_size=a;
      else
       new_size=c;
    }
    else
    {
      if(b>c)
        new_size=b;
      else
       new_size=c;
    }
  }
  //return max plus 1 since you are provided in index
  return new_size+1;
}



void delete_whitespace(string line_from_file, vector<string>& v)
{

  int i=0; 
  while(i<line_from_file.size())
  {
    string temp="";
    while((isspace(line_from_file[i])==false) && (i<line_from_file.size()))//white not a whitespace
    {
      temp=temp+line_from_file[i];
      i++;
    }
    if(temp.size()>0)//I actually found some valid content
    {
      v.push_back(temp);
    }
    i++;
  }

}