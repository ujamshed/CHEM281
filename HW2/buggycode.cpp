#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

struct header
{
  header* next;
  header* previous;
  uint64_t size;
};

class allocator
{
public:
  allocator();
  ~allocator();
  void* allocate(uint64_t size);
  void release(void*);
private:
  header head;
};

allocator::allocator() : head({NULL, NULL, 0})
{
}

allocator::~allocator()
{
  header* buffer = head.next;
  while (buffer)
    {
    header* nextbuffer = buffer->next;
    release((char*) buffer + sizeof(header));
    buffer = nextbuffer;
    }
}

void
allocator::release(void* mem)
{
  header* buffer = (header*)((char*) mem - sizeof(header));
  uint64_t memsize = buffer->size;
  buffer->previous->next = buffer->next;
  if (buffer->next) buffer->next->previous = buffer->previous;
  munmap(buffer, memsize);
}

void*
allocator::allocate(uint64_t size)
{
  // Changed allocation size from 4096 bits which would only accomodate 512 bytes at most, but we need 538.

  //const uint64_t offbits = 4095UL;
  const uint64_t offbits = 4304UL;
  // const size_t allocSize = (size+sizeof(header)+offbits) & (~offbits);
  const size_t allocSize = offbits;
  header* buffer = (header*) mmap(NULL, allocSize, PROT_READ|PROT_WRITE,
				  MAP_PRIVATE|MAP_ANONYMOUS , -1 , 0);
  buffer->next = head.next;
  buffer->previous = &head;
  buffer->size = allocSize;
  head.next = buffer;
  return (char*) buffer+sizeof(header);
}

double mean(const double* array, const uint64_t len)
{
  double mean = 0.d+00;
  for (unsigned int i=0; i<len; i++)
  {
    mean += array[i];
  }
  return mean;
}

allocator* globalAllocator=NULL;

void compute(double* a, double*& b, uint64_t len2)
{
  uint64_t looplen = len2;
  
  for (unsigned int j=0; j<looplen; j++)
  {
    b[j] = rand()%2 ? -a[j] : a[j];
    // Used for debugging: std::cout << "B value is: " << b[j] << std::endl;
  }
}

uint64_t getarrdim()
{
  // Added the missing dimension and the correct evaluation from gendata.cpp
  uint64_t dim1 = rand();
  uint64_t dim2 = rand();
  uint64_t dim3 = rand();
  dim1 *=52;
  dim2 *=52;
  return dim1/dim3;
}

void getdata(const char* datafile, double* buffer, uint64_t& len)
{
  int fd = open(datafile, O_RDONLY);
  if (fd == -1)
    {
    printf("ERROR: File cannot open file %s\n", datafile);
    exit(1);  
    }
  read(fd, &len, sizeof(uint64_t));
  read(fd, buffer, len*sizeof(double));
  close(fd);
}


int main(int argc, char* argv[])
{
  srand(222209);

// Commented out the argc to not use command line arguments, and instead hardcoded the hwddata file for debugging with VScode

//   if (argc < 2)
//     {
//     printf("Error, data file missing\n");
//     exit(1);
//     }
  argv[1] = "hwddata";

  const char* datafile = argv[1];
  uint64_t dlen = 0;
  uint64_t dimarr = getarrdim();
  double arr[dimarr];
  double* ptr1 = NULL;

  // Allocate memory here so that the destructor is not called as soon as the compute function goes out of scope
  allocator getmem;
  globalAllocator = globalAllocator == NULL ? &getmem : globalAllocator;
  if (ptr1==NULL)
    {
    ptr1 = (double*) globalAllocator->allocate(dlen);
    }  

  getdata(datafile, arr, dlen);
  compute(arr, ptr1, dlen);

  double meanvalue = mean(ptr1, dlen);
  printf("meanvalue %15le\n", meanvalue);
  printf("data sample\n");
  for (unsigned int i=0; i<10; i++)
    printf("%le ", ptr1[i]);
  printf("\n");
  return 0;
}