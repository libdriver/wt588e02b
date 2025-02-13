### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(wt588e02b REQUIRED)
```

### 3. WT588E02B

#### 3.1 Command Instruction

1. Show wt588e02b chip and driver information.

   ```shell
   wt588e02b (-i | --information)
   ```

2. Show wt588e02b help.

   ```shell
   wt588e02b (-h | --help)
   ```

3. Show wt588e02b pin connections of the current board.

   ```shell
   wt588e02b (-p | --port)
   ```

4. Run wt588e02b play test, index is the voice index.

   ```shell
   wt588e02b (-t play | --test=play) [--index=<index>]
   ```

5. Run wt588e02b update test, index is the voice index, path is the bin file path.

   ```shell
   wt588e02b (-t update | --test=update) [--index=<index>] [--file=<path>]
   ```

6. Run wt588e02b update all test, path is the bin file path.

   ```shell
   wt588e02b (-t update-all | --test=update-all) [--file=<path>]
   ```

7. Run wt588e02b play function, index is the voice index. 

   ```shell
   wt588e02b (-e play | --example=play) [--index=<index>]
   ```
8. Run wt588e02b play list test, number is the list number.

   ```shell
   wt588e02b (-e play-list | --example=play-list) [--list=<number>]
   ```
   
9. Run wt588e02b play loop function, index is the voice index. 

   ```shell
   wt588e02b (-e play-loop | --example=play-loop) [--index=<index>]
   ```
10. Run wt588e02b play loop advance function, index is the voice index. 

       ```shell
       wt588e02b (-e play-loop-advance | --example=play-loop-advance) [--index=<index>]
       ```

11. Run wt588e02b play loop all function. 

       ```shell
       wt588e02b (-e play-loop-all | --example=play-loop-all)
       ```

12. Run wt588e02b stop function. 

       ```shell
       wt588e02b (-e stop | --example=stop)
       ```

13. Run wt588e02b set volume function, volume is the set volume. 

       ```shell
       wt588e02b (-e volume | --example=volume) [--vol=<volume>]
       ```
14. Run wt588e02b update function, index is the voice index, path is the bin file path.

       ```shell
       wt588e02b (-e update | --example=update) [--index=<index>] [--file=<path>]
       ```
15. Run wt588e02b update all function, index is the voice index, path is the bin file path.

       ```shell
       wt588e02b (-e update-all | --example=update-all) [--file=<path>]
       ```

#### 3.2 Command Example

```shell
./wt588e02b -i

wt588e02b: chip is Waytronic Electronic WT588E02B.
wt588e02b: manufacturer is Waytronic Electronic.
wt588e02b: interface is SPI.
wt588e02b: driver version is 1.0.
wt588e02b: min supply voltage is 2.0V.
wt588e02b: max supply voltage is 5.5V.
wt588e02b: max current is 16.00mA.
wt588e02b: max temperature is 85.0C.
wt588e02b: min temperature is -20.0C.
```

```shell
./wt588e02b -p

wt588e02b: SCLK connected to GPIO11(BCM).
wt588e02b: MISO connected to GPIO9(BCM).
wt588e02b: MOSI connected to GPIO10(BCM).
wt588e02b: CS connected to GPIO17(BCM).
```

```shell
./wt588e02b -t play --index=0

wt588e02b: chip is Waytronic Electronic WT588E02B.
wt588e02b: manufacturer is Waytronic Electronic.
wt588e02b: interface is SPI.
wt588e02b: driver version is 1.0.
wt588e02b: min supply voltage is 2.0V.
wt588e02b: max supply voltage is 5.5V.
wt588e02b: max current is 16.00mA.
wt588e02b: max temperature is 85.0C.
wt588e02b: min temperature is -20.0C.
wt588e02b: start play test.
wt588e02b: play test.
wt588e02b: play list test.
wt588e02b: play loop test.
wt588e02b: play loop advance test.
wt588e02b: play loop all test.
wt588e02b: finish play test.
```
```shell
./wt588e02b -t update-all --file=./bin/all.bin

wt588e02b: chip is Waytronic Electronic WT588E02B.
wt588e02b: manufacturer is Waytronic Electronic.
wt588e02b: interface is SPI.
wt588e02b: driver version is 1.0.
wt588e02b: min supply voltage is 2.0V.
wt588e02b: max supply voltage is 5.5V.
wt588e02b: max current is 16.00mA.
wt588e02b: max temperature is 85.0C.
wt588e02b: min temperature is -20.0C.
wt588e02b: start update all test.
wt588e02b: start update all...
wt588e02b: finish update.
wt588e02b: finish update all test.
```

```shell
./wt588e02b -t update --index=7 --file=./bin/single.t3z

wt588e02b: chip is Waytronic Electronic WT588E02B.
wt588e02b: manufacturer is Waytronic Electronic.
wt588e02b: interface is SPI.
wt588e02b: driver version is 1.0.
wt588e02b: min supply voltage is 2.0V.
wt588e02b: max supply voltage is 5.5V.
wt588e02b: max current is 16.00mA.
wt588e02b: max temperature is 85.0C.
wt588e02b: min temperature is -20.0C.
wt588e02b: start update test.
wt588e02b: start update...
wt588e02b: finish update.
wt588e02b: finish update test.
```


```shell
./wt588e02b -e play --index=0

wt588e02b: play index 0.
wt588e02b: play end.
```

```shell
./wt588e02b -e play-list --list=321

wt588e02b: play list 321.
wt588e02b: play list end.
```

```shell
./wt588e02b -e play-loop --index=0

wt588e02b: play loop index 0.
```
```shell
./wt588e02b -e play-loop-advance --index=0

wt588e02b: play loop advance index 0.
```
```shell
./wt588e02b -e play-loop-all

wt588e02b: play loop all.
```
```shell
./wt588e02b -e stop

wt588e02b: stop.
```
```shell
./wt588e02b -e volume --vol=63

wt588e02b: set volume 63.
```
```shell
./wt588e02b -e update --index=0 --file=./bin/single.t3z

wt588e02b: update index 0.
wt588e02b: update end.
```
```shell
./wt588e02b -e update-all --file=./bin/all.bin

wt588e02b: update all.
wt588e02b: update end.
```
```shell
./wt588e02b -h

Usage:
  wt588e02b (-i | --information)
  wt588e02b (-h | --help)
  wt588e02b (-p | --port)
  wt588e02b (-t play | --test=play) [--index=<index>]
  wt588e02b (-t update | --test=update) [--index=<index>] [--file=<path>]
  wt588e02b (-t update-all | --test=update-all) [--file=<path>]
  wt588e02b (-e play | --example=play) [--index=<index>]
  wt588e02b (-e play-list | --example=play-list) [--list=<number>]
  wt588e02b (-e play-loop | --example=play-loop) [--index=<index>]
  wt588e02b (-e play-loop-advance | --example=play-loop-advance) [--index=<index>]
  wt588e02b (-e play-loop-all | --example=play-loop-all)
  wt588e02b (-e stop | --example=stop)
  wt588e02b (-e volume | --example=volume) [--vol=<volume>]
  wt588e02b (-e update | --example=update) [--index=<index>] [--file=<path>]
  wt588e02b (-e update-all | --example=update-all) [--file=<path>]

Options:
  -e <play | play-list | play-loop | play-loop-advance | play-loop-all | stop | volume | update | update-all>,
      --example=<play | play-list | play-loop | play-loop-advance | play-loop-all | stop | volume | update | update-all>
                          Run the driver example.
      --file=<path>       Set the bin file path.([default: update.bin])
  -h, --help              Show the help.
  -i, --information       Show the chip information.
      --index=<index>     Set the index of the voice.([default: 0])
      --list=<number>     Set the list of the voice.([default: 123])
      --vol=<volume>      Set the volume of the voice.([default: 63])
  -p, --port              Display the pin connections of the current board.
  -t <play | update | update-all>, --test=<play | update | update-all>
                          Run the driver test.
```
