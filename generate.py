import os
import random


tests_folder = os.path.join(os.path.abspath(os.path.dirname(__file__)), 'tests')

alphabet = ['A', 'C', 'G', 'T']

num_tests_small = 5
num_tests_mid = 3
num_tests_big = 2

num_tests = num_tests_small + num_tests_mid + num_tests_big

test_sizes_small = [random.randint(100, 2000) for _ in range(num_tests_small)]
test_sizes_mid = [random.randint(5000, 50000) for _ in range(num_tests_mid)]
test_sizes_big = [random.randint(300000, 1000000) for _ in range(num_tests_big)]

test_sizes = []
test_sizes.extend(test_sizes_small)
test_sizes.extend(test_sizes_mid)
test_sizes.extend(test_sizes_big)


line_size = 70
sequence_size = 700

for test in range(num_tests):
    f = open(tests_folder + '/input_{}.fa'.format(test), "a+")

    cnt = 1
    f.write('>{}\n'.format(cnt))
    
    for i in range(test_sizes[test]):
        if i % line_size == 0 and i != 0:
            f.write('\n')

        if i % sequence_size == 0 and i != 0:
            cnt += 1
            f.write('>{}\n'.format(cnt))
        
        letter = random.randint(0, 3)
        f.write(alphabet[letter])
