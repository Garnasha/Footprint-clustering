# Biological background
This section will only cover common knowledge:

Biologists and those having completed any introductory course in
DNA biochemistry should be able to skip ahead to the subsection
[Transcription factors] \(and likely skip most of that). 

Molecular biologists should skip ahead to [Dataset], the next major
section.

##Caveat
When a mathematician says "for all" or "there is no" ("not exists"),
they mean it, much more so than is usual in common parlance. Biologists,
on the other hand, do not; they mean it as much as anyone describing the
real world means it. We will follow this latter convention in this
chapter, except where clearly purely mathematical statements are
concerned.

##Prior knowledge
We will assume the reader is familiar with biology up to the existence
of cells, DNA, chromosomes, genes and proteins. No intimate familiarity
with their properties is required; such as is needed will be noted here.

###Cells
Cells form more or less self-contained units: they can be isolated for
study without completely disrupting their behaviour (though some
disruption will occur). Our model will cover a part of the processes in
one cell, averaged over all cells in a sample.

###DNA
####Nucleotides
DNA is a bioheteropolymer composed of nucleotides. There are 4
nucleotides used in the construction of DNA: dAMP, dCMP, dGMP and dTMP,
generally referred to as A, C, T, G. A strand of DNA is generally
represented by stringing the letters of the involved nucleotides
together in order: ACATGG refers to a single strand of DNA containing
every nucleotide once, and A and G twice.

####Directionality
Nucleotides are asymmetrical, having distinct ends called 5' and 3'
(referring to the chemical numbering of those positions in the molecule),
and polymerization matches 5' to 3' ends, giving DNA a persistent
direction which is thought of as from 5' to 3', in which direction
sequences are always reported. So, ACTG is a strand with A at the 5'
end, and different from GTCA.

####Complements
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

####Pyramidines and Purines
Nucleotides vary in structure and size. A and G are "purines", similar
in structure and size and larger than the "pyramidines" T and C,
similarly similar to each other. This is relevant to note, since some of
the processes we will want to model might e.g. only react to a rising
edge (pyramidine to purine) or falling edge in a sequence, rather than
to any specific nucleotide. 

###Chromosomes
Human DNA is ordered into chromosomes, 23 pairs of extremely long double
DNA strands. Each cell has a copy, and distributed over these
chromosomes are all human genes (excepting mitochondrial DNA which we
won't get into). 

###Genes
Genes are sequences, located on chromosomes, which encode the sequence
of a specific protein. The exact nature of the encoding is not relevant
here, but the 1-on-1 nature is (although some genes apply tricks to encode
multiple related proteins): one gene being "active" corresponds to one
protein being mass-produced.

###Proteins
Proteins are a different kind of bioheteropolymer, forming the
workhorses of living cells. The sequence of a protein (along with some
post-processing) gives rise to its functionality.

##Transcription factors
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
