#include <cstdio>

int main() {
  int n = 10;
  double dx = 1. / n;
  double pi = 0;
  double x[n];

#pragma omp parallel for
  for (int i=0; i<n; i++)
    x[i] = (i + 0.5) * dx;
#pragma omp parallel for reduction(+:pi)
  for (int i=0; i<n; i++)
    pi += 4.0 / (1.0 + x[i] * x[i]) * dx;
  printf("%17.15f\n",pi);
}
