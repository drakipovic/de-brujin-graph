# de-bruijn-graph
Implementation of implicit compressed de Bruijn graph. 

Project for bioinformatics course on Faculty of Electrical Engineering and Computing, Zagreb.

## Authors
  [Tena Perak] (https://github.com/tenap)  
  [Katarina Matić] (https://github.com/qwertziuo40)   
  [Dino Rakipović] (https://github.com/drakipovic)  


## Prerequisites

    git clone git@github.com:simongog/sdsl-lite.git sdsl-lite
	cd sdsl-lite
	./install.sh [PATH]
    export SDSLLITE=[PATH]

## Clone the repo

    git clone https://github.com/drakipovic/de-brujin-graph
    cd de-brujin-graph
    
## Compiling

    make

This compiles the code and creates `bin/main` executable.

## Running

    bin/main input_file output_file --option -k={int}
    
`input_file` is absoulte path to input file in fasta format
`output_file` is absolute path to output file.

options are
    
    --implicit
    --explicit
    --bitvector
    
`implicit` prints only implicit graph  
`explicit` prints only explicit graph  
`bitvector` prints only bit vectors  
`{int}` is size of k-mer.

## Testing

    chmod +x run_tests.py
    ./run_tests.py
    
## License

MIT License  
Copyright (c) Katarina Matic, Tena Perak, Dino Rakipovic
