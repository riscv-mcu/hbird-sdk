# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = build
DOXYDIR       = $(BUILDDIR)/html/design/doxygen

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

all: doxygen_core
	make html

clean_xml:
	rm -rf $(DOXYDIR)/core/xml/
	rm -rf $(DOXYDIR)/core/def/

doxygen_core:
	mkdir -p $(DOXYDIR)
	cd source/doxygen && doxygen nmsis_core.dxy

firefox:
	firefox build/html/index.html

firefox_pdf:
	firefox build/latex/*.pdf
