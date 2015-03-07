CMP = g++
MAIN = main
FUNC1 = puzzle
FUNC2 = sudokusolver
EXEC = $(MAIN)
FLAGS = 

$(EXEC): $(MAIN).o $(FUNC1).o $(FUNC2).o 
	$(CMP) $(MAIN).o $(FUNC1).o $(FUNC2).o $(FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(FUNC1).h $(FUNC2).h
	$(CMP) -c $(MAIN).cpp

$(FUNC1).o: $(FUNC1).cpp
	$(CMP) -c $(FUNC1).cpp

$(FUNC2).o: $(FUNC2).cpp
	$(CMP) -c $(FUNC2).cpp
clean:
	rm *.o $(EXEC)
