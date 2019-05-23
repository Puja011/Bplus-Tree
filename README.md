## Problem

Implement B+ tree to handle the following type of queries

1. INSERT x - insert x into the B+tree
2. FIND x - print YES if x is already inserted , else NO
3. COUNT x - print number of occurrences of x in B+tree
4. RANGE x y - print number of elements in range x to y ( both x and y included)

## Constraints

1. -10^9 <= x <= 10^9 and -10^9 <= y <= 10^9.
2. Number of queries will be less than 10^6.

## Input ​​ : 
​Filename,M,B
1. Inputs must be taken as command line arguments
2. Each line in the filename consists one of the above-mentioned query.

## Output ​:

1. Print output of each command in a separate line


## Note:

1. M denotes the number of buffers and B denotes the buffer size (M>=2 and M*B<=10^6)
2. Out of the M buffers, M-1 Buffers will be used as input buffers (which will hold the records
    from the input file), 1 buffer will be used as output buffer (holds the distinct records). If the
    output buffer gets filled, it should be flushed to the output. If the input buffers get empty, the
    next chunk of records should be read from the input file.
3. The size of B+ tree and hash table is ​ **NOT** ​ included in M.

## Compile:

./bplustree.o filename M B

M anynumber

B 21 for 4 nodes per block ((21-1)/4)-1

