/* --------------------
   TTNinterval.hpp
   (interval.hpp)
   --------------------
   Vasilis.N.Nikolaidis
   ---------------------------
   Interval Arithmnetic Header.
   1994 (c)
   ---------------------------- */

#define INTERVAL_HEADER_VERSION "0.0.2"

#include <stdio.h>
#include <math.h>

#define runerror(x,y) printf("%s ---> ",y)

#define REAL      float
#define LARGEREAL +10000
#define SMALLREAL -10000

// #define min(x,y) (x)<(y)?(x):(y)
// #define max(x,y) (x)>(y)?(x):(y)

class interval
 {
 private:
  REAL inf;
  REAL sup;

 public:

// Constructors

 interval()
  {
  inf=0;
  sup=0;
  }

 interval(REAL a)
  {
  inf=a;
  sup=a;
  }

 interval(REAL a1,REAL a2)
  {
  if(a1<=a2)
   {
   inf=a1;
   sup=a2;
   }
  else
   {
   inf=a2;
   sup=a1;
   }
  }

// destructors

// Basic operation protos

 interval operator = (interval);

 interval operator + (interval);
 interval operator - (interval);
 interval operator * (interval);
 interval operator / (interval);

// interval operator + (REAL);
// interval operator - (REAL);
// interval operator * (REAL);
// interval operator / (REAL);

//      int operator > (interval);
//      int operator < (interval);
//      int operator >= (interval);
//      int operator <= (interval);
//      int operator == (interval);

// Other protos

 void show(void);
 REAL value_of_inf(void);
 REAL value_of_sup(void);

};


//--------------------------------------------------------------------------------------
// Definitions of interval operations.
//--------------------------------------------------------------------------------------


interval interval::operator = (interval i)
 {
 return interval(this->inf=i.inf,this->sup=i.sup);
 }

//--------------------------------------------------------------------------------------

interval interval::operator + (interval i)
 {
 return interval(this->inf + i.inf, this->sup + i.sup);
 }

//--------------------------------------------------------------------------------------

interval interval::operator - (interval i)
 {
 return interval(this->inf - i.inf, this->sup - i.sup);
 }

//--------------------------------------------------------------------------------------

interval interval::operator * (interval i)
 {
 REAL a1,a2,b1,b2,n1,n2;
 REAL p[4];
 int n;

 a1=this->inf;
 a2=this->sup;
 b1=i.inf;
 b2=i.sup;

 p[0]=a1*b1;
 p[1]=a2*b2;
 p[2]=a1*b2;
 p[3]=a2*b1;

 n1=n2=p[0];
 for(n=1;n<4;n++) n1=min(p[n],n1);
 for(n=1;n<4;n++) n2=max(p[n],n2);

 return interval(n1,n2);
 }

//--------------------------------------------------------------------------------------


interval interval::operator / (interval i)
 {
 if((i.inf<=0)&&(i.sup>=0))
  {
  runerror(777,"Interval contains zero, can't divide.");
  return interval(LARGEREAL,LARGEREAL);
  }
 else
  return (interval(this->inf,this->sup)*interval(1/i.inf,1/i.sup));
 }

//--------------------------------------------------------------------------------------

//interval interval::operator + (REAL n)
// {
// return interval(this->inf+n,this->sup+n);
// }

//--------------------------------------------------------------------------------------

//interval interval::operator - (REAL n)
// {
// return interval(this->inf-n,this->sup-n);
// }

//--------------------------------------------------------------------------------------

//interval interval::operator * (REAL n)
// {
// return interval(this->inf*n,this->sup*n);
// }

//--------------------------------------------------------------------------------------

//interval interval::operator / (REAL n)
// {
// if(n==(REAL)0)
//  {
//  runerror(777,"Can not to divide interval by zero.");
//  return interval(LARGEREAL,LARGEREAL);
//  }
// return interval(this->inf/n,this->sup/n);
// }

//--------------------------------------------------------------------------------------

//interval interval::operator + (interval i,REAL n)
//{
//return interval (i.inf+n,i.sup+n);
//}

//--------------------------------------------------------------------------------------

void interval::show(void)
 {
 printf("[%f %f]\n",this->inf,this->sup);
 }

//--------------------------------------------------------------------------------------

REAL interval::value_of_inf(void)
 {
 return this->inf;
 }

//--------------------------------------------------------------------------------------

REAL interval::value_of_sup(void)
 {
 return this->sup;
 }

//--------------------------------------------------------------------------------------
// Other functions using interval class.
//--------------------------------------------------------------------------------------

interval exp(interval x)
{
return interval((REAL)exp(x.value_of_inf()),(REAL)exp(x.value_of_sup()));
}

//--------------------------------------------------------------------------------------

interval sqrt(interval x)
{
return interval((REAL)sqrt(x.value_of_inf()),(REAL)sqrt(x.value_of_sup()));
}

//--------------------------------------------------------------------------------------


