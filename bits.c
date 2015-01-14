/* 
 * CS:APP Data Lab 
 * 
 * <Denis Kazakov, 102298967>
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
 /*
  QUESTIONS:
  how do we debug?
  "file test" - wrong architecture 
  * 
  overflow (7fffffff + 1 - overflow) (80000000 - 1 =>underflow)
  * 
  logical negative vs negative (~x+1) vs Ax?
  * 
  I can't call a function with specific values. 
 */
 
 /*
  Knowledge:
    //The logical negative value of x.
	int neg_x = ~x + 1;
	x-x = x+(~x+1);
	
	//if then else
	*
	//equivalence (x==y)
	!(x^y)
	* 
	1 or 0:
	a&0x1
	* 
	use overflow! 
	* 
	<<(-1) <=> >>1
	* 
	(!!n & 1)
	* 
	if (test1)
    output = a
if (!test1 & test2)
    output = b
if (!test1 & !test2 & test3)
    output = c
if (!test1 & !test2 & !test3)
    output = d
This leads to an expression like this for all the if else ifs.

output = (((test1 << 31) >> 31) & a)
         | ((((!test1 & test2) << 31) >> 31) & b)
         | ((((!test1 & !test2 & test3) << 31) >> 31) & c)
         | ((((!test1 & !test2 & !test3) << 31) >> 31) & d)
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
the coding rules are less strict.  !!!You are allowed to use looping and
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
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~(~x&y)&~(x&~y));
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.  
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
//[-32768;32767] <=> [11111111111111111000000000000000;0111111111111111(7FFF)]
// once it's all ones for y, y+1=0;
   int y=x>>(15); 
  return !(y+1) | !y;
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB(from the right)) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  int mask0 = 0x49;
  int mask2 = mask0|mask0<<9;
  int mask3 = mask2|mask2<<18;
  
  return mask3;
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000 //because F - covers 4 upper bits with ones
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {//***a way to avoid "-" sign: n + ~0 = n-1
   return ((!!n & 1) << 31) >> (n + ~0);
   //scoot one over to the most imortant bit, since it's arythmetic >>, it's going to be filled with ones if there is a leading one. 
   //***n&1 - for exception of 0. (determined first number)
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
	//the trick is in the idea that upper bits are all ones, or all zeroes. 
  int y=x>>(n+(~0));
  return (!(y+1)) | (!y); //if it's in the positive range, then !(y+1)=0, but !y = 1
  // if negative range, then !(y+1) = 1, !y=0. 
  // if not in the range, then 
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) { // It returns false, if and only if the first term is true, and the second term is false.
    return !x|(!!y); //"!!" to make expressions purely binary. 
    //We know that the outcome is going to be either 1 or 0, so why not jsut make those 1 or 0 in the first place?!
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Example: leastBitPos(96) = 0x20 (100000 mask for 1100000 decimal) //first one
 *   Rating: 2 
 */
int leastBitPos(int x) {
  return (~x+1)&x; //that means, the last one is going to become 0 (~x), +1 makes it 1. Then &x marks out the rest (because they are all different). 
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) { //48-57 //64 - next level. 
 
  int maskneg = 0x1<<31;
  return !!((x+(~57)) & maskneg) & !((x+(~47)) & maskneg);
	//1) (x-58) - should overflow  2) (x-48) - shouldn't overflow
}
/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x? (saturate to TMAX!!!!!!!)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {//will only overflow if positive becomes neg, or the opposite. 
  // + for multiplication
  // Tmax = ~Tmin (1..0..0, or 1...1.1) xor one with all ones or all zeroes and you will get the opposite
  // 1) overflow?
  // 2) neg or pos?
  // 3) saturate
    int  tmin = 0x1<<31;
    int  sign = x>>31;//either all ones or all zeroes
  	int x2x;	// x * 2
  	int toobig;	// too big?
  	int sat2;	
	
	x2x = x + x;
	toobig = (x^x2x) >> 31; //for sign change, that's why XOR. If it does change sign, we make it all ones. Otherwise, it's all zeroes and we destroy tmix/tmax mask
	// to tmax if x>=0 and tmin if x<0
	sat2 = toobig & (sign ^ ~tmin); 
	//				if it was neg, we make mask for tmax. if it was pos, we make mask for tmin. 
	
	// return sat2 if it x>max
	return (sat2) | (~toobig & x2x);
    return 2;
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {//???
	//shift right logically - main obstacle. 
	//let's try to erase those ones we copied if x was negative. (in x>>(32-n))
	//mask out two parts and then add them together. 
	//can we do unsinged int? - just mask it
	int unsignedmask = (0x1<<31)+(~0); //mask of all ones except leading bit (0111...)
	return x<<n | (x>>(32+(~n+1)) & unsignedmask>>(31+(~n+1)));
    //return (x << n) | ((unsigned int)x >> (32 - n)); - works, but we can't use unsigned int. 
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  int mask = 0x1; //only for signed bit. 
  int signx = (x>>31)&mask;
  int signy = (y>>31)&mask;
  int onezero = signy^signx; //only for cases when only one (either x or y) is positve. because +-+ = -; --- = + (no overflow, just arythmetic)
  int sum = (x+(~y+1))>>31;
  int sumsign = (sum&mask)^signx; // if subtraction is different sighn than x.
  return !(sumsign&onezero);      //combines onezero condition and sumsign condition
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's //if it's odd number of zeros it's odd number of ones. compare a section of number to itself. 
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
//xor with same size piece will converge even or uneven amoung of ones (but only with piece that you compare against (16 vs 16 etc)). 
  int y =x;
  y = y^(y>>16);
  y = y^(y>>8);
  y = y^(y>>4);
  y = y^(y>>2);
  y = y^(y>>1);
  return y&0x1;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
	//since it's a power of 2, we can expect x-1 to be all ones. So, we mask x with x-1
	//Note that no negative number is a power of 2.  =>  not neg mask. 
  
  return !(x&(x+~0)) & (!(0x1<<31 & x)) & (!((0x1)<<31 & (x+~0)));
  //1&0000  		 	, not negative,     exception of 0 (only 0 will overfow)
}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word. (msb is 1!)
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) { //check 16 - 8 - 4 - 2 
    //make count dependent on position. 
    int temp = x;
	int result;	
	int shift;
	int one = !(~x); 
	// Check the top 16 bits and add them to our result if they exist
	result = !(~(temp>>16)) << 4; //if there are no ones in the front, we just shift temp by a huge number, so temp is zero. 
	temp = temp << result;
	// check the remaining 8 bits (32-24)
	shift = !(~(temp >> 24)) << 3;
	temp = temp << shift;
	result = result | shift;
	// remaining 4 bits
	shift = !(~(temp>>28)) << 2;
	temp = temp << shift;
	result = result | shift;
	// remaining 2 bits
	shift = !(~(temp >> 30)) << 1;
	temp = temp << shift;
	result = result | shift;
	// remaining 1 bits
	result= result ^ (1&((temp>>31)));

	//rememer to add one if we have 32 on bits
	return result + one;
  
}
