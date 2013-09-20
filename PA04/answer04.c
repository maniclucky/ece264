/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */

void printPartition(int * part, int ind)
{
  int i;
  printf("= %d",part[0]);
  for(i=1;i<ind;i++)
    {
      printf(" + %d",part[i]);
    }
  printf("\n");
  return;
}

void partition(int * part,int ind, int left)
{
  int val;
  if(left==0)
    {
      printPartition(part,ind);
      return;
    }
  for(val=1;val<=left;val++)
    {
      part[ind]=val;
      partition(part,ind+1,left-val);
    }
}

void partitionAll(int value)
{
  printf("partitionAll %d\n", value);
  int * arr;
  arr=malloc(sizeof(int)*value);
  partition(arr,0,value);
  free(arr);
  return;
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

void partinc(int * part, int ind, int left, int nxt)
{
  int val;
  if(left==0)
    {
      printPartition(part, ind);
      return;
    }
  else if(left<0)
    {
      return;
    }
  for(val=nxt;val<=left;val++)
    {
      part[ind]=val;
      partinc(part,ind+1,left-val,val+1);
    }
  return;
}

void partitionIncreasing(int value)
{
  printf("partitionIncreasing %d\n", value);
  int * arr;
  arr=malloc(sizeof(int)*value);
  partinc(arr,0,value,1);
  free(arr);
  return;
}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */

void partdec(int * part, int ind, int left, int nxt)
{
  if(left==0)
    {
      printPartition(part,ind);
      return;
    }
  else if(left<0)
    {
      return;
    }
  int val;
  for(val=nxt;val>0;val--)
    {
      part[ind]=val;
      partdec(part,ind+1,left-val,val-1);
    }
  return;
}
void partitionDecreasing(int value)
{
  printf("partitionDecreasing %d\n", value);
  int * arr;
  arr=malloc(value*sizeof(int));
  partdec(arr,0,value,value);
  free(arr);
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partodd(int * part, int ind, int left)
{
  if(left==0)
    {
      printPartition(part,ind);
      return;
    }
  else if(left<0)
    {
      return;
    }
  int val;
  for(val=1;val<=left;val++)
    {
      if(val%2==1)
	{
	  part[ind]=val;
	  partodd(part,ind+1,left-val);
	}
    }
  return;
}
void partitionOdd(int value)
{
  printf("partitionOdd %d\n", value);
  int * arr;
  arr=malloc(sizeof(int)*value);
  partodd(arr,0,value);
  free(arr);
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void parteven(int * part, int ind, int left)
{
  if(left==0)
    {
      printPartition(part,ind);
      return;
    }
  else if(left<0)
    {
      return;
    }
  int val;
  for(val=2;val<=left;val++)
    {
      if(val%2==0)
	{
	  part[ind]=val;
	  parteven(part,ind+1,left-val);
	}
    }
  return;
}

void partitionEven(int value)
{
  printf("partitionEven %d\n", value);
  int * arr;
  arr=malloc(sizeof(int)*value);
  parteven(arr,0,value);
  free(arr);
}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partoe(int * part, int ind, int left, int oe)
{
  if(left==0)
    {
      printPartition(part,ind);
      return;
    }
  else if(left<0)
    {
      return;
    }
  int val;
  for(val=1;val<=left;val++)
    {
      if(oe==0 && val%2==0)
	{
	  part[ind]=val;
	  partoe(part,ind+1,left-val,1);
	}
      else if(oe==1 && val%2==1)
	{
	  part[ind]=val;
	  partoe(part,ind+1,left-val,0);
	}
    }
  return;
}

void partitionOddAndEven(int value)
{
  printf("partitionOddAndEven %d\n", value);
  int * arr;
  arr=malloc(sizeof(int)*value);
  partoe(arr,0,value,1);
  free(arr);
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

int isprime(int val)
{
  int i;
  int limit=(int)(sqrt(val))+1;
  for(i=2;i<limit;i++)
    {
      if(val%i==0)
	{
	  return(0);
	}
    }
  return(1);
}

void partprime(int * part, int ind, int left)
{
  if(left==0)
    {
      printPartition(part,ind);
      return;
    }
  else if(left<0)
    {
      return;
    }
  int val;
  for(val=2;val<=left;val++)
    {
      if(isprime(val)==1)
	{
	  part[ind]=val;
	  partprime(part,ind+1,left-val);
	}
    }
  return;
}

void partitionPrime(int value)
{
  printf("partitionPrime %d\n", value);
  int * arr;
  arr=malloc(sizeof(int)*value);
  partprime(arr,0,value);
  free(arr);
}
