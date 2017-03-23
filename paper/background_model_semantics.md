# Model
Before formulating the research question, we shall describe the problem
as a biological question, and then introduce a mathematical model of
this problem, with the associated semantics referring back to the
biological question. To do this, some background in biology is required
first.

## Biological background
This section will only cover common knowledge:

Biologists and those having completed any introductory course in
DNA biochemistry should be able to skip ahead to the subsection
[Transcription factors] \(and likely skip most of that). 

Molecular biologists should skip ahead to [Dataset], the next major
section.

###Caveat
When a mathematician says "for all" or "there is no" ("not exists"),
they mean it, much more so than is usual in common parlance. Biologists,
on the other hand, do not; they mean it as much as anyone describing the
real world means it. We will follow this latter convention in this
chapter, except where clearly purely mathematical statements are
concerned.

###Prior knowledge
We will assume the reader is familiar with biology up to the existence
of cells, DNA, chromosomes, genes and proteins. No intimate familiarity
with their properties is required; such as is needed will be noted here.

####Cells
Cells form more or less self-contained units: they can be isolated for
study without completely disrupting their behaviour (though some
disruption will occur). Our model will cover a part of the processes in
one cell, averaged over all cells in a sample.

####DNA
#####Nucleotides
DNA is a bioheteropolymer composed of nucleotides. There are 4
nucleotides used in the construction of DNA: dAMP, dCMP, dGMP and dTMP,
generally referred to as A, C, T, G. A strand of DNA is generally
represented by stringing the letters of the involved nucleotides
together in order: ACATGG refers to a single strand of DNA containing
every nucleotide once, and A and G twice.

#####Directionality
Nucleotides are asymmetrical, having distinct ends called 5' and 3'
(referring to the chemical numbering of those positions in the molecule),
and polymerization matches 5' to 3' ends, giving DNA a persistent
direction which is thought of as from 5' to 3', in which direction
sequences are always reported. So, ACTG is a strand with A at the 5'
end, and different from GTCA.

#####Complements
Each nucleotide has a complement: A complements T, C complements G.
Besides polymerizing "front" to "back", nucleotides can weakly connect
"side" to "side", but only to their complement. This also gives rise to
complements of sequences, being the pointwise complements of their
nucleotides, with one catch: the complement has reversed orientation.
Illustration: ACTG is complemented by CAGT (not TGAC):
```
5'-A-C-T-G-3'
   : : : :
3'-T-G-A-C-5'
```
In nature, all DNA strands are almost always paired up in complements,
forming "double stranded" DNA.

#####Pyramidines and Purines
Nucleotides vary in structure and size. A and G are "purines", similar
in structure and size and larger than the "pyramidines" T and C,
similarly similar to each other. This is relevant to note, since some of
the processes we will want to model might e.g. only react to a rising
edge (pyramidine to purine) or falling edge in a sequence, rather than
to any specific nucleotide. 

####Chromosomes
Human DNA is ordered into chromosomes, 23 pairs of extremely long double
DNA strands. Each cell has a copy, and distributed over these
chromosomes are all human genes (excepting mitochondrial DNA which we
won't get into). 

####Genes
Genes are sequences, located on chromosomes, which encode the sequence
of a specific protein. The exact nature of the encoding is not relevant
here, but the 1-on-1 nature is (although some genes apply tricks to encode
multiple related proteins): one gene being "active" corresponds to one
protein being mass-produced.

####Proteins
Proteins are a different kind of bioheteropolymer, forming the
workhorses of living cells. The sequence of a protein (along with some
post-processing) gives rise to its functionality.

###Transcription factors
Since every cell contains all genes, but no cell needs every gene, it
needs to be possible to toggle genes on and off. This is accomplished by
means of *Transcription Factors*, proteins which bind DNA and signal
"somewhere relatively near this place is a gene which should/shouldn't
be active". 

These transcription factors attach to DNA in the right locations by
recognizing (binding) specific sequences. However, they do not bind one
specific sequence. Rather, they bind any sequence which conforms to
specific properties, generally being "close enough" to some ideal
recognized sequence and identical in the most important positions.

The characterization of these families of recognized sequences, based on
the dataset described below, is the focus of this thesis.


##Dataset
###Reference Genome
Genetic information within a species is very similar, allowing the
construction of a reference genome, which is freely available on the
internet, courtesy of the Genome Reference Consortium.
--TODO-- (Mostly covered in dataset.md)


##Model
###DNA sequences
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

###Transcription factors
Since we do not have any data about the individual transcription factors
themselves, we will identify only the families of recognized sequences.
To do so, some notation for such a family is needed.

####Motifs
One way to denote such a family is a motif: a sequence of probabilities
of each nucleotide appearing. For mathematicians and programmers:

\begin{displaymath}
Sequence : \{A,C,T,G\}^*

Motif : ([0,1]^4)^*

t : \{A,C,T,G\} → [0,1], A ↦ (1,0,0,0), C ↦ (0,1,0,0), etc.

i : Sequence → Motif, () ↦ (), cw ↦ t(c)i(w)
\end{displaymath}

This is the notation preferred by biologists, but it strips some
information (like implications "A in position 2 requires that C be in
location 5"), and implies more knowledge about the family than I expect
can be gained from this dataset.

####Wildcard patterns
A simpler, cruder representation can be gained by replacing the [0,1] in
the motifs above with {0,1}, yielding values of "may appear" and "can't
appear". Since this representation conveys less information, it is
easier to construct from indirect observation, and will be the goal of
initial efforts.

####Advanced Motifs
Noting implications such as suggested for motifs might yield very
interesting results, but is a subject for future research.

#Research Question
Given the dataset and model as above, find Wildcard Patterns such that,
with high likelyhood, each Transcription Factor active in the cells
giving rise to the dataset matches every sequence within one of those 
Wildcard Patterns, and none outside it. Additionally, no spurious
wildcard patterns must be introduced: each must correspond to at least
one TF. So, there must be a surjective function `f` from TFs to Wildcard
Patterns, and with 
```
matches: Wildcard -> P(Sequence) 
recognizes: TF -> P(Sequence)
```
with the obvious interpretations, we want `matches o f = recognizes`.

Note: `f` should exist, but doesn't have to be known (nor could it be
found in this dataset): The set of wildcards produced should merely be
such that it *can* exist.
