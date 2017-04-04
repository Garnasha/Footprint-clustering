.PHONY: clean all

FLAGS = --number-sections -H inheader.tex --top-level-division=chapter 
COMPONENTFILES = metadata.yaml macros.md acks.md \
		intro.md rq.md background2.md dataset.md model.md formal_rq.md \
		mst-alg.md results.md discussion.md conclusion.md 

all: composed.pdf composed.tex composed.odt # composed.docx

clean:
	rm composed.*

direct.pdf: rq.md background2.md model.md formal_rq.md dataset.md \
	metadata.yaml abstract.yaml acks.md mst-alg.md results.md discussion.md \
	conclusion.md macros.md Makefile
	pandoc macros.md metadata.yaml acks.md \
		intro.md rq.md background2.md dataset.md model.md formal_rq.md \
		mst-alg.md results.md discussion.md conclusion.md \
		--latex-engine=xelatex -o direct.pdf \
		$(FLAGS)

direct.tex: rq.md background2.md model.md formal_rq.md dataset.md \
	metadata.yaml abstract.yaml acks.md mst-alg.md results.md discussion.md \
	conclusion.md macros.md
	pandoc macros.md metadata.yaml acks.md \
		intro.md rq.md background2.md dataset.md model.md formal_rq.md \
		mst-alg.md results.md discussion.md conclusion.md \
		--latex-engine=xelatex -o direct.tex \
		$(FLAGS)

composed.md: rq.md background2.md model.md formal_rq.md dataset.md \
	metadata.yaml abstract.yaml acks.md mst-alg.md results.md discussion.md \
	conclusion.md macros.md
	pandoc macros.md metadata.yaml acks.md \
		intro.md rq.md background2.md dataset.md model.md formal_rq.md \
		mst-alg.md results.md discussion.md conclusion.md \
		-R -o composed.md \
		$(FLAGS)

composed.pdf: $(COMPONENTFILES) Makefile inheader.tex
	pandoc $(COMPONENTFILES) --latex-engine=xelatex -o composed.pdf $(FLAGS)

composed.tex: $(COMPONENTFILES)
	pandoc $(COMPONENTFILES) -s --latex-engine=xelatex -o composed.tex $(FLAGS)

composed.odt: $(COMPONENTFILES)
	pandoc $(COMPONENTFILES) -o composed.odt $(FLAGS)

composed.docx: $(COMPONENTFILES)
	pandoc $(COMPONENTFILES) -o composed.docx $(FLAGS)

