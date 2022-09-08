#include <iostream>
#include <type_traits>
#include <cmath>
#include <numbers>

using namespace std;

// example for unreadable code from Pete Goodliffe, Code Craft, page 59
//
unsigned int fval(int i)
{
   unsigned int ret = 2;

   for(int n1 = 1, n2 = 1, i2 = i - 3; i2 >= 0; --i2)
   {
      n1 = n2; n2= ret; ret = n2+n1;
   }
   return (i < 2) ? 1 : ret;
}

unsigned int fib_recursive1(unsigned int const n)
{
   if (n <= 1)
      return n;
  
   return fib_recursive1(n - 1) + fib_recursive1(n - 2);   
}


unsigned int fib_recursive2(unsigned int const n)
{
   return (n <= 1) ? n : (fib_recursive2(n - 1) + fib_recursive2(n - 2));   
}


unsigned int fib_iterative1(unsigned int n)
{
   unsigned int a = 0;
   unsigned int b = 1;

   while(n > 0)
   {
      auto t = a + b;
      a      = b;
      b      = t;
      --n;
   }
   return a;
}

unsigned int fib_iterative2(unsigned int n)
{
   unsigned int a = 0;
   unsigned int b = 1;

   for(; n > 0; --n)
   {
      b += a;
      a  = b - a;
   }
   return a;
}

unsigned int fib_iterative4(unsigned int n)
{
   if (n <= 2)
      return 1;

   unsigned int prev_prev = 1;
   unsigned int prev      = 1;
   unsigned int result    = 2;

   for(unsigned i = 3; i < n; ++i)
   {
      prev_prev = prev;
      prev      = result;
      result    = prev + prev_prev;
   }
   return result;
}

unsigned int fib_iterative5(unsigned int n)
{
   if (n <= 2)
      return 1;

   unsigned int a_2 = 1;
   unsigned int a_1 = 1;
   unsigned int a   = 2;

   for(n -= 3; n > 0; --n)   
   {
      a_2 = a_1;
      a_1 = a;
      a   = a_2 + a_1;
   }
   return a;
}

unsigned int fib_iterative6(int n)
{
   unsigned int a_2 = 1;
   unsigned int a_1 = 1;
   unsigned int a   = 2;

   for(n -= 2; n > 0; --n)   
   {
      a_2 = a_1;
      a_1 = a;
      a   = a_2 + a_1;
   }
   return a_1;
}


unsigned int fib_iterative_asm(unsigned int n)
{
   unsigned int a = 0;
   unsigned int b = 1;

   while(n-- > 0)
   {
      /* TEMP <- SRC + DEST;
         SRC  <- DEST;
         DEST <- TEMP;
      */
      //      asm("xadd %1, %0" : "+b" (b), "+a" (a)); 
      asm("xadd %1, %0" : "+r" (b), "+r" (a)); 
   }
   return a;
}


long fib_direct(int n)
{
   // long double sqrtl();
   //c++20 numbers::phi
   double const phi = (1.0 + sqrt(5.0)) / 2.0;

   return lround(pow(phi, n) / sqrt(5.0));
}


/* Note:
   https://godbolt.org/
   for(; n > 0; --) { }
   while(n-- > 0) { }
   while(n > 0) { --n }

   all generates identical assembler code
*/

int main([[maybe_unused]] int const argc, char const* const* const argv)
{
   unsigned int n = make_unsigned_t<int>(atoi(argv[1]));

   cout << "n = " << n << endl;
   cout << "recursive 1 = " << fib_recursive1(n) << endl;
   cout << "recursive 2 = " << fib_recursive2(n) << endl;
   cout << "iterative 1 = " << fib_iterative1(n) << endl;
   cout << "iterative 2 = " << fib_iterative2(n) << endl;
   cout << "iterative 3 = " << fib_iterative_asm(n) << endl;
   cout << "iterative 4 = " << fib_iterative4(n) << endl;
   cout << "iterative 5 = " << fib_iterative5(n) << endl;
   cout << "iterative 6 = " << fib_iterative6(n) << endl;
   cout << "direct      = " << fib_direct(n) << endl;
   cout << "bad code    = " << fval(n) << endl;
}
