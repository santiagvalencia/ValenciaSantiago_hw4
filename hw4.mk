datosODE = RG_45.txt RG_10.txt RG_20.txt RG_30.txt RG_40.txt RG_50.txt RG_60.txt RG_70.txt
graficasODE = Tray_45.pdf Tray_varias.pdf

datosPDE = final_A.txt final_F.txt final_P.txt inicial.txt intermedio1_A.txt intermedio1_F.txt intermedio1_P.txt intermedio2_A.txt intermedio2_F.txt intermedio2_P.txt promedios.txt
graficasPDE = final_A.pdf final_F.pdf final_P.pdf inicial_A.pdf inicial_F.pdf inicial_P.pdf intermedio1_A.pdf intermedio1_F.pdf intermedio1_P.pdf intermedio2_A.pdf intermedio2_F.pdf intermedio2_P.pdf promedios.pdf

Resultados_hw4.pdf: $(graficasODE) $(graficasPDE) Resultados_hw4.tex
	pdflatex Resultados_hw4.tex

$(graficasODE) $(graficasPDE): $(datosODE) $(datosPDE)
	python Plots_hw4.py

$(datosODE): ODE.cpp
	g++ ODE.cpp
	./a.out

$(datosPDE): PDE.cpp
	g++ PDE.cpp
	./a.out

.PHONY : clean

clean:
	rm -r *.txt
	rm -r *.pdf
	rm -r *.out
	rm -r *.log
	rm -r *.aux
