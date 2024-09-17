import random

sizes = [10, 100, 1000, 10000, 100000, 1000000, 10000000]

for size in sizes:
    with open(f'input_{size}.txt', 'w') as f:
        for _ in range(size):
            f.write(f"{random.randint(1, 1000000)}\n")
