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
 * Cannot tell motifs apart whose matching sequences are too close
   together. Actual overlap cannot be compensated for by any amount of
   tuning.

###Detailed description
####Reading the data
#####Data format
The data consists of a list of all locations of footprints, in the
format
```
<chromosome name> <start index> <end index>
```
as well as, for each chromosome name, a file containing the sequence of
that chromosome in FASTA-format, named `<chromosome name>.fa`

#####Reading Algorithm
Since the human genome is rather large (on the order of 3GB), we don't
want to open all files at once. Therefore, we first parse the locations
file into a mapping from chromosomes to lists of locations on that
chromosome.  Then, for each entry in this mapping, we open the
corresponding file, look up every footprint on that chromosome, and note
their sequence together with their location, before closing the file and
moving on to the next chromosome. This yields a list of all footprints
with both location and sequence known.

We now have a $\texttt{raw\_dataset} = \{(\lookup(l), l) \mid l ∈ \texttt{locationfile} \} ⊂ \Sequences × \Locations$ where

$$\Sequences = \text{Nucleotides}^*$$
$$\Locations = \text{Strings} × ℕ × ℕ$$
$$\text{Strings} = \text{AlphaNumeric}^*$$
$$\texttt{locationfile} = \text{(the locations of all footprints)} ⊂ \Locations$$
$$\lookup : \Locations → \Sequences, \text{location} → \text{sequence at that location in the chromosome files}$$


####Taking the multiset
This particular algorithm doesn't care about location (no useful metric
considers it), but some possible refinements consider how often a
particular sequence occurs (for cutoff criteria, or metric tweaking).
Therefore, count occurences and discard locations, yielding a new
$\text{dataset} ⊂ \Sequences × ℕ$

####Minimal Spanning Tree Construction
The construction of a Minimal Spanning Tree is done by Prim's Algorithm,
a standard memoized greedy algorithm which takes a set of vertices $V$ and a
weight function $w: V × V → W ⊂ ℝ$ on these vertices. By setting

$$V ⊂ \Sequences × ℕ$$
$$w = d\text{ for some metric }d : V × V → ℝ$$

we can use Prim for clustering in a metric space. NB: while metrization
is possible, V does not have any obvious concept of averages (it can,
however, be embedded in a join-semilattice, which we will use later)

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

Running `Prim(dataset,d,v ∈ dataset)` yields `MST = (V,E)`.

#####A note on complexity and choice of algorithms
An alternative approach to constructing the MST would be to use
Kruskal's algorithm, which does not construct a tree but simply keeps
adding the shortest edges overall without forming cycles.

However, this performs slightly worse than linear in the amount of
edges, while Prim's algorithm can be made quadratic in the amount of
vertices. Since we're effectively operating on a complete graph, the
amount of edges is the square of the amount of vertices, making Prim's
algorithm strictly linear in the amount of edges.

Several other algorithms exist, but we aren't aware of any that do
better than linear in the amount of edges.

####Choosing the distance metric
*FIXME:* For now, we have set `d = hamming o π₁` , so a simple hamming
distance on the sequence, ignoring the count.

####Culling the MST
The hypothesis now is that vertices which should be clustered will be
close in the MST, and so cutting longest edges will not split any true
clusters. Therefore, decide on some number N of edges to cut and remove
the N longest edges from E to yield E′, resulting in a forest of N+1
components.

####Selecting the amount of edges to cut
*FIXME:* Currently, this is a constant, based on a reasonable guess at
the amount of clusters in the data.

####Collecting the MST
Now determine the connected components
$\{V[n] = \{v ∈ V \mid ∃ \text{path from } v[n] \text{ to } v\}\}$ with $∀n ¬∃m<n, v[n] ∈ V[m]$

####Taking the join of a connected component.
At this point, we want to produce a list of motifs to answer the
biological question. To do this, we embed the sequence space Sequence
(from chapter [Model]) into the wildcard space
$\Wildcard:=({0,1}⁴)^*$ by embedding $i: \nA ↦ (1,0,0,0), \nC
↦ (0,1,0,0), \nT ↦ (0,0,1,0), \nG ↦ (0,0,0,1)$. Now we
define a join-semilattice on $\Wildcard$, by defining the join of two
motifs of the same length to be their pointwise coordinatewise
disjunction:

\begin{flalign*}
\join : & \{0,1\}⁴ \times \{0,1\}⁴ → \{0,1\}⁴ \\
        & ((x₁,x₂,x₃,x₄),(y₁,y₂,y₃,y₄)) ↦ (x₁ ∨ y₁,x₂ ∨ y₂,x₃ ∨ y₃,x₄ ∨ y₄) \\
\join : & \left(\{0,1\}⁴\right)^* × \left(\{0,1\}⁴\right)^* → \left(\{0,1\}⁴\right)^* \\
        & (l, r) ↦ \begin{cases}
            () &\mbox{if } (l, r) = ((),()) \\
            \join(b, c) ⋅ \join(v, w) &\mbox{if } (l, r) = (bv, cw) \\
            ↑ &\mbox{otherwise}
        \end{cases}
\end{flalign*}

Having defined this semilattice, we can take the join of each cluster,
translate the resulting may/may not appear-codes back into standard
IUPAC DNA ambiguity codes, and deliver these to biologists as our best
guess.


####Formalism and types (WIP)
We'll first note some type definitions, then note the steps taken in
pseudocode. Lines starting with `Let` introduce some concept not easily
or concisely expressible in pseudocode, and follow mathematical
conventions instead. Comments will be proceded by "Note:"

NB: We will ignore most details of the interpretation of this
formalism. While systems for rigorous typing of IO actions do exist (IO
monad, uniqueness typing), this is not the subject of this thesis.
Instead, we'll leave this to the actual implementation, and introduce
some dummy functions to mark where files are opened and closed.
```
Let Numeric, AlphaNumeric, * (Kleene Star), N have their usual meanings.

toNat : Numeric* → N,
    base 10 notation of n |→ n

Strings := AlphaNumeric*

Let Files be the set of files.

open : Strings → Files ,
       path |→ file in the location described by path

close : Files → {1}
     , file |→ 1
Note: This is a placeholder to denote the closing of a function.

Let Nucleotides be the set of nucleotides, representable by
{'a','c','t','g'}.

Sequences := (Nucleotides U {'N'})*

readFasta : Files → Sequences

```
