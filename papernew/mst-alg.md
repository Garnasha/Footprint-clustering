#Algorithm
We will use an algorithm based on finding a minimal spanning tree,
then strategically removing edges to get a forest with each connected
component being a cluster. 

Different algorithms have been considered, but have not been implemented
due to time constraints. Some of these will be discussed in
\autoref{potential-improvements}.

##Justification
In this approach, we use the fact that sequences within a motif can't be
too different; therefore, all sequences matching a motif must fall
within a fairly close edit distance of each other. Conversely, sequences
with small edit distances to each other are likely to belong to the same
motif. Since MSTs form a grouped measure of closeness, they can be used
to search for a cluster.

##Outline
The algorithm is rather straightforward: Convert all footprints to
sequences, yielding a multiset. Take the weighted complete graph on
these sequences, with weights equal to the distance between sequences.
Construct the MST and remove the longest edges from the MST, yielding
a forest. Each connected component is now expected to correspond to a
motif, which can be found or approximated as the "join" of the sequences
in the component.

##Tuning factors
Decisions which need to be made in this algorithm are:

 * What metric to apply to the sequences.
 * How to decide how many edges to take away. This can be some constant,
   or based runtime on the dataset.
 * What join to use.

##Strengths
 * Easy to implement
 * Low computational complexity

##Weaknesses
 * Likely bad resolution
 * Cannot tell motifs apart whose matching sequences are too close
   together. Actual overlap cannot be compensated for by any amount of
   tuning.

##Detailed description
###Reading the data
####Data format
The data consists of a list of all locations of footprints, in the
format
```
<chromosome name> <start index> <end index>
```
as well as, for each chromosome name, a file containing the sequence of
that chromosome in FASTA-format, named `<chromosome name>.fa`

####Reading Algorithm
Since the human genome is rather large (on the order of 3GB), we don't
want to open all files at once. Therefore, we first parse the locations
file into a mapping from chromosomes to lists of locations on that
chromosome.  Then, for each entry in this mapping, we open the
corresponding file, look up every footprint on that chromosome, and note
their sequence together with their location, before closing the file and
moving on to the next chromosome. This yields a list of all footprints
with both location and sequence known.

We now have a $\texttt{raw\_dataset} = \{(\lookup(l), l) \mid l \in \texttt{locationfile} \} \subset \Sequences \times \Locations$ where

$$\Sequences = \text{Nucleotides}^*$$
$$\Locations = \text{Strings} \times \mathbb{N} \times \mathbb{N}$$
$$\text{Strings} = \text{AlphaNumeric}^*$$
$$\texttt{locationfile} = \text{(the locations of all footprints)} \subset \Locations$$
$$\lookup : \Locations \rightarrow \Sequences, \text{location} \mapsto \text{sequence at that location in the chromosome files}$$


###Taking the multiset
This particular algorithm doesn't care about location (no useful metric
considers it), but some possible refinements consider how often a
particular sequence occurs (for cutoff criteria, or metric tweaking).
Therefore, count occurences and discard locations, yielding a new
$\text{dataset} \subset \Sequences \times \mathbb{N}$

###Noise Reduction: Minimum Occurrence Count
Since we expect noise to not produce the same sequence over and over,
but do expect legitimate footprints to do so, we apply a filter at this
point: Any sequence which does not occur at least $N$ times is
discarded, producing a high-pass filter of sorts. Since we have no
algorithm to determine a good value for $N$ from the dataset, we ask for
a value for $N$ at run-time, and let the user determine a good value by
trial and error.

###Minimal Spanning Tree Construction
The construction of a Minimal Spanning Tree is done by Prim's Algorithm
[as described in @tarjan1983 p. 76], a standard memoized greedy
algorithm which takes a set of vertices $V$ and a weight function $w: V
\times V \rightarrow W \subset \mathbb{R}$ on these vertices.

By setting
$$V \subset \Sequences \times \mathbb{N}$$
$$w = d\text{ for some metric }d : V \times V \rightarrow ℝ$$
we can use Prim for clustering in a metric space. Since this gives us
a complete graph, we will not be using the heap-based optimization for
sparse graphs [described in @tarjan1983 p. 77].

NB: while metrization is possible, V, not being a ring, does not have
any obvious concept of averages. It can, however, be embedded in a
join-semilattice, which we will use later.

The idea behind Prim's algorithm is to expand the tree iteratively,
calculating at each step which node not in the tree is closest to the
tree (this being the minimum distance to any node in the tree), then
adding that node to the tree, recalculating minima, and going to the
next iteration until all nodes are in the tree, at which point our tree
is both spanning and minimal.

Note that in the first iteration, there is no tree yet. However, we can
simply set any vertex $r$ to be in the tree, giving us a valid 1-vertex
tree.

Pseudocode for Prim:
```
Prim (V, w, r ∈ V):
    let W : P(V) × V → ℝ,
        (A,v) ↦ min({w(a,v) | a ∈ A})
    let MINFROM : P(V) × V → V,
        (A,v) ↦ a ∈ A with w(a,v) = W(A,v)
    let MINTO : P(V) → V,
        A ↦ v ∈ V\A with W(A,v) = min({W(A,u) | u ∈ V\A})
    ##Note: the choices in CLOSEST and MIN are finite
    ##Note: we will explicitly calculate both W and MINFROM as part of
    ##  the algorithm: their definition above is for clarity and to show
    ##  correctness. Since this turns W into a lookup operation (O(1)),
    ##  MINTO can be calculated in O(|V|)
    Let T[0] = {r}
    We have:
        W(T[0],v) = w(r,v)
        MINFROM (T[0],v) = r
    Let E[0] = ∅
    Now inductively define:
        u = MINTO(T[n])
        E[n+1] = E[n] ∪ {(MINFROM(u),u)}
        T[n+1] = T[n] ∪ {u}
        and we have:
            W(T[n+1],v) = min(W(T[n],v),w(u,v))
            MINFROM(T[n+1],v) = MINFROM(T[n],v)     | W(T[n+1],v) = W(T[n],v)
                              = u                   | otherwise
    Now T[n-1] = V, and (V,E[n-1]) forms a Minimal Spanning Tree
```

Given this algorithm, we run `Prim(dataset,d,v ∈ dataset)` and obtain an MST.

####A note on complexity and choice of algorithms
An alternative approach for constructing the MST would be to use
Kruskal's algorithm, which does not expand a single tree but simply
keeps adding the shortest edges overall without forming cycles, forming
a forest which eventually merges into one tree.

However, this performs slightly worse than linear in the number of
edges, while Prim's algorithm can be made quadratic in the number of
vertices [see @tarjan1983 pp. 74-76]. Since we're effectively
operating on a complete graph, the number of edges is the square of the
number of vertices, making Prim's algorithm strictly linear in the
number of edges, and therefore optimal.

Several other algorithms exist, but we aren't aware of any that perform
better than linear in the number of edges.

###Choosing the distance metric
In this thesis, we have set $d = hamming \circ \pi_1$, a simple hamming
distance on the sequence, ignoring the count. This is the simplest
reasonable metric. Due to time constraints, no more sophisticated
metrics have been tried, although the code does support using custom
metrics if any are available.

###Culling the MST
The hypothesis now is that vertices that should be clustered will be
close in the MST, and so cutting longest edges will not split any true
clusters. Therefore, decide on some number $N$ of edges to cut and
remove the $N$ longest edges from $E$ to yield $E′$, resulting in a
forest of $N+1$ components.

###Cutting criterion
After some trial-and-error, we have concluded that cutting all edges
longer than 1 is the best cutting policy when using Hamming distances.
Metrics offering a better resolution should be combined with a more
sophisticated cutting criterion. 

###Collecting the MST
Now determine the connected components by iterating over all vertices,
doing a simple (depth-first) tree traversal to discover all vertices
reachable from the current vertex, marking all vertices so found,
recording them as one cluster, and skipping marked vertices in future
iterations to avoid duplication.

####Taking the join of a connected component.
At this point, we want to produce a list of motifs to answer the
biological question. To do this, we embed the sequence space Sequence
(from chapter [Model]) into the wildcard space
$\Wildcard:=(\{0,1\}^4)^*$ by embedding $i: \nA \mapsto (1,0,0,0), \nC
\mapsto (0,1,0,0), \nT \mapsto (0,0,1,0), \nG \mapsto (0,0,0,1)$. Now we
define a join-semilattice on $\Wildcard$, by defining the join of two
motifs of the same length to be their pointwise coordinatewise join:

\begin{flalign*}
\join : & \{0,1\}^4 \times \{0,1\}^4 \rightarrow \{0,1\}^4 \\
        & ((x_1,x_2,x_3,x_4),(y_1,y_2,y_3,y_4)) \mapsto 
        (x_1 \vee y_1,x_2 \vee y_2,x_3 \vee y_3,x_4 \vee y_4) \\
\join : & \left(\{0,1\}^4\right)^* \times \left(\{0,1\}^4\right)^* 
        \rightarrow \left(\{0,1\}^4\right)^* \\
        & (l, r) \mapsto \begin{cases}
            () &\mbox{if } (l, r) = ((),()) \\
            \join(b, c) \cdot \join(v, w) &\mbox{if } (l, r) = (bv, cw) \\
            \uparrow &\mbox{otherwise}
        \end{cases}
\end{flalign*}
Having defined this semilattice, we can take the join of each cluster,
translate the resulting may appear/may not appear-codes back into standard
IUPAC DNA ambiguity codes, and deliver these to biologists as our best
guess.

##Code
The code for the algorithm described above is included in Appendix Code, 
as well as digitally at [www.math.ru.nl/~bosma/Students?/????] . 

