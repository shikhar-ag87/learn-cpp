import time

cache = {1:1}

def fib(n: int) -> int:
    if (n in cache.keys()): return cache[n]
    if (n < 1): return 0
    if (n==0 or n==1): return 1
    fib_res = fib(n-1) + fib(n-2)
    cache[n] = fib_res
    return fib_res

n = 1000
# for i in range(n):
#     print(fib(i+1))
start = time.time()
res = fib(n)
end = time.time()
print(res)
print(f"Total execution time: {(end-start)*1000}ms")