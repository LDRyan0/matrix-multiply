# matrix-multiply
A set of CPU-based matrix multiplication algorithms utilizing the [Google Benchmark](https://github.com/google/benchmark) framework. ~280x speedup using threading and cache locality over naive implementation. 

## Versions
1. Naive
2. Loop reordering for cache efficiency
3. Thread-level parallelism using OpenMP
4. Cache tiling
5. Threading + tiling

## Usage
A `Makefile` is provided in each subdirectory. Alternatively a shell script is provided that compiles and runs all versions.
```
git clone https://github.com/LDRyan0/matrix-multiply.git
cd matrix-multiply/ 
./run_all.sh
```

## Dependencies
- [Google Benchmark](https://github.com/google/benchmark)
- OpenMP
