clear
echo "Compiling..."
g++ -c Timber.cpp
echo "Linking..."
g++ Timber.o -o out/timber -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
rm Timber.o
echo "Executing..."
./out/timber
echo "Program exited"