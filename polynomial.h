/*******************************************************************************
  Title          : polynomial.h
  Author         : Patrycja Krawczuk
  Created on     : February 5th, 2017
  Description    : Interface to the Polynomial class
  Purpose        : To provide methods for processing polynomials
  Usage          : 
  Build with     : makefile
  Modifications  : 

 
*******************************************************************************/
#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include <iostream>
#include <string>
#include <list>

//predefiniton of a helper class
class Term;

using namespace std;


class Polynomial
{

public:

/**Polynomial() - default constructor*/
Polynomial();

/**Polynomial(int coef, int expo) - 
*   @param  int   [in]  coef  - coefficient of one of the polynomial's terms 
*           int   [in]  expo  - exponent of one of the polynomial's terms
* Object of class Polynomial is created with provided parameters
*/
Polynomial(int coef, int expo);

/**Polynomial(const Polynomial& object)- copy constructor for the class 
*   @param  Polynomial const  [inout]  object  - object of the the class to be copied 
* New object of class Polynomial is created, a copy of provided argument
*/
Polynomial(const Polynomial& object);

/**Polynomial(vector <string>& v)
*   @param  vector<string> [inout]  v  - vector containing data to create a Polynomial 
* New object of class Polynomial is created based on data in vector v
*/
Polynomial(vector <string>& v);

/**Polynomial() - default deconstructor for the class*/
~Polynomial();

/**eval(double x);  
* Evaluates the polynomial using the provided argument x and returns the value as a double.
*   @param  double   [in]  x  - value for the calculation
* @pre    none
* @post   x is substituted for value in the polynomial and evaluated
* @returns result of calculation
*/
double eval(double x);


/**operator *(Polynomial& RHS_polynomial) - overload operator * for Polynomial objects 
* Distributes each term of a calling object to every term of object passed by reference.
* Multiplies coefficients and adds the exponents. Stores the result in a new object Polynomial.
* Calls helper funtions that add like terms and delete terms with zero coefficients.
*   @param  double   [in]  x  - value for the calculation
* @pre    none
* @post   Two polynomials are multiplied, new object storing the result is created
* @returns object of class Polynomial with results of the operation
*/
Polynomial operator *(Polynomial& RHS_polynomial);

/**operator =(Polynomial& RHS_polynomial) - overload assigment operator 
* Modifies the calling object by assigning to it a copy of an object passed be reference
*   @param  Polynomial [inout]  RHS_polynomial  - object to copy
* @pre    none
* @post   Calling object is assigned the copy of RHS_polynomial
* @returns void
*/
void operator =(const Polynomial& RHS_polynomial);

/** operator <<(ostream& write_stream, Polynomial& polynomial_to_print) -friend function
* Prints the Polynomial object to the screen in descending order of exponent powers
* Format:  Poly[3]= 4x^6 + -5x^4 + x^3 + -1
*   @param  ostream    [inout]  write_stream
            Polynomial [input]  polynomial_to_print
* @pre    working open stream is provided
* @post   Polynomial object is printed to the screen
* @returns osream&
 */
friend ostream& operator <<(ostream& write_stream, Polynomial& polynomial_to_print);


private:

//private data memeber, stores terms that Polynomial consist of 
list<Term> poly_terms;

/** remove_zero_terms()
* Removes terms with zero coefficient from Polynomial
* @pre    
* @post   Polynomial does not contain tems with zero coefficient
* @returns void
 */
void remove_zero_terms();

/** operator() (double y)= overload () operator
* Helper function for eval(), it substitutes y for x and evaluate each term of Polynomial
*   @param  double    [in]  y -value to substitute for x   
* @pre    
* @post   single term is evaluated with y as argument
* @returns calculated value
 */
double operator() (double y);

/** term_addition()
* Adds like terms in a calling object, polynomial terms with the same exponent 2x^5 + 4x^5 = 6x^5
* @pre    working open stream is provided
* @post   Polynomial object is printed to the screen
* @returns Polynomial object that stores the result of the operation
 */
Polynomial term_addition();

/** prepare_to_store() - helper function
* Calls sort, remove_zero_terms and term_addition function to prepare each Polynomial object for storing
* @pre    
* @post   Calling object is in sorted (desending order of exponent), it is reduced (like terms added),
*         does not contain any zero terms (terms with coefficient equel zero)
* @returns void
 */
void prepare_to_store();

/**my_compare(Term& term1, Term& term2)- helper function for list class function sort()
* Specifies a rule for sorting terms in list of Terms (descending order of exponents)
*  true if term1 has higher exponent than term2, else false
*   @param  Term   [inout]  term1  object storing coefficent and exponent 
            Term   [input]  term2  object stroing coefficent and exponent
* @pre    valid Terms
* @post   
* @returns true if term1 has higher exponent than term2
 */
static bool my_compare(Term& term1, Term& term2);
  
};



#endif /* __POLYNOMIAL_H__ */