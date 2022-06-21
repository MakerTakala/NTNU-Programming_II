all: setup
	doxygen -g
	doxygen Doxyfile
	cd latex && make && mv refman.pdf ../

setup:
	@echo "Download Doxygen..."
	sudo apt-get install doxygen
	@echo "Download texlive-latex-base..."
	sudo apt-get install texlive-latex-base
	@echo "Download texlive-latex-extra..."
	sudo apt-get install texlive-latex-extra