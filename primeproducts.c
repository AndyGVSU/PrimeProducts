#include <gmp.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define PRIME_FILE "primes.txt"
#define PRODUCT_FILE "products.txt"

int main(){

  char nextPrime[5000];
  char startPrime[2] = {'1','\0'};
  mpz_t current;
  mpz_t next;
  mpz_t iter;
  mpz_init(current);
  mpz_init(next);
  mpz_init(iter);

  int flag;
  unsigned long long int toFactor;
  
  FILE* primeFile = fopen(PRIME_FILE,"r");
  FILE* productFile = fopen(PRODUCT_FILE,"a");
  fseek(productFile, 0, SEEK_END);

  //seek to the end of the file to get the most recent prime
  if (primeFile == NULL)
  	{
	primeFile = fopen(PRIME_FILE,"w");
	mpz_set_ui(current, 1);
	}
  else
	{
	while (fscanf(primeFile, "%s\n", &nextPrime) != EOF)
		{
		//do nothing
		}
	flag = mpz_set_str(current, nextPrime, 10);
	gmp_printf("%Zd\n",current);
	}

  printf("Most recent prime productized: %s \nNumber of primes to productize:",nextPrime);
  scanf("%u", &toFactor);

  fclose(primeFile);
  primeFile = fopen(PRIME_FILE, "a");
  fseek(primeFile, 0, SEEK_END);

  for(unsigned long long int i = 0; i < toFactor; i++)
  	{
	//set next prime	
	mpz_nextprime(next, current);
	mpz_set(current, next);
	
  	primeFile = fopen(PRIME_FILE, "a");
  	fseek(primeFile, 0, SEEK_END);
	gmp_fprintf(primeFile, "%Zd\n", next);
	fclose(primeFile);

	//cycle through all previously calculated primes, multiplying each by the current prime
	//write the result to file
	primeFile = fopen(PRIME_FILE, "r");
	while (fscanf(primeFile, "%s\n", &nextPrime) != EOF)
		{
		mpz_set_str(iter, nextPrime, 10);
		mpz_mul(next, current, iter);
	
		gmp_fprintf(productFile, "%Zd | %Zd\n", next, iter);
		}	
	}

  mpz_clear(current);
  mpz_clear(next);
  mpz_clear(iter);

  fclose(primeFile);
  fclose(productFile);
}
