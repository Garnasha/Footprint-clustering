#Input Data

The data we will be using have been acquired using a rather blunt
approach: Rather than trying to track the behaviour of each individual
species of TF, a near impossible task, the behaviour of all TFs in a
living cell is analysed at once, using the procedure sketched below.

##Process
First, chemically "freeze" a cell with formaldehyde, instantly killing
it but preserving various aspects of its state at the moment of death,
among them what DNA is bound by what proteins. However, preserving state
and observing it are not the same; the best known approach to the latter
is then using DNAseI to cut all unbound DNA into small pieces, then
reversing the freezing process and seeing what parts remain uncut. Each
such uncut part represents a "footprint" of a TF bound at the moment of
death.

##Limitations
Unfortunately, this does not reveal anything about what protein did the
binding: all it reveals is what DNA was bound. This means
protein-specific information is lost, and any analysis, including this
one, can only draw conclusions "up to protein equivalence", which does
not yield protein identities.

##Caveat: Noise
More unfortunately, during the writing of this thesis, a source of noise
was discovered: DNAseI does not cut all DNA sequences equally. This
means that some sequences, while unbound, will still remain uncut due to
being ignored by DNAseI, giving the false impression of being bound. It
has been decided to accept this noise, since no dataset free of it is
available or likely to become available. 

##Noise mitigation 
In various places, treshold values are used in attempt to limit the
effect of this noise. While the noise might surpass this treshold in
some instances, it is hoped those instances will form clusters distinct
from legitimate clusters, possibly recognisably so, but at worst
yielding only false clusters, rather than fouling legitimate clusters.
This hope is founded in some biological properties of false and true
positives, which won't be discussed further here. (* Possibly create an
appendix B and refer to it here *)

##Data format 
The data has been supplied as a single file per dataset, with on each
line one footprint, formatted as such:
    `[chromosome ID] [start index] [end index]`
We cross-reference this with publicly available reference genomes,
formatted according to the fasta standard, to produce the associated
sequence for each footprint.

##Acknowledgement 
The dataset we have used has been produced by the stellar work of (*
Insert credits for dataset here *), who has/have our deep gratitude and
without whose generosity in sharing their test results this thesis would
have been impossible.
