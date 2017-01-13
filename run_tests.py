#!/usr/bin/env python

import os
import subprocess

root_path = os.path.abspath(os.path.dirname(__file__))

bin_path = os.path.join(root_path, 'bin')
tests_path = os.path.join(root_path, 'tests')

input_files = os.listdir(tests_path)

correct = 0
total = len(input_files) - 1

for input_file in input_files:
    if input_file.startswith('input'):
        input_file_index = input_file.split('.')[0].split('_')[1]
        if(int(input_file_index) >= 8): continue

        output = subprocess.check_output([bin_path + '/main', input_file])
        with open(os.path.join(tests_path, 'explicit_ground_truth_output/', 'output_' + input_file_index + '.out')) as f:
            correct_output = f.read()
        
        correct += output == correct_output


print 'correct/total {}/{}'.format(correct, total)