a.out: main.o CursorMovement.o DLL_Operations.o Enter_Backspace.o cut.o copy.o paste.o Undo.o Redo.o
	gcc -o a.out main.c CursorMovement.c DLL_Operations.c Enter_Backspace.c cut.c copy.c paste.c Undo.c Redo.c
main.o: main.c
	gcc -c main.c
CursorMovement.o: CursorMovement.c
	gcc -c CursorMovement.c
DLL_Operations.o: DLL_Operations.c
	gcc -c DLL_Operations.c
Enter_Backspace.o: Enter_Backspace.c
	gcc -c Enter_Backspace.c
cut.o: cut.c
	gcc -c cut.c
copy.o: copy.c
	gcc -c copy.c
paste.o: paste.c
	gcc -c paste.c
Undo.o: Undo.c
	gcc -c Undo.c
Redo.o: Redo.c
	gcc -c Redo.c
clean:
	rm -f a.out main.o CursorMovement.o DLL_Operations.o Enter_Backspace.o cut.o copy.o paste.o Undo.o Redo.o