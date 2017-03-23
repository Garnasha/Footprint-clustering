#Appendix: Results

The following is the output of the program compiled from the
current version of the source.

Note that the first part of the output is diagnostic information,
introduced in the debugging phase. It provides a window into the 
program state at various points during execution, but otherwise 
should be skipped over.

The interesting part of the output starts after "Press any key to
continue." Everything after this follows the same format: On every line,
one motif, in the same format:
```
<sequence> <#(data points in cluster)> <#(unique original sequences in cluster)>
```
Where the sequences as written here use IUPAC ambiguity codes.

```
262426
INFO: seq_count count: 142510
Please enter a highpass cutoff for sequence counts: 
INFO: high-passing seq_counts with cutoff 5
INFO: high-passed seq_count counts, remaining: 5003
INFO: defined distfunc.
INFO: built tree, testing...
INFO (build_index_adj_list): Called
INFO (max_index_from_edges): Called
INFO (max_index_from_edges): Complete, result 5002
INFO (build_index_adj_list): Complete, result size 5003
testcluster has 1 element(s)
first has size 5003
INFO: SORTED
INFO (build_index_adj_list): Called
INFO (max_index_from_edges): Called
INFO (max_index_from_edges): Complete, result 5002
INFO (build_index_adj_list): Complete, result size 5003
sortcluster has 1 element(s)
first has size 5003
Shrunk tree by 600, new size 4938
INFO (build_index_adj_list): Called
INFO (max_index_from_edges): Called
INFO (max_index_from_edges): Complete, result 5002
INFO (build_index_adj_list): Complete, result size 5003
clusters has 65 element(s)
first has size 1628
motifs has 65 element(s)
first is NNNNNN seen 73930 times 
Sorting by length...
Press any key to continue.
NNNNNN 73930 1628
NNNNNNN 30959 2428
NNNNNNNN 6157 789
GRAARBNNN 277 37
RRAAAAWNN 106 13
SCBSCSSNS 92 13
MRWMMYTTC 60 7
GKCGSGRMB 54 8
RGGAAGTDS 47 5
RGCGSGCGS 30 4
RGGAAGTGRB 29 5
RKCCAATB 28 5
AAAAAAAAMD 25 4
HGTCACTTCC 20 3
AAAAAAAAAAR 14 2
CYCCGCCCC 12 2
TTCCATTC 11 1
TGTAATCC 10 1
AAAAAAAAAARA 10 2
AGTGGCCC 9 1
GTAATCCC 8 1
CATTCTTTC 8 1
GCCGGCGCC 7 1
AAAAAAAAAAAAAG 7 1
GATGCCAC 6 1
AAAGGGAAC 6 1
GCTCGGCGC 6 1
CCCCACTTC 6 1
CTCCGCGGC 6 1
CCGGGTTC 5 1
AAACTGAG 5 1
AATAATCT 5 1
AAAGAGGC 5 1
ATGAAATA 5 1
AAATTTGG 5 1
TTTCTCCA 5 1
TGTCGCTC 5 1
AACCGGAG 5 1
AACTGAAG 5 1
AACTCCGC 5 1
AACTGCTT 5 1
CTCCCCCA 5 1
CACAGAGC 5 1
AGCGCCGAC 5 1
TGCAATTTC 5 1
ACTTTTTTC 5 1
GAAACCACC 5 1
AAAGCCTTC 5 1
AGCCCGGAG 5 1
AAAATTACA 5 1
CCTCGCTTC 5 1
AATGACTTC 5 1
AGCGCGGCC 5 1
AGGGCGGGGC 5 1
CTCCACTTCC 5 1
AGCCCCGCCC 5 1
GCTCCGCCCC 5 1
GTTCACTTCC 5 1
CCTCATTTCC 5 1
AGCAACTTCC 5 1
CCGCCGCCGC 5 1
CCGCCCCGCC 5 1
AAAAAAAAAAAAC 5 1
CGCGCGCGCGCGC 5 1
AAAAAAAAAAAAAAAGA 5 1
```
