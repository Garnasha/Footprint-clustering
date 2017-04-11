#Formalised Research Problem
Given the dataset and model as above, find Wildcard Patterns such that,
with high likelihood, each Transcription Factor active in the cells
giving rise to the dataset matches every sequence within one of those
Wildcard Patterns, and none outside it. Additionally, no spurious
wildcard patterns must be introduced: each must correspond to at least
one TF. So, there must be a surjective function $f$ from TFs to Wildcard
Patterns, such that
$\text{matches}: \text{Wildcard} \rightarrow \mathcal{P}(\text{Sequence})$, 
$\text{recognizes}: \text{TF} \rightarrow \mathcal{P}(\text{Sequence})$, 
with the obvious interpretations, satisfy $\text{matches} \circ f = \text{recognizes}$.

Note: $f$ should exist, but doesn't have to be known (nor could it be
found in this dataset): The set of wildcards produced should merely be
such that it *can* exist.
