#Synopsis


##Motivation

An interesting question in biology is how decision-making at the
molecular level is regulated. The "source code", DNA, is known, but not
fully understood. While we do have the equivalent of a parts list, we don't
yet know for each part where it goes and what it does. Cells produce
different "parts" to adapt to different roles and circumstances; by
understanding how they select those parts, we can hope to simultaneously
infer the function of the more obscure parts, and the structure of the
larger machine. Additionally, the selection process itself is key in
various disease processes, and as such is therapeutically interesting in
itself.

Since ChIP-sequencing for every transcription factor is expensive and
does not work in vivo, it is tempting to look for alternatives. In this
thesis, we will try one such alternative approach by looking for common 
motifs in transcription factor footprints.


##Raw Data

This approach is based on analysis of the data produced by a rather
unsubtle technique known as footprinting: It is possible to chemically
"freeze" a cell, killing it but preserving various aspects of its state,
among them what DNA is bound by what proteins. However, preserving state
and observing it are not the same; the best known approach to the latter
is using DNAseI to cut all unbound DNA into small pieces, then reversing
the freezing process and see what parts remain uncut. Unfortunately,
this does not reveal anything about what protein did the binding: all it
reveals is what DNA was bound.


##Intent 

The idea, then, is as follows: apply Big Data techniques to datasets
acquired as above, and, through clustering, produce hypotheses about
what motifs must exist, even though the corresponding proteins remain
unknown. For this purpose, we will implement and test both MST- and
association analysis-based clustering algorithms, and compare them to
each other and to known solutions for some datasets.





####Background
An important role in this regulation is known to be fulfilled by
transcription factors. To do something, a cell generally needs some
specific protein. To make that protein, the DNA encoding it (gene) must 
be read (expressed). To ensure genes are expressed *iff* their protein
product is needed, regulatory proteins bind the DNA around each gene,
and help or hinder gene expression depending on the needs of the cell.
These regulatory proteins are called transcription factors (TFs), and their
recognition of the proper locations in DNA to bind will be the focus of
my thesis.

####Intent
These transcription factors bind specific locations in DNA because they
recognize specific sequences. However, there is a considerable degree of
"fuzzy matching", leading to recognized "motifs", families of similar
sequences, rather than a single sequence corresponding to 

For my thesis, I will be looking at common motifs in so-called
transcription factor footprints. 


The easy parts are genes, which encode (mostly)
proteins. This, however, only translates to a parts list, for the entire
organism, and takes up about 2% of e.g. human DNA.
