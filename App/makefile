OBJ = main.o sound.o screen.o comm.o
APPNAME = wave.a

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lm -lcurl

%.o : %.c
	gcc -c -o $@ $< -std=c99

clean :
	rm $(OBJ) $(APPNAME) *.tar *.wav

archive :
	tar cf sound.tar *.c *.h makefile

send :
	scp sound.tar huypham060398@gmail.com:.

git :
	git add *.c
	git commit -m "Added C source code"
	git add *.h
	git commit -m "Added C header file"
#	git add makefile
#	git commit -m "Added makefile"
