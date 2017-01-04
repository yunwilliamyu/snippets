#!/usr/bin/env python
'''Converts a VCF file with many genotypes to a feature vector. 

Copyright (c) 2017 Yun William Yu <contact@yunwilliamyu.net>
Released under CC0 1.0 Universal
'''
from __future__ import print_function

__version__ = "0.1.0"

import argparse
import sys
import numpy as np

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--version", action="version",
            version="%(prog)s {version}".format(version=__version__))
    parser.add_argument("vcffile", help="VCF file with genotypes", nargs='?', type=argparse.FileType('r'), default=sys.stdin)
    parser.add_argument("output", help="Optional output file", nargs='?', type=argparse.FileType('w'), default=sys.stdout)
    args = parser.parse_args()
    mat = read_vcf(args.vcffile, args.output)
    

def genotype_strings_to_numeric(gen):
    '''Converts a list of strings ["0|0", "1|0", "0/1", "1/1", "2/3"] to
    [0,1,1,1,1], specifying either wildtype or mutant'''
    ans = [0 if (a=="0|0" or a=="0/0") else 1 for a in gen]
    return ans


def read_vcf(fin, fout):
    '''Reads a VCF file with many genotypes
    
    fin: input IOStream
    fout: output IOStream
    '''
    cols = []
    while len(cols) == 0:
        l = fin.readline()
        if l[0:2] == "##":
            pass
        elif l[0] == "#":
            cols = l[1:].split()

    idind = cols.index("ID")
    begin = cols.index("FORMAT") + 1
    nodes = cols[begin:]
    col_to_node = dict(zip(range(len(nodes)), nodes))

    variant_list = []
    genotype_list = []
    sys.stderr.write("Reading VCF...")
    counter = 0
    for l in fin:
        lsplit = l.split()
        variant = lsplit[idind]
        genotype_string = lsplit[begin:]
        variant_list.append(variant)
        g = np.asarray((genotype_strings_to_numeric(genotype_string)),
                dtype=bool)
        genotype_list.append(g)
        counter = counter + 1
        if counter % 100000 == 0:
            print(counter)
    mat = np.vstack(genotype_list)
    np.savetxt(fout, mat.transpose(), fmt="%i", delimiter='\t')
    return mat


if __name__ == "__main__":
    main()
