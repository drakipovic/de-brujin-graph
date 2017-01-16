#!/usr/bin/env python

import os

from graph_parser import Graph

class bcolors:
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    HEADER = '\033[95m'

root_path = os.path.abspath(os.path.dirname(__file__))

bin_path = os.path.join(root_path, 'bin')
tests_path = os.path.join(root_path, 'tests')

synthetic_tests_input_path = os.path.join(tests_path, 'synthetic', 'input')
synthetic_tests_output_path = os.path.join(tests_path, 'synthetic', 'output')

e_coli_tests_input_path = os.path.join(tests_path, 'e_coli', 'input')
e_coli_tests_output_path = os.path.join(tests_path, 'e_coli', 'output')

explicit_tests_input_path = os.path.join(tests_path, 'explicit', 'input')
explicit_tests_output_path = os.path.join(tests_path, 'explicit', 'output')

input_files = os.listdir(synthetic_tests_input_path)


#bitvector tests

print bcolors.HEADER + 'BIT VECTOR TESTS' + bcolors.ENDC

print bcolors.OKBLUE + 'Running synthetic tests...' + bcolors.ENDC

for input_file in input_files:
    if input_file.startswith('input'):
        input_file_index = input_file.split('.')[0].split('_')[1]
        print 'Starting test on file {}...........'.format(input_file),

        output_file = 'output_{}.out'.format(input_file_index)
        command = bin_path + '/main ' + os.path.join(synthetic_tests_input_path, input_file) + ' ' + \
                    os.path.join(synthetic_tests_output_path, output_file) + ' --bitvector -k=3'

        os.system(command)

        with open(os.path.join(tests_path, 'bit_vector_ground_truth_output/', 'output_{}.out'.format(input_file_index))) as f:
            correct_output = f.read()
        
        with open(os.path.join(synthetic_tests_output_path, 'output_{}.out'.format(input_file_index))) as f:
            output = f.read()

        if output == correct_output:
            print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
        else:
            print bcolors.FAIL + 'FAILED' + bcolors.ENDC

print bcolors.OKBLUE + 'Running e. coli test...' + bcolors.ENDC

print 'Starting test on file input_10.fa...........',

input_file = 'input_10.fa'
output_file = 'output_10.out'
command = bin_path + '/main ' + os.path.join(e_coli_tests_input_path, input_file) + ' ' + \
                    os.path.join(e_coli_tests_output_path, output_file) + ' --bitvector -k=3'

os.system(command)
with open(os.path.join(tests_path, 'bit_vector_ground_truth_output/', 'output_10.out')) as f:
    correct_output = f.read()

with open(os.path.join(e_coli_tests_output_path, 'output_10.out')) as f:
    output = f.read()
        
if output == correct_output:
    print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
else:
    print bcolors.FAIL + 'FAILED' + bcolors.ENDC

# #implicit graph tests

print bcolors.HEADER + 'IMPLICIT GRAPH TESTS' + bcolors.ENDC

print bcolors.OKBLUE + 'Running synthetic tests...' + bcolors.ENDC

for input_file in input_files:
    if input_file.startswith('input'):
        input_file_index = input_file.split('.')[0].split('_')[1]
        print 'Starting test on file {}...........'.format(input_file),

        output_file = 'output_{}.out'.format(input_file_index)
        command = bin_path + '/main ' + os.path.join(synthetic_tests_input_path, input_file) + ' ' + \
                    os.path.join(synthetic_tests_output_path, output_file) + ' --implicit -k=3'

        os.system(command)

        with open(os.path.join(tests_path, 'implicit_ground_truth_output/', 'output_{}.out'.format(input_file_index))) as f:
            correct_output = f.read()
        
        with open(os.path.join(synthetic_tests_output_path, 'output_{}.out'.format(input_file_index))) as f:
            output = f.read()

        if output == correct_output:
            print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
        else:
            print bcolors.FAIL + 'FAILED' + bcolors.ENDC

print bcolors.OKBLUE + 'Running e. coli test...' + bcolors.ENDC

print 'Starting test on file input_10.fa...........',

input_file = 'input_10.fa'
output_file = 'output_10.out'
command = bin_path + '/main ' + os.path.join(e_coli_tests_input_path, input_file) + ' ' + \
                    os.path.join(e_coli_tests_output_path, output_file) + ' --implicit -k=3'

os.system(command)
with open(os.path.join(tests_path, 'implicit_ground_truth_output/', 'output_10.out')) as f:
    correct_output = f.read()

with open(os.path.join(e_coli_tests_output_path, 'output_10.out')) as f:
    output = f.read()
        
if output == correct_output:
    print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
else:
    print bcolors.FAIL + 'FAILED' + bcolors.ENDC




# #explicit graph tests

print bcolors.HEADER + 'EXPLICIT GRAPH TESTS' + bcolors.ENDC

print bcolors.OKBLUE + 'Running synthetic tests...' + bcolors.ENDC

for input_file in input_files:
    if input_file.startswith('input'):
        input_file_index = input_file.split('.')[0].split('_')[1]
        print 'Starting test on file {}...........'.format(input_file),
        
        output_file = 'output_{}.out'.format(input_file_index)        
        command = bin_path + '/main ' + os.path.join(explicit_tests_input_path, input_file) + ' ' + \
                    os.path.join(explicit_tests_output_path, output_file) + ' --explicit -k=3'

        os.system(command)

        g1 = Graph()
        g1.parse(filename=os.path.join(explicit_tests_output_path, output_file))
        output = g1.traverse()
        
        g2 = Graph()
        g2.parse(filename=os.path.join(tests_path, 'explicit_ground_truth_output/', 'output_{}.out'.format(input_file_index)))
        correct_output = g2.traverse()

        
        if output == correct_output:
            print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
        else:
            print bcolors.FAIL + 'FAILED' + bcolors.ENDC
