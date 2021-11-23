EXEC = prog     #permet de créer une variable pour pouvoir changer tout rapidement
ARG = -Wall -Wextra -g -lm `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf -lSDL_mixer#Argument pour les erreurs

all : $(EXEC)

$(EXEC) : main.o fonction.o
	
	gcc -o $(EXEC) main.o fonction.o $(ARG)

#$@ permet d'avoir la cible

main.o : main.c
	gcc -o $@ -c main.c $(ARG)

fonction.o : fonction.c
	gcc -o $@ -c fonction.c $(ARG)


clean :				#permet de nettoyer les objet
	rm -rf *.o

mrproper : clean    #permet de nettoyer même l'executable
	rm -rf $(EXEC)

save :
	tar -czvf monsave.tar.gz *

restore :
	ls | grep -v monsave.tar.gz | xargs rm
	tar xzvf monsave.tar.gz
	make save

doc :
	doxygen Doxyfile

bibli :
	sudo apt install libsdl1.2debian libsdl2-dev libsdl-image1.2 libsdl-image1.2-dev libsdl-ttf2.0-0 libsdl-ttf2.0-dev libsdl-mixer1.2 libsdl-mixer1.2-dev
	