#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <random>

#include <benchmark/benchmark.h>
#include <omp.h>

// prints square flat matrix of arbitrary type
template<typename T, size_t SIZE>
void print2DMatrix(T (&array)[SIZE]) { 
  int N = int(sqrt(SIZE));
  for(int i = 0; i < N; ++i) { 
    for(int j = 0; j < N; ++j) { 
      std::cout << std::left << std::setw(3) << array[i*N + j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void BM_matMul(benchmark::State &state) { 
  size_t N = state.range(0);

  // create random number generator
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_real_distribution<float> dist(-10,10);

  float *A = new float[N*N];
  float *B = new float[N*N];
  float *C = new float[N*N];

  // Initialize them with random values (and C to 0)
  std::generate(A, A + N * N, [&] { return dist(rng); });
  std::generate(B, B + N * N, [&] { return dist(rng); });
  std::generate(C, C + N * N, [&] { return 0.0f; });

  for(auto _ : state) {
    #pragma omp parallel for
    for(int row = 0; row < N; ++row)
      for(int block = 0; block < N; block += 16)
        for(int chunk = 0; chunk < N; chunk += 16)
          for(int subChunk = 0; subChunk < 16; subChunk += 16)
            for(int idx = 0; idx < 16; ++idx) 
              C[row*N+block+idx] += A[row*N+chunk+subChunk] * B[(chunk+subChunk)*N+block+idx];
  }
  delete[] A;
  delete[] B;
  delete[] C;
  
}

BENCHMARK(BM_matMul)->RangeMultiplier(2)->Range(1<<7,1<<10)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
