#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <x86intrin.h>

int main() {
  const int N = 8;
  float x[N], y[N], m[N], fx[N], fy[N];
  for(int i=0; i<N; i++) {
    x[i] = drand48();
    y[i] = drand48();
    m[i] = drand48();
    fx[i] = fy[i] = 0;
  }
  for(int i=0; i<N; i++) {
    float jidx[N];
    for(int j=0; j<N; j++)
      jidx[j] = j;

    __m512 jvec = _mm512_load_ps(jidx);
    __m512 ivec = _mm512_set1_ps(i);
    __mmask16 mask = _mm512_cmp_ps_mask(jvec, ivec, _MM_CMPINT_EQ);
    
    __m512 xivec = _mm512_set1_ps(x[i]);
    __m512 xjvec = _mm512_load_ps(x);
    __m512 yivec = _mm512_set1_ps(y[i]);
    __m512 yjvec = _mm512_load_ps(y);
    __m512 rxvec = _mm512_sub_ps(xivec, xjvec);
    __m512 ryvec = _mm512_sub_ps(yivec, yjvec);
    __m512 rrvec = _mm512_rsqrt14_ps(_mm512_add_ps(_mm512_mul_ps(rxvec, rxvec), _mm512_mul_ps(ryvec, ryvec)));
    __m512 rr_3_vec = _mm512_mul_ps(_mm512_mul_ps(rrvec, rrvec), rrvec);
    __m512 mvec = _mm512_load_ps(m);
    __m512 rxmvec = _mm512_mul_ps(rxvec, mvec);
    __m512 rymvec = _mm512_mul_ps(ryvec, mvec);
    
    __m512 zerovec = _mm512_setzero_ps();
    fx[i] -= _mm512_reduce_add_ps(_mm512_mask_blend_ps(mask, rxmvec, zerovec));
    fy[i] -= _mm512_reduce_add_ps(_mm512_mask_blend_ps(mask, rymvec, zerovec));



  //  for(int j=0; j<N; j++) {
  //    if(i != j) {
  //      float rx = x[i] - x[j];
  //      float ry = y[i] - y[j];
  //      float r = std::sqrt(rx * rx + ry * ry);
  //      fx[i] -= rx * m[j] / (r * r * r);
  //      fy[i] -= ry * m[j] / (r * r * r);
  //    }
  //  }
    printf("%d %g %g\n",i,fx[i],fy[i]);
  }
}
