/*******************************************************************************
  Title          : polynomial.cpp
  Author         : Patrycja Krawczuk
  Created on     : February 5th, 2017
  Description    : Interface to the Poolynomial and Term class, definition of Term class
  Purpose        : To provide methods for processing polynomials and terms
  Usage          : 
  Build with     : makefile
  Modifications  : 

 
*******************************************************************************/


#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include "polynomial.h"
using namespace std;

class Term
{
public:

/**Term () - default constructor*/
Term();

/**Term (int coef, int expo) - 
*   @param  int   [in]  coef  - coefficient of one of the polynomial's terms 
*           int   [in]  expo  - exponent of one of the polynomial's terms
* Object of class Term is created with provided parameters
*/
Term(int coef, int expo);

/**Term(const Term& object)- copy constructor for the class 
*   @param  Term const  [inout]  object  - object of the the class to be copied 
* New object of class Term is created, a copy of provided argument
*/
Term(const Term& object);

/**Term() - default deconstructor for the class*/
~Term();


/**operator *(Term& RHS_term) - overload operator * for Term objects 
* Multiplies coefficients and adds the exponents. Stores the result in a new object Term
*   @param  Term   [inout]  RHS_term  
* @pre    none
* @post   Two terms are multiplied, new object storing the result is created
* @returns object of class Term with the results of the operation
*/
Term operator *(Term& RHS_term);

/**operator +(Term& RHS_term) - overload operator + for Term objects 
* Adds coefficients of two terms with the same exponent and adds the exponents. Stores the result in a new object Term
*   @param  Term   [inout]  RHS_term  
* @pre    calling Term and the Term passed by reference have equel exponent power
* @post   Two terms are added
* @returns object of class Term with the results of the operation
*/
Term operator +(Term& RHS_term);


/** get_coefficient() -getter function for the class
* @returns value of calling Term coefficient
*/
int get_coefficient();

/** get_exponent() -getter function for the class
* @returns value of calling Term exponent
*/
int get_exponent();


/**operator =(Term& RHS_term) - overload assigment operator 
* Modifies the calling object by assigning to it a copy of an object passed be reference
*   @param  Term [inout]  RHS_term  - object to copy
* @pre    none
* @post   Calling object is assigned the copy of RHS_term
* @returns void
*/
void operator =(const Term& RHS_term);


/** operator <<(ostream& write_stream, Term& term_to_print) -friend function
* Prints term to the screen
* Format:  3x^6, -5x^4, x^3, -1
*   @param  ostream    [inout]  write_stream
            Term       [input]  term_to_print
* @pre    working open stream is provided
* @post   Term object is printed to the screen
* @returns ostrem&
 */
friend ostream& operator <<(ostream& write_stream, Term& term_to_print);

/**operator < (Term& RHS_term);
*   @param  Term   [inout]  RHS_term  object storing coefficent and exponent  
* @returns true if the calling object's exponent is less than RHS_term's exponent
 */
bool operator < (Term& RHS_term);

/**operator > (Term& RHS_term);
*   @param  Term   [inout]  RHS_term  object storing coefficent and exponent  
* @returns true if the calling object's exponent is bigger than RHS_term's exponent
 */
bool operator > (Term& RHS_term);

/**operator == (Term& RHS_term);
*   @param  Term   [inout]  RHS_term  object storing coefficent and exponent  
* @returns true if the calling object's exponent is equel to RHS_term's exponent
 */
bool operator ==(Term& RHS_term);
  
private:
//private data members
int coefficient;

int exponent;
  
};

Term::Term()
{
	coefficient=5;
	exponent=5;
}

Term::Term(int coef, int expo)
{
	coefficient=coef;
	exponent=expo;
}

Term::Term(const Term& object)
{
	coefficient=object.coefficient;
	exponent=object.exponent;
}

Term::~Term()
{

}

int Term:: get_coefficient()
{
	return coefficient;
}


int Term:: get_exponent()
{
	return exponent;
}

Term Term:: operator *(Term& RHS_term)
{
	Term temp_pol;
	temp_pol.coefficient=coefficient * RHS_term.coefficient;
	temp_pol.exponent=exponent+RHS_term.exponent;
	
	return temp_pol;
}

Term Term:: operator +(Term& RHS_term)
{
	Term new_term;
	new_term.exponent=exponent;
	new_term.coefficient=coefficient+RHS_term.coefficient;

	return new_term; 
}

//RHS is passed by reference, LHS is edited
void Term::operator =( const Term& RHS_term)
{
	coefficient=RHS_term.coefficient;
	exponent=RHS_term.exponent;
}

bool Term::operator < (Term& RHS_term)
{
	if (exponent < RHS_term.exponent)
		return true;
	else
		return false;
}

bool Term:: operator > (Term& RHS_term)
{
	if (exponent > RHS_term.exponent)
		return true;
	else
		return false;
}

bool Term:: operator ==(Term& RHS_term)
{
	if ((exponent==RHS_term.exponent) &&(coefficient==RHS_term.coefficient))
		return true;
	else
		return false;
}

ostream& operator <<(ostream& write_stream, Term& term_to_print)
{
	if(term_to_print.coefficient != 1){
	   write_stream<<term_to_print.coefficient;}

   if((term_to_print.exponent != 0) && (term_to_print.exponent != 1) 
   	  && (term_to_print.coefficient != 0))
     {
	   write_stream<<"x^";
	   write_stream<<term_to_print.exponent<<" ";
     }
    else if (term_to_print.exponent == 1)
    {
    	write_stream<<"x";
    }
    else if (term_to_print.coefficient ==1)
    {
    	write_stream<<term_to_print.coefficient;
    }

	return write_stream;
}
  

Polynomial::Polynomial()
{

	Term temp(0,0);
	poly_terms.push_back(temp);	
}

Polynomial::Polynomial(int coef, int expo)
{
	Term temp(coef,expo);
	poly_terms.push_back(temp);
}


Polynomial::Polynomial(const Polynomial& object)
{
	list<Term>::const_iterator iter_orginal;

	for( iter_orginal = object.poly_terms.begin(); iter_orginal!= object.poly_terms.end(); iter_orginal++)
	{
		poly_terms.push_back(*iter_orginal);	
	}
}

Polynomial::Polynomial(vector <string>& v)
{
	int coefficient, exponent;
	for (int n=2; n<v.size(); n+=2)
        {
            coefficient=stoi(v[n]);
            exponent= stoi(v[n+1]);
            Term temp(coefficient, exponent);
            poly_terms.push_back(temp);
        }
        prepare_to_store();

}

Polynomial::~Polynomial()
{
	poly_terms.clear();
}

double Polynomial:: eval(double x)
{
	Polynomial poly=*this; 
	//calll to overload operator ()
	double sum=poly(x);
	return sum;

}

double Polynomial:: operator()(double y)
{
	list<Term>::iterator iter;
	double sum=0.00;
	Term temp;
	int coef, expo;

	for( iter = poly_terms.begin() ; iter != poly_terms.end() ; iter++)
	{
		temp=*iter;
		coef=temp.get_coefficient();
		expo=temp.get_exponent();
		sum=sum+coef*pow(y,expo);
	}

	return sum;
}


Polynomial Polynomial::operator *(Polynomial& RHS_polynomial)
{
	
	Polynomial result;
	list<Term>::iterator iter_RHS, iter_LHS;

	for( iter_LHS =poly_terms.begin(); iter_LHS !=poly_terms.end(); iter_LHS++)
	{
	   for(iter_RHS =RHS_polynomial.poly_terms.begin(); iter_RHS != RHS_polynomial.poly_terms.end(); iter_RHS++)
	   {
	   		result.poly_terms.push_back((*iter_LHS)*(*iter_RHS));
	   }
	}

	result.poly_terms.sort(my_compare);
	result=result.term_addition();
	result.remove_zero_terms();
	return result;
}


ostream& operator <<(ostream& write_stream, Polynomial& polynomial_to_print)
{
	list<Term>::iterator iterA;
	
	for(iterA=polynomial_to_print.poly_terms.begin(); iterA !=polynomial_to_print.poly_terms.end(); iterA++)
	   {
	   	 if (iterA != polynomial_to_print.poly_terms.begin())
	   	     {
	   	     	write_stream<<" + "<<*iterA;
	   	     }
	   	 else cout<<" "<<*iterA;
	   }

return write_stream;
}


Polynomial Polynomial:: term_addition()
{
	list<Term>::iterator iter_old;
	iter_old=poly_terms.begin();

	Polynomial result;

	int temp_exponent;
	int temp_coefficient;
   //adds terms as long as they have equel exponents
	while(iter_old !=poly_terms.end())
	{
		Term temp_term, temp_term2;
		temp_term=*iter_old;
		
		temp_exponent=temp_term.get_exponent();
		temp_coefficient=temp_term.get_coefficient();

		iter_old++;
        
        if(iter_old != poly_terms.end())
        {
            temp_term2=*iter_old;
           
		   while(temp_exponent== temp_term2.get_exponent())
		   {
			temp_coefficient=temp_coefficient+temp_term2.get_coefficient();
			iter_old++;

			 if(iter_old != poly_terms.end())
			 {
			 	temp_term2=*iter_old;
			 }
			 else
			 	break;
		    }
		}
        //no more terms with equel exponent time create new term object and to push back
		Term new_term(temp_coefficient, temp_exponent);
		result.poly_terms.push_back(new_term);
		
	}

	return result;

}

void Polynomial:: remove_zero_terms()
{
	//check for possible zero terms and erase them
	if (poly_terms.size()>1)
	{
		list<Term>::reverse_iterator iter_LHS;
		list<Term>::iterator iter_eraser;
		
        //using erase member function of list class is only possible with reverse iteration
		for( iter_LHS =poly_terms.rbegin() ; iter_LHS != poly_terms.rend() ; iter_LHS++)
		{
			Term temp=*iter_LHS;

			if (temp.get_coefficient()==0)
				{
					iter_LHS++;
					//base changes iterator type (from reverse iterator to regular iterator)
					iter_eraser=iter_LHS.base();
					poly_terms.erase(iter_eraser);	
				}	
		}

	}
	//In case all terms in the list were 0,0 and the list is empty,
	if (poly_terms.size()==0)
		poly_terms.push_back(Term(0,0));


}

bool Polynomial:: my_compare(Term& term1, Term& term2)
{
   if(term1.get_exponent() > term2.get_exponent())
   	return true;
   else
   	return false; 
}


void Polynomial:: prepare_to_store()
{
	poly_terms.sort(my_compare);
	*this=term_addition();
	remove_zero_terms();
}




void Polynomial:: operator =(const Polynomial& RHS_polynomial)
{
	list<Term>::const_iterator iter_RHS;
	poly_terms.clear();
	
	for( iter_RHS = RHS_polynomial.poly_terms.begin() ; iter_RHS !=  RHS_polynomial.poly_terms.end() ; iter_RHS++)
	{
		poly_terms.push_back(*iter_RHS); 
		
	}
}
  

  



