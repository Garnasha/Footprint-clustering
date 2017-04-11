#Model
##DNA sequences
We will represent DNA sequences the usual way, noting only one side of a
double strand.

Because the interactions we are interested in involve double strands, we
will identify each sequence with its complement (since the double strand
they form is the same). This is non-trivial in implementation, and so
should be explicitly addressed in implementing any sub-algorithm which
considers sequences directly.

The distinction between pyramidines and purines, while interesting, has
not been modeled due to time constraints and difficulty using this
information in algorithms not built around it. This is an area for
future work.

##Transcription factors
Since we do not have any data about the individual transcription factors
themselves, we will identify only the families of recognized sequences.
To do so, some notation for such a family is needed.

###Motifs
One way to denote such a family is a motif: a sequence of probabilities
of each nucleotide appearing. For mathematicians and programmers:

$$\text{Sequence} : \left \{ \nA, \nC, \nT, \nG \right \}^*$$
$$\text{Motif} : \left( [0,1]^4 \right)^*$$
$$t : \{ \nA, \nC, \nT, \nG \} \rightarrow [0,1], \nA \mapsto (1,0,0,0), \nC \mapsto (0,1,0,0), \text{etc.}$$
$$i : \text{Sequence} \rightarrow \text{Motif}, () \mapsto (), cw \mapsto t(c) i(w)$$

This is the notation preferred by biologists, but it strips some
information (like implications "A in position 2 requires that C be in
location 5"), and implies more knowledge about the family than can
likely be gained from this dataset.

###Wildcard patterns
A simpler, cruder representation can be gained by replacing the $[0,1]$ in
the motifs above with $\{0,1\}$, yielding values of "may appear" and "can't
appear". Since this representation conveys less information, it is
easier to construct from indirect observation, and will be the goal of
initial efforts.

###Advanced Motifs
Noting implications such as suggested for motifs might yield very
interesting results, but is a subject for future research.
