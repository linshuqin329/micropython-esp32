#!/usr/bin/env python


import os
import sys
import re

filenames = ('sdkconfig.h', 'sdkconfig')

filename = None

class pair(object):
    def __init__(self, k, v):
        self.k = str(k)
        self.v = str(v)
        if self.v == 'y':
            self.v = '1'
        if self.v == 'n':
            self.v = '0'

    def __str__(self):
        return '%s: %s' % (self.k, self.v)

    def __hash__(self):
        return hash(self.k) 

    def __cmp__(self, other):
        if self.k > other.k:
            return 1
        elif self.k < other.k:
            return -1
        return 0

    __repr__ = __str__

if len(sys.argv) < 3:
    print 'usage:', sys.argv[0], '<dir> <dir>'
    sys.exit(1)

filesets = []

dirs = sys.argv[1:3]
paths = []
lineRe = re.compile(r'(CONFIG_\w+)(?:\s+|=)(\S+)')

for d in dirs:
    for filename in (os.path.join(d,i) for i in filenames):
        if os.path.exists(filename):
            paths.append(filename)
            filesets.append(set())
            fileset = filesets[-1]
            print 'found:', filename
            with open(filename) as f: lines = f.readlines()


            for line in lines:
                m = lineRe.search(line)
                if m:
                    fileset.add(pair(*m.groups((1,2))))

if len(filesets) != 2:
    sys.exit()

a_set, b_set = filesets
a_file, b_file = paths


a_only = a_set - b_set
b_only = b_set - a_set
common = a_set & b_set

print common

print 'common:'
a_map = { q.k:q.v for q in a_set if q in common }
b_map = { q.k:q.v for q in b_set if q in common }
keys = sorted(b_map.keys())

for i in keys:
    a_val = a_map[i]
    b_val = b_map[i]
    if a_val != b_val:
        print 'common: %s: "%s" "%s"' % (i, a_val, b_val)

if a_only:
    print '---'
    for i in sorted(list(a_only)):
        print a_file, 'only:', i

if b_only:
    print '---'
    for i in sorted(list(b_only)):
        print b_file, 'only:', i



