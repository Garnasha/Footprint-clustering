#Discussion and reflection
##Main conclusion
Based on the summary given above, the main result is negative: No useful
clusters can be found in the majority of the dataset by this algorithm.
From this, we can conclude that a simple Hamming metric is probably too
coarse. The lowest non-zero distance it can create is 1, and this has
been taken as the maximum distance to relate two otherwise unrelated
sequences. No stricter criterion is possible, yet it is not strict
enough to not absorb the vast majority of the data into a single cluster
per sequence length.

What this says about the dataset is that, using this metric, we can walk
within sequences in the dataset from almost any point to almost any
other point without ever having a step distance greater than 1.
Intuitively, this seems to indicate that if any real clusters exist,
those clusters all touch, which gives a rather "fuzzy" view.

Alternatively, the dataset might just be too noisy. However, if this is
the case, the majority of the dataset is under the noise floor, based on
trial and error with the minimum occurence count setting: any setting
which eliminates the "all" cluster leaves only a few scattered peaks,
with no or nearly no actual clustering occurring. 

Note that this is a property of the dataset equipped with this metric:
Other metrics might produce a clearer view, and indeed this is likely if
they have more possible values and are chosen sensibly.

The problem, however, might very well be the MST algorithm itself: it
cannot distinguish overlapping clusters at all, and such overlap is not
impossible or even unlikely given the subject matter. If clusters
overlap, a more sophisticated algorithm will be required, likely
designed specifically with this problem in mind, rather than this most
generic of clustering algorithms.

##Other considerations
###Singleton clusters
The tails of singletons noted in the summary are very unlikely to
actually exist as proper motifs belonging to transcription factors,
especially considering their low occurence numbers. They are almost
certainly noise, and should be ignored.

However, their existence also indicates the amount of noise in the
entire dataset, including where it might interfere with clustering
algorithms. Any succesful clustering algorithm will have to handle such
noise correctly. A filter capable of removing such noise before clustering
might work, but ideally, clustering algorithms should be made inherently 
robust against this type of noise.

###Similarity across lengths
In designing both the distance function and the join function, it had
been assumed that all sequences within a motif should be of the same
length. Several sequences in the result seem to contradict this
assumption, including some non-trivial pairs with a length difference of 1.  
Therefore, future algorithms should *not* make this assumption, and
instead find some way to interpret and represent similarity between
sequences of different lengths.

##Potential improvements
###Distance functions
The distance function used was a simple Hamming metric, which is
relatively coarse. Several refinements are imaginable:

####Sequence-based refinement
Not all distances between two nucleotides are equal: each nucleotide has
spatial and chemical features which are closer to or further from
those of each other nucleotide. Incorporating such differences into the
distance function could increase point-wise resolution, if based on
biochemical knowledge. This would in turn increase resolution on the
sequence level.

Additionally and alternatively, some features recognized by
transcription factors are known to be based not on individual
nucleotides, but by the transition between them in a sequence. Thus, the
metric could be enriched by adding some similarity score if certain
properties on sequential pairs of nucleotides are equal, rather than the
nucleotides themselves.

####Frequency-based refinement
There is a possibility that motifs have properly disjoint "cores" which
are most often seen, but also contain less commonly seen "peripheries",
which can overlap. If so, clusters might be distinguishable by having
distances between sequences seen with low frequency be penalized
(increased) compared to distances between high-frequency sequences. This
would, under the assumptions given, keep cluster cores together while
pushing the confounding peripheries apart.

###Alternative algorithms
Constructing an MST doesn't really leave any choices or tuning variables,
so it is hard to improve it except by choosing a better distance
function. Alternative algorithms are thinkable however, so long as one
keeps in mind that the sequence space does not have meaningful averages,
and so it's not possible to use averaging-based clustering algorithms.

####Convexity-based
One very plausible hypothesis is that true clusters are (mostly) convex.
This requires a generalisation of the concept of convexity:

A subset $A$ of a metric space $X$ is considered convex iff
$\forall x, y \in A \, \forall z \in X \, d(x,z) + d(z,y) = d(x,y) \Rightarrow z \in A$. 

In other words, if two points are in a convex set, that set must also
include all points "between" them for which the triangle inequality is
an equality. This is consistent with the notion of convexity in spaces
with weighted averages such as real and complex numbers and vector
spaces.

Given such a notion of convexity, it might be possible and useful to
define an algorithm based on trying to split non-convex clusters,
ideally such that as many points in the cluster but not in the dataset
are excluded from the union of the two new clusters (intuitively, split
along the plane of maximum missing datapoints in the cluster). Given an
algorithm to perform such a step, apply this iteratively to the most
non-convex cluster after each step, starting with a universal cluster.

No attempt has been made here to write such an algorithm beyond
formulating the concept, but further work could include making such an
attempt.

####Co-occurrence based
Another possibility is to look not only at what sequences are found, but
also where they are found. Transcription factors form complexes, so
often, the same motifs will always occur together, with similar relative
positioning. It is possible to base a statistical algorithm on this,
with the chance of two sequences belonging to the same motif increasing
as they occur next to the same other motif. This is a very different
approach, and only vaguely sketched here, but it might detect patterns
which pure sequence-based algorithms would miss.

###Dealing with different sequence lengths
While it is relatively easy to adapt distance functions to enable
comparisons on sequences of unequal length, by replacing Hamming
distances by edit distances, doing the same for joins is a greater
challenge, and we will make no attempt at a solution here.
