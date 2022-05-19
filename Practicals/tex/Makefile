NAMES= compiling_batch  good_practice  openmp_instructions
SRCS =	$(addsuffix .tex, $(NAMES))

BUILT =	$(addsuffix .pdf, $(NAMES))

TEX = pdflatex

all: $(BUILT)

remake: clean all

clean:
	rm -f $(BUILT)
	rm -f $(addsuffix .aux, $(NAMES)) $(addsuffix .log, $(NAMES)) $(addsuffix .toc, $(NAMES))

install: all
	cp compiling_batch.pdf ../prac1/notes/task_2_compiling_batch
	mv compiling_batch.pdf ../prac2/notes/
	mv good_practice.pdf ../prac2/notes/
	mv openmp_instructions.pdf ../prac4/notes/

%.pdf: %.tex
	$(TEX) -interaction batchmode $<
	$(TEX) -interaction batchmode $<
	$(TEX) -interaction batchmode $<
