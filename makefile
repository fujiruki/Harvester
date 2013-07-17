# gccとmakeが入っている環境で使えるmakefileです。
# 「make」というコマンドが入っていれば使えます。
# make     ---> コンパイル
# make run ---> コンパイルして実行

OUTNAME = game.o

$(OUTNAME) : main.o emu.o
	gcc emu.o main.o -o $(OUTNAME) -lglut -lGLU -lGL -lm -lpthread -Wall

main.o : main.h main.c
	gcc main.c -c

emu.o : emu.h emu.c
	gcc emu.c -c

run : $(OUTNAME)
	./game.o
