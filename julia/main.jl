include("readfa.jl")

using ReadFasta

function main()
    fps = readfootprints(datapath*monocytes)
    gc()
    while true
        println("Enter an index to print")
        i = parse(Int,readline())
        println(fps[i])
    end
end

main()
