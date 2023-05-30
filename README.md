# Hanoip Charge Control
This script can be used to set charging current for hanoip device.

## Usage :
1. Open Root Shell using some Terminal app.
2. Copy `charger.sh` to somewhere in `/data` to be able to get execute permission.
3. Make it an executable using `chmod +x charger.sh`
4. Use it like `./charger.sh <level>`, here level is number from 0-8

## Level -> Current
```
0 -> 3600 mA
1 -> 3000 mA
2 -> 2500 mA
3 -> 2000 mA
4 -> 1500 mA
5 -> 1200 mA
6 ->  900 mA
7 ->  700 mA
8 ->  500 mA
```
