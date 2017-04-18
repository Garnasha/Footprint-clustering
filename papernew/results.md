#Results
[Appendix: Results] contains raw output of various runs of the
program compiled from the current version of the source.

##Reading the raw results
Except for the dialogue setting the minimum occurence count ("cutoff")
on lines 3 and 4, the first part of each run of output is diagnostic
information. This has been introduced in the debugging phase, and gives
some insight into the state of the program during execution,
facilitating potential further development. Outside of development, it
should be ignored.

Actual output starts, in each run, below the line "Press any key to
continue." After this, every line contains one motif, formatted as
```
<sequence> <#(data points in cluster)> <#(unique original sequences in cluster)>
```
With sequences written using standard IUPAC ambiguity codes [see
@iupacodes]. The lists are sorted by the second column, with shorter
sequences coming first in case of a tie.

All runs are performed with the same settings, except for the lower
limit on the amount of identical sequence occurences in the input
dataset required before a sequence gets included as a data point for the
MST algorithm.

Runs are presented in no particular order. Runs with lower limits below
5 are excluded from the print version, due to such settings creating
excessive amounts of output. Digital plain text files for runs with
lower limits 3 and 1 (no filter) are available.


##Summary
While the output of the analysis program itself is too large to include
here, a summary is possible:

 - The vast majority of the data is absorbed by $N^*$ sequences of
   various lengths, which accept everything.
 - For every lower bound, the data has a tail of sequences, each output
   sequence based on a single input sequence (degenerate clusters).
 - There are several examples of sequences which look very similar, but
   are of different length.
