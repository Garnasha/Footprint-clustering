#Algorithms

To achieve the desired program, we will consider, implement, compare
and possibly **FIXME** combine several clustering algorithms, outlined
below.

##Minimal spanning tree-based

###Justification
One approach is to use the fact that sequences within a motif can't be
too different; therefore, all sequences matching a motif must fall
within a fairly close edit distance of each other. Conversely, sequences
with small edit distances to each other are likely to belong to the same
motif. Since MSTs form a grouped measure of closeness, they can be used
to search for a cluster.

###Outline
The algorithm is rather straightforward: Convert all footprints to
sequences, yielding a multiset. Take the weighted complete graph on
these sequences, with weights equal to the distance between sequences.
Construct the MST and remove the longest edges from the MST, yielding 
a forest. Each connected component is now expected to correspond to a
motif, which can be found or approximated as the "join" of the sequences
in the component.

###Tuning factors
Decisions which need to be made in this algorithm are:
 * What metric to apply to the sequences.
 * How to decide how many edges to take away. This can be some constant,
   or based runtime on the dataset.
 * What join to use.
 
###Strengths
 * Easy to implement
 * Low computational complexity

###Weaknesses
 * Likely bad resolution
 * Can not tell motifs apart whose matching sequences are too close
   together. Actual overlap cannot compensated for by any amount of
   tuning.

##Clique-based

###Justification 
This algorithm is justified the same way as the MST-based algorithm:
sequences with small edit distances to each other are likely part of the
same motif. However, rather than rely on the sparse structure of an
MST-based forest, we search for any subsets with a limited diameter,
effectively searching for cliques in the subgraph obtained by limiting
maximum edge weight of the full graph.

###Strengths
 * Correctly tells apart motifs whose matching sequences partially
   overlap.
 * Under some assumptions, every motif should yield a clique, while
   random large cliques are very unlikely.

###Weaknesses
 * Computationally expensive, and thus hard to implement efficiently.
 * The assumptions required to make motifs yield cliques are quite
   limiting, and likely false in practice.

##Convex Pseudo-clique-based

###Justification
While MST is too forgiving, and will lump together unrelated motifs if
their sequence sets intersect at all, cliques are too restrictive,
trying to restrict motifs beyond the diameter of their actual sequence
sets. Therefore, a mixed approach might work best, allowing the diameter
of a clique to expand, but only while it remains (mostly) convex in
edit distance-based sequence-space. 

###Strengths
 * The mechanics of TF binding mean that proper sequence sets are
   expected to be mostly convex
 * Under some assumptions, will yield minimal false positives and false
   negatives, behaving like MST for motifs with actual big sequence
   sets, and like cliques for overlapping sets.
 * Such assumptions are relatively weak, much more likely to be true,
   and more amenable to fudging by tuning variables than the pure
   cliques approach.

###Weaknesses
 * Potential computational nightmare.
 * Lots of tuning variables.
 * Appropriate algorithms are more obscure or non-existent

##Tentative wildcard addition
**FIXME**

##Association Analysis-based

###Justification 

Another approach is based on the fact that the TFs binding these motifs
do not exist in a vacuum: they often work together in set combinations,
each partner binding a seperate location.  Therefore, given the motif of
one TF, the set of sequences appearing near each instance of the known
motif, at roughly the same offset, could very well match the exact motif
of a fixed partner TF. Using association analysis on the set of
footprints, basing equality on sequence and association on spatial
nearness, might succesfully exploit this property to reveal motifs with
more sensitivity and less noise than sequence-only approaches can
achieve.

###Strengths
 * Has more information to work with, so has a higher upper limit of
   resolution.
 * Has the potential to tell apart near-identical motifs, or recognize
   even identical motifs as being used in different contexts
 * Well-known algorithms exist in Big Data literature.

###Weaknesses
 * Likely computationally intensive
 * Might need help from sequence-based algorithms for both sanity
   checking and to correctly categorize rare forms of a motif.
 * Well-known is not the same as easily implemented or easily proven
   correct.
