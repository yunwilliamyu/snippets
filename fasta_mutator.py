#!/usr/bin/env python
'''Mutates all the reads in a fasta file with specified point SNP and indel
rates'''

from __future__ import print_function

import sys
import argparse
import random

def main(argv):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-s", "--snp",
            help="fraction of locations to give SNP errors",
            type=float, default=0.01)
    parser.add_argument("-d", "--indel",
            help="fraction of locations to give indel errors",
            type=float, default=0.01)
    parser.add_argument('infile', nargs='?', type=argparse.FileType('r'),
            default=sys.stdin)
    parser.add_argument('outfile', nargs='?', type=argparse.FileType('w'),
            default=sys.stdout)

    args = parser.parse_args(argv)
    #print(args)
    fasta_mutate(args.infile, args.outfile, args.snp, args.indel)

def randbase():
    '''Generates a random A, C, G, T base'''
    return random.choice(["A","C","G","T"])
    
def mutate(line, s, d):
    '''Mutates a line with s SNP error and d indel error
    '''
    ans = list(line)
    for idx, _ in enumerate(ans):
        randvalue = random.random()
        if randvalue < s:
            ans[idx]= randbase()
        elif randvalue < (s + d):
            if random.random() < 0.5:
                ans.pop(idx)
                ans.append(randbase())
            else:
                ans.insert(idx, randbase())
                ans.pop()
    return "".join(ans)

def insert_linebreaks(par, n=80):
    '''Inserts linebreaks so that every line has no more than 80 non-newline
    characters, and inserts a linebreak at the very end'''
    parlist = list(par)
    if len(parlist) > 0:
        breakloc = range(0,len(parlist),n)
        breakloc = reversed(breakloc[1:])
        for i in breakloc:
            parlist.insert(i, '\n')
        if par[-1] != '\n':
            parlist.append('\n')
    return "".join(parlist)


def fasta_mutate(infile, outfile, s, d):
    '''Assumes (without error checking) that the infile is in Fasta format,
    such that for every line not beginning with ">" is part of the sequence,
    to be mutated'''
    sequence=""
    for line in infile:
        if line[0]==">":
            outfile.write(insert_linebreaks(mutate(sequence, s, d)))
            outfile.write(line)
            sequence = ""
        else:
            sequence = sequence + line.rstrip('\n')
    outfile.write(insert_linebreaks(mutate(sequence, s, d)))

if __name__ == "__main__":
    main(sys.argv[1:])

