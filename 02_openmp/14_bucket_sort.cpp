#include <cstdio>
#include <cstdlib>
#include <vector>

int main() {
  int n = 50;
  int range = 5;
  std::vector<int> key(n);
  for (int i=0; i<n; i++) {
    key[i] = rand() % range;
    printf("%d ",key[i]);
  }
  printf("\n");

  std::vector<int> bucket(range,0); 
  for (int i=0; i<n; i++)
    bucket[key[i]]++;
  std::vector<int> offset(range,0);
  for (int i=1; i<range; i++) 
    offset[i] = offset[i-1] + bucket[i-1];

  std::vector<int> j(range);
  std::vector<int> b(range);
  std::vector<int> key_new(n, -1);
#pragma omp parallel for
  for (int i=0; i<range; i++) {
    j[i] = offset[i];
    b[i] = bucket[i];
    bucket[i] = 0;
    for (int k=0; k<b[i]; k++) {
      if (key_new[j[i]+k] == -1 || key_new[j[i]+k] < i) 
        key[j[i]+k] = i;
    }
  }

  for (int i=0; i<n; i++) {
    printf("%d ",key[i]);
  }
  printf("\n");
}
