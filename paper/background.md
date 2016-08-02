#Background 

##Biological basics

First, since this is a cross-disciplinary thesis, we shall establish
some context assuming minimal prior knowledge of biology, and introduce
some terminology. Because this is a mathematical thesis, no such basic
background in mathematics will be provided in the main body of the text,
though some background will be provided in Appendix A to cover any terms
not necessarily familiar to biologists.

Note that, due to the nature of biology, qualifiers such all "all",
"always", "every", "none" or "never" are rarely absolute when talking
about biological truths: There tends to be an exception to every rule,
but unless those are particularly relevant to the subject of interest,
we shall tacitly ignore them as edge cases. That being said:


###Cells

Every living thing is an organism, and every organism is either a cell
or composed of cells. Cells are microscopic sacs filled with chemicals
of various kinds, performing the various functions of life.

###RNA, Proteins, DNA

The most interesting of those chemicals in terms of complexity of form
and function are RNA, proteins and DNA. Each of these form
heteropolymers, sequences of similar but distinct sub-molecules, the
exact sequence giving rise to a specific function.

Generally, _proteins_ are the most flexible and powerful tools a cell has,
but they are end-products; no protein can be directly copied, and they
are generally fairly short-lived. _RNA_ can be replicated by itself, and
can either perform a narrow range of tasks by itself, or be
**translated** into protein.  However, RNA replication is not very
reliable, and RNA also tends toward short-livedness. 

Finally, _DNA_ is very stable, long-lived and reliably replicatable, but
cannot perform any useful function by itself, nor be translated into
protein.  However, its sequence can be **transcribed** to RNA,
exploiting their similarity in structure and replication mechanism. This
allows DNA to act as long-term sequence storage for both RNA and, via
RNA, proteins.

For a more in-depth look at these molecules, see Appendix B.


##Transcription factors

###Role
Transcription is tightly regulated, and necessarily so, since every cell
has, at all times, the instructions in its DNA to produce any and all
kinds of RNA and protein any cell in the entire organism might need at
any time. Being a liver cell is partly a matter of knowing not to be a
muscle cell. To achieve this regulation, over a thousand proteins
cooperate. Those which directly interact with DNA in the context of this
regulation are known as **transcription factors** (TFs), and their
behaviour will be the subject of the rest of this paper.

###Specificity
In order to perform any meaningful regulation, TFs must bind
specifically near the genes they are supposed to regulate, rather than
all over the genome. To achieve this specificity, specific sequences on
DNA are recognized and bound, ensuring locality of TF activity to genes
next to the corresponding sequences.

###Motifs 
Although each TF binds specific sequences, no TF binds just a single
sequence: There is a considerable degree of "fuzzy matching", giving
rise to a family of similar sequences which are recognized, some more
enthousiastically than others. This gives rise to the concept of a
**motif**: A sequence which, for each location, notes, not a specific
"letter", but the probability of each possible letter appearing in that
location.
