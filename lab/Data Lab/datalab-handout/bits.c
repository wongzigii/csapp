/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x) | (~y));
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // int bits = 8 * n
  // since we can't use `*`
  // that is: bits = n << 3
  int bits = n << 3;
  int after = x >> bits;
  return 0xFF & after;

}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  // bitmask(00001111..) & (x >> n)
  
  // shifts x over arithmatically
  x = x >> n;
  
  // bitmask 11110000..
  int tmp = 1;   // 1
  tmp = tmp << 31; // 100000..
  tmp = tmp >> n; // 111110..
  tmp = tmp << 1; //  111100..
  return (x & ~tmp);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  return 2;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {

  // just to guarantee that the MSB will be 0 if the number is non zero,
  // and be 1 if the original was 0
  //
  x = x | (~x + 1);  // (x | -x) : MSB will 0 if x is original zero, otherwise MSB will be 1
  x = x >> 31; // extend bit sign from (1...) or (0...), so result is either -1(1111) or 0(0000) => plus 1 => 0 or 1
  return x + 1;  //
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // 1000 0000 => -128
  return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  // the easiest way is plus x and -x
  return 2;
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  // if x is positive, then x >> n
  // otherwise (x + something) >> n
  // here something is 2^n - 1
  int sign = x >> 31;
  return (x + (sign & ((1 << n) - 1))) >> n;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  // result should be converted to bool
  int msb = !(x >> 31);  // most significant bit = 0 => x >= 0
  return msb & !!x;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // x = y, x - y = 0, x + ~y+1 = 0
  int a = !(x + (~y) + 1);
  
  // x's sign
  int sign_x = (x >> 31) & 0x1;
  // y's sign
  int sign_y = (y >> 31) & 0x1;
  
  int sign_ymx = ((y + (~x) + 1) >> 31) & 0x1;
  
  // x and y have difference sign and x < 0 (sign_x = 1)
  int b = (sign_x ^ sign_y) & sign_x;
  // x and y have same sign and y - x > 0 (sign_ymx = 0)
  int c = !(sign_x ^ sign_y) & !sign_ymx;
  return a | b | c;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  // find the highest bit 1 of the binary number
  //
  
  int tmp, bitmask, bits, total = 0;
  
  // check left 16 bitsmask, equals 0xFFFFFFFF if left 16 bits have at least one 1, otherwise will be 0x0
  tmp = x >> 16;
  bitmask = ((!!tmp) << 31) >> 31;
  bits = (bitmask & tmp) | (~bitmask & x);
  total += (bitmask & 16) | (~bitmask & 0);
  
  // get bits from previous
  tmp = bits >> 8;
  bitmask = ((!!tmp) << 31) >> 31;
  bits = (bitmask & tmp) | (~bitmask & bits);
  total += (bitmask & 8) | (~bitmask & 0);
  
  tmp = bits >> 4;
  bitmask = ((!!tmp) << 31) >> 31;
  bits = (bitmask & tmp) | (~bitmask & bits);
  total += (bitmask & 4) | (~bitmask & 0);
  
  tmp = bits >> 2;
  bitmask = ((!!tmp) << 31) >> 31;
  bits = (bitmask & tmp) | (~bitmask & bits);
  total += (bitmask & 2) | (~bitmask & 0);
  
  tmp = bits >> 1;
  bitmask = ((!!tmp) << 31) >> 31;
  bits = (bitmask & tmp) | (~bitmask & bits);
  total += (bitmask & 1) | (~bitmask & 0);
  
  return total;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 // https://en.wikipedia.org/wiki/Single-precision_floating-point_format
 // http://stackoverflow.com/a/12038943/4234171
 // NaN +- infi
 // 1000 0000 0000 0000
 unsigned sign_mask = 0x80000000;
 // 1 1111 1111 1000 000
 unsigned nan = 0x7FC00000;
 // 0 1111 1111 1000 000
 unsigned infi = 0xFFC00000;
 if (uf == nan || uf == infi) {
   return uf;
 }
 return sign_mask ^ uf;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  // integer to float
  // 1000 0000 0000 0000 int: -Int.max
  // (-1)^sign * 2^(e-127), so e = 158
  // that is 1 1001 1110 0000 000
//  if (x == 0) {
//    return 0;
//  } else if (x == 0x80000000) {
//    return 0xcf000000;
//  }
//  
//  int sign = (x >> 31) & 0x01;
//  if (sign) {
//    return -x;
//  }
//  int exponent = 127;
//  
//  return 2;
  int sign=x>>31&1;
  int i;
  int exponent;
  int fraction;
  int delta;
  int fraction_mask;
  if(x==0)//||x==0x8000000)
    return x;
  else if(x==0x80000000)
    exponent=158;
  else{
    if (sign)//turn negtive to positive
      x = -x;
    i = 30;
    while ( !(x >> i) )//see how many bits do x have(rightshift until 0)
      i--;
    //printf("%x %d\n",x,i);
    exponent = i + 127;
    x = x << (31 - i);//clean all those zeroes of high bits
    fraction_mask = 0x7fffff;//(1 << 23) - 1;
    fraction = fraction_mask & (x >> 8);//right shift 8 bits to become the fraction,sign and exp have 8 bits total
    x = x & 0xff;
    delta = x > 128 || ((x == 128) && (fraction & 1));//if lowest 8 bits of x is larger than a half,or is 1.5,round up 1
    fraction += delta;
    if(fraction >> 23) {//if after rounding fraction is larger than 23bits
      fraction &= fraction_mask;
      exponent += 1;
    }
  }
  return (sign<<31)|(exponent<<23)|fraction;
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
