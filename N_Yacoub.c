#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>

struct tablo {
  int * tab;
  int size;
};

void printArray(struct tablo * tmp) {
  printf("---- Array of size %i ---- \n", tmp->size);
  int size = tmp->size;
  int i;
  for (i = 0; i < size; ++i) {
    printf("%i ", tmp->tab[i]);
  }
  printf("\n");
}

struct tablo * allocateTablo(int size) {
  struct tablo * tmp = malloc(sizeof(struct tablo));
  tmp->size = size;
  tmp->tab = malloc(size*sizeof(int));
  return tmp;
}

void generateArray(struct tablo * s, int taille , char** a) {

  s->tab=malloc(taille*sizeof(int));
  #pragma omp parallel for
  for (int i = 0 ; i < taille-1; i++ ){
    s->tab[i]= atoi(a[i+1]);
    printf("%d ",s->tab[i]);
  }
  s->size=taille;

}

int main(int argc, char**  argv) {

  // Q

  struct tablo q;
  generateArray( &q, argc , argv );

// PSUM

  struct tablo  psum;
  (&psum)->size = argc;
  (&psum)->tab=malloc((&psum)->size*sizeof(int));
  #pragma omp parallel for
  for (int i = 0 ; i < 1; i++ ){
      (&psum)->tab[i] = (&q)->tab[i];
  }
  #pragma omp parallel for
  for (int i = 0 ; i < (&psum)->size-1; i++ ){
      (&psum)->tab[i+1] += (&psum)->tab[i];
  }





//SSUM

  struct tablo ssum;
  (&ssum)->size = argc;
  (&ssum)->tab=malloc((&ssum)->size*sizeof(int));
  #pragma omp parallel for
  for (int i = (&ssum)->size-1 ; i >= (&ssum)->size-  2 ; i-- ){
      (&ssum)->tab[i] = (&q)->tab[i];
  }
  #pragma omp parallel for
  for (int i = (&ssum)->size-1 ; i > 0; i-- ){
      (&ssum)->tab[i] += (&ssum)->tab[i+1];
  }


//SMAX

  struct tablo smax;
  (&smax)->size = argc;
  (&smax)->tab=malloc((&smax)->size*sizeof(int));
  #pragma omp parallel for
  for (int i = (&smax)->size-1 ; i >= (&smax)->size-  2 ; i-- ){
      (&smax)->tab[i] = (&psum)->tab[i];
  }
  #pragma omp parallel for
  for (int i = (&smax)->size-1 ; i > 0; i-- ){
      if ((&smax)->tab[i] <= (&psum)->tab[i]){
        (&smax)->tab[i] = (&psum)->tab[i];
    }
      else{
        (&smax)->tab[i] = (&smax)->tab[i+1];

    }


}


// PMAX

  struct tablo pmax;
  (&pmax)->size = argc;
  (&pmax)->tab=malloc((&pmax)->size*sizeof(int));
  #pragma omp parallel for
  for (int i = 0 ; i <= 1 ; i++ ){
      (&pmax)->tab[i] = (&ssum)->tab[i];
  }
  #pragma omp parallel for
  for (int i = 0 ; i > (&pmax)->size-1; i++ ){
      if ((&pmax)->tab[i] <= (&ssum)->tab[i]){
        (&pmax)->tab[i] = (&ssum)->tab[i];
      }
      else{
        (&pmax)->tab[i] = (&pmax)->tab[i-1];

      }


  }




// M

  struct tablo m;
  struct tablo ms;
  struct tablo mp;
  (&m)->size = argc;
  (&ms)->size = argc;
  (&mp)->size = argc;
  (&m)->tab=malloc((&m)->size*sizeof(int));
  (&ms)->tab=malloc((&ms)->size*sizeof(int));
  (&mp)->tab=malloc((&mp)->size*sizeof(int));
  #pragma omp parallel for
  for (int i = 0 ; i <= (&m)->size-1 ; i++ ){
    (&ms)->tab[i] = (&pmax)->tab[i] - (&ssum)->tab[i] + (&q)->tab[i];
    (&mp)->tab[i] = (&smax)->tab[i] - (&psum)->tab[i] + (&q)->tab[i];
    (&m)->tab[i] = (&ms)->tab[i] + (&mp)->tab[i] - (&q)->tab[i];
  }


//Subarray with the largest value in M

  struct tablo subarraym;
  (&subarraym)->size = argc;
  (&subarraym)->tab=malloc((&subarraym)->size*sizeof(int));
  #pragma omp parallel for
  for (int i = 0 ; i <= 1 ; i++ ){
    (&subarraym)->tab[i] = (&m)->tab[i];
}
  #pragma omp parallel for
  for (int i = 0 ; i <= (&m)->size-1 ; i++ ){
    if ((&subarraym)->tab[i] < (&m)->tab[i]){
      (&subarraym)->tab[i] = (&m)->tab[i];
  }
    else{
      (&subarraym)->tab[i] = (&subarraym)->tab[i-1];
  }
  }








  //(&smax)->tab[i+1] = (&smax)->tab[i];

//for (int i = 0 ; i < (&smax)->size - 1; i++ ){
//  printf("%d ",(&smax)->tab[i]);
//}






  //struct tablo * a = malloc(sizeof(struct tablo));
  //a = allocateTablo((source.size*2) );

  //montee(&source, a);
 // printArray(a);

  //struct tablo * b = malloc(sizeof(struct tablo));
  //b = allocateTablo((source.size*2) );

  //descente(a, b);
  //printArray(b);

  //final(a,b);
  //printArray(b);

}
