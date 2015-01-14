from random import randint
import time
bitRange = 10

#generate random number of n-bits
def randNum():
	global bitRange
	randMin = 2**(bitRange-1)
	randMax = 0
	for i in range(0,bitRange):
		randMax+=2**i
	#print "The range of keys to generate from is [%d, %d]" %(randMin, randMax)
	return randint(randMin, randMax)

#generates a random Number in a given range. returns it it's prime. 
def generatePrime():
	global bitRange
	prime = 0
	while (prime == 0):
		potentialPrime = randNum()
		
		#check if number is prime using little fermat's theorem
		for i in range(0,10):
			a = randint(2,potentialPrime)
			if((a**(potentialPrime-1))%potentialPrime == 1):
				prime = 1
			else: prime = 0
	return potentialPrime

def gcdEuclid(a,b):
	if (b==0): return a
	return gcdEuclid(b,a%b)

#find Relative Prime
def findRP(phi):
	while True: 
		e = randint(2,phi-1)
		if (gcdEuclid(e,phi)==1):
			return e
			
#find Multiplicative Inverse, reference:wikipedia
def findMI(phi, key):
    x, y = 0, 1
    a, b = phi, key
    while b:
        a, q, b = b, a // b, a % b
        x, y = y - q * x, x
    result = (1 - y * phi) // key
    if result < 0:
        result += phi
    assert 0 <= result < phi and key * result % phi == 1
    return result

#MAIN_BODY
#generate 2 prime numbers p,q of size n-bits
start_time = time.time()
while True:
	p = generatePrime()
	q = generatePrime()
	if (p!=q):
		break
N = p*q
phi = (p-1)*(q-1)
print "BitRange is [%d]" %bitRange
print "Prime Numbers: p = %d, q = %d" %(p, q)
print " N = %d \n phi = %d" %(N,phi)

# choose e: gcd(e,phi) = 1  (so that there exists multiplicative inverse)
e = findRP(phi)
print " e = %d" %e
#find d = mult. inverse of e
d = findMI(phi,e)
print " d = %d" %d
#RSA encrypt - decrypt
encoded = (13**e)%N
decoded = (encoded**d)%N
print "message is :%d \nencodedMessage is:%d \ndecodedMessage is:%d" %(13, encoded, decoded)
#TIME
current_time = time.time() - start_time
print "run took %s seconds" % current_time
