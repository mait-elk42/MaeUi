all:
	c++ main.cpp -o game -Llib -lraylib -lbox2d -lGL -lm -lpthread -ldl -lrt -lX11 -I include -D PHYSAC_IMPLEMENTATION
	./game