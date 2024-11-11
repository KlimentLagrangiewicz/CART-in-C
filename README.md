# CART-in-C
Naive implementation of CART (Classification And Regression Tree) algorithm in C (standard C89/C90) for data classification

## Example of usage
Cloning project and changing current directory:
```
git clone https://github.com/KlimentLagrangiewicz/CART-in-C
cd CART-in-C
```
Building from source (Linux):
```
make
```
Building from source (Windows):
```
make windows
```
If building was successfully, you can find executable file in `bin` subdirectory.  
Run the program:
```
./bin/CART-in-C 9 4 150 ./datasets/iris/iris9.txt ./datasets/iris/test150.txt ./datasets/iris/result.txt ./datasets/iris/ideal150.txt 
```