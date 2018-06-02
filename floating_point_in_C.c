#include <stdio.h>

int main()
{
  double x ;

  // alphabet = ascii
  // legit symbols in OUR double =
  // {'0','1','2','3','4','5','6','7','8','9','e','E','+','-','.'} 

  /*
   pass : 
    x = 0.5 ;
    x = .5 ;
    x = .5e+4 ;
    x = .5e4 ;
    x = .5E4 ;
    x = .5E-4 ;
    x = +.5E-4 ;
    x = -.5E-4 ;
    x = -2.E-4 ;
    x = 23. ; 
    x = 23.e2 ;  
  */
  //////////////////////////////////

  // fail :
  //  x = -.E-4 ; // flaw
  //  x = -2.f-4 ; // this gives -6, for our purposes, f not legit modifier
  //  x =-2-4 ; // gvies -6
  //  x = 2.3-e4 ;  // no
  //  x = ++3 ; // no
  //  x = +-3 ; // it tolerated this but we won't
  //  x = 23.e+ ; // no
  //  x = 3.e+-2 ; // no

  printf("x = %lf\n",x) ;
}

  //  x = + -3 ; // it tolerated this as some arithemtic construct
                 // but we won't tolerate it as a floating point constant
