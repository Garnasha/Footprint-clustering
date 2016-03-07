module ReadFasta

using BioSeq

const datapath="/home/sal/scriptie/data/"
const refpath=datapath*"reffa/"
const monocytes="Monocytes_0.05FDR_FOOTPRINTS"

pop=s->s[1:end-1]

type Chromosome
	name::ASCIIString
	seq::Vector{Nucleotide} 
end

type Footprint
	chr::ASCIIString
	seq::Vector{Nucleotide} 
	loc::Tuple{Int,Int}
end
	
function readfa(chrN::ASCIIString)
	Chromosome(chrN,Vector{Nucleotide}(*(map(pop,Vector{ASCIIString}(readlines(refpath*"$chrN.fa")[2:end]))...)))
end

##  function readfa(chrN::ASCIIString)
##  	lines=Vector{ASCIIString}(readlines(refpath*"$chrN.fa"))
##  	for k in 1:length(lines)
##  		lines[k] = pop(lines[k])
##  	end
##  	readfa_inner(chrN,lines[2:end])
##  end
##
function readfa_inner(chrN,file)
	Chromosome(chrN,Vector{Nucleotide}(*(file)...))
end

function parsefootprint_helper(chr,n,i,j)
	Footprint(n,chr.seq[parse(i):parse(j)],(parse(i),parse(j)))
end

function parsefootprint(entry::ASCIIString,chr) #TODO: turn this into a ctor or conv
	@assert split(entry)[1] == chr.name
	parsefootprint_helper(chr,split(entry)...)
end

function pushifnew!(v,s)
	if (length(v) > 0 ?v[end] == s:false)
		v
	else
        push!(v,s)
	end
end

function readfootprints(footprintfilename)
	fpfile=readlines(footprintfilename)
	readfootprints_inner(fpfile)
end

function readfootprints_inner(fpfile)
	sort!(fpfile,by=(s->split(s)[1]))
	chrlist=mapreduce(s->split(s)[1],(v,s)->pushifnew!(v,s),Vector{ASCIIString}(),fpfile)::Vector{ASCIIString}
#=	chrlist = ASCIIString[]
	previous = ""
	for item in fpfile
		tmp = split(item)[1]
		if tmp != previous
			push!(chrlist,item)
		end
	end =#
	footprints=Footprint[]
	for chrN in chrlist
		println("Reading $chrN")
		chr=readfa(chrN)
		println("Read $chrN")
		gc()
		append!(footprints,[parsefootprint(s,chr) for s in filter(s->split(s)[1]==chrN,fpfile)])
	end
	footprints
end

export readfootprints
export monocytes                          
export datapath ##TODO: Remove this export, interactive only!



end ##module ReadFasta
