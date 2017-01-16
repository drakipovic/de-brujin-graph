#!/usr/bin/env python

import os
import subprocess

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

input_files = os.listdir(tests_path)


#bitvector tests

print bcolors.HEADER + 'BIT VECTOR TESTS' + bcolors.ENDC

print bcolors.OKBLUE + 'Running synthetic tests...' + bcolors.ENDC

for input_file in input_files:
    if input_file.startswith('input'):
        input_file_index = input_file.split('.')[0].split('_')[1]
        if input_file_index == '10': continue
        print 'Starting test on file {}...........'.format(input_file),

        output = subprocess.check_output([bin_path + '/main', input_file, '--bitvector'])
        with open(os.path.join(tests_path, 'bit_vector_ground_truth/', 'output_' + input_file_index + '.out')) as f:
            correct_output = f.read()
        
        if output == correct_output:
            print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
        else:
            print bcolors.FAIL + 'FAILED' + bcolors.ENDC


#implicit graph tests

print bcolors.HEADER + 'IMPLICIT GRAPH TESTS' + bcolors.ENDC

print bcolors.OKBLUE + 'Running synthetic tests...' + bcolors.ENDC

for input_file in input_files:
    if input_file.startswith('input'):
        input_file_index = input_file.split('.')[0].split('_')[1]
        if input_file_index == '10': continue
        print 'Starting test on file {}...........'.format(input_file),

        output = subprocess.check_output([bin_path + '/main', input_file, '--implicit'])
        with open(os.path.join(tests_path, 'implicit_ground_truth_output/', 'output_' + input_file_index + '.out')) as f:
            correct_output = f.read()
        
        if output == correct_output:
            print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
        else:
            print bcolors.FAIL + 'FAILED' + bcolors.ENDC

print bcolors.OKBLUE + 'Running e. coli test...' + bcolors.ENDC

print 'Starting test on file input_10.fa...........',
output = subprocess.check_output([bin_path + '/main', 'input_10.fa', '--implicit'])
with open(os.path.join(tests_path, 'implicit_ground_truth_output/', 'output_10' + '.out')) as f:
    correct_output = f.read()
        
if output == correct_output:
    print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
else:
    print bcolors.FAIL + 'FAILED' + bcolors.ENDC


#explicit graph tests

print bcolors.HEADER + 'EXPLICIT GRAPH TESTS' + bcolors.ENDC

print bcolors.OKBLUE + 'Running synthetic tests...' + bcolors.ENDC

for input_file in input_files:
    if input_file.startswith('input'):
        input_file_index = input_file.split('.')[0].split('_')[1]
        if input_file_index == '10': continue
        print 'Starting test on file {}...........'.format(input_file),

        output = subprocess.check_output([bin_path + '/main', input_file, '--explicit'])

        g1 = Graph()
        g1.parse(data=output.split('\n'))
        output = g1.traverse()
        
        g2 = Graph()
        g2.parse(filename=os.path.join(tests_path, 'explicit_ground_truth_output/', 'output_' + input_file_index + '.out'))
        correct_output = g2.traverse()

        
        if output == correct_output:
            print bcolors.OKGREEN + 'CORRECT' + bcolors.ENDC
        else:
            print bcolors.FAIL + 'FAILED' + bcolors.ENDC
