Resultados_hw4.pdf: Tray_45.pdf Tray_varias.pdf Resultados_hw4.tex
	pdflatex Resultados_hw4.tex

datos = RG_45.txt RG_10.txt RG_20.txt RG_30.txt RG_40.txt RG_50.txt RG_60.txt RG_70.txt

Tray_45.pdf Tray_varias.pdf: $(datos)
	python Plots_hw4.py

$(datos): ODE.cpp
	g++ ODE.cpp
	./a.out
