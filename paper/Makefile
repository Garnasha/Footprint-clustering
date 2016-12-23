
FLAGS =  # --top-level-division=chapter

composed.pdf: rq.md background2.md model.md formal_rq.md dataset.md \
	metadata.yaml abstract.yaml acks.md mst-alg.md results.md discussion.md \
	conclusion.md
	pandoc acks.md \
		intro.md rq.md background2.md dataset.md model.md formal_rq.md \
		mst-alg.md results.md discussion.md conclusion.md \
		metadata.yaml --latex-engine=xelatex -o composed.pdf \
		$(FLAGS)

composed.tex: rq.md background2.md model.md formal_rq.md dataset.md \
	metadata.yaml abstract.yaml acks.md mst-alg.md results.md discussion.md \
	conclusion.md
	pandoc acks.md \
		intro.md rq.md background2.md dataset.md model.md formal_rq.md \
		mst-alg.md results.md discussion.md conclusion.md \
		metadata.yaml abstract.yaml \
		-st latex --latex-engine=xelatex -o composed.tex $(FLAGS)
