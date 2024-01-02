# Entities and Projectiles with Delta

Written in C, this program aims to provide a user with a text-based simulation to determine whose projectile will make contact first with a given set of parameters.

## Why?

I enjoy [Star Citizen](https://robertsspaceindustries.com/star-citizen) player versus player combat, which involves six degrees of freedom. An 
[Avenger Squadron](https://robertsspaceindustries.com/orgs/AVSQN) ace, and engineer, MarkyMark (markymark2145) posited that "as long as the
delta stays the same, the shots hit at the same time," and that "shots taken at the same time at any velocity going any direction will
result in the shots hitting at the same time, unless the shots are going slower [sic] enough that they would never hit each other,"
adding on, "as long as velocity is constant."

This program **proves** this hypothesis, though, as with any experiment or simulation of reality (or in this case, a game world), **real**
testing should be performed, and thus independent verification is necessary.

At the end of the day, however, this is simply fun, simple mathematics for entertainment value. One should acknowledge that results may greatly
vary. Given the lack of overall robustness in this program, I can imagine one might produce *interesting* output(s) with it.

## Features

1. Projectiles inherit the **initial** velocity of the parent entity.
2. "Step-by-step" display; information at every time interval.
3. Easy-to-use command-line interface via paramatization.

## Usage

**Windows**

1. Download or compile the executable.
2. Open a command prompt and change directory to where the executable is located.
3. Run the executable `executable-name-here.exe`, ensuring the appropriate parameters are present.

**Linux**

1. Compile the binary.
2. Open a terminal and change directory to where the binary is located.
3. Run the binary `./binary-name-here`, ensuring the appropriate parameters are present.

## Parameters

**All parameters must have a value entered for program execution.**

* Left-side entity.
	* `-lev` - Left entity velocity (integer).
	* `-lea` - Left entity acceleration (integer).
	* `-les` - Left entity starting position (integer).
	* `-lpv` - Left projectile velocity (integer).
* Right-side entity.
	* `-rev` - Right entity velocity (integer).
	* `-rea` - Right entity acceleration (integer).
	* `-res` - Right entity starting position (integer).
	* `-rpv` - Right projectile velocity (integer).

As the simulation plane is 2D, **negative values** move entities and projectiles **to the left**.

## Example

**Windows**

`C:\path\to\executable> executable-name-here.exe -lev 1 -lea 0 -les 0 -lpv 10 -rev 2 -rea 0 -res 10 -rpv -10`.

**Linux**

`/path/to/binary$ ./binary-name-here -lev 1 -lea 0 -les 0 -lpv 10 -rev 2 -rea 0 -res 10 -rpv -10`.

## Contributions

As this is a one-off program, unintended for serious usage, it is best for one to fork the repository to make changes as necessary.
The only planned updates are to fix mathematical discrepancies, if such are found.

## The MIT License (MIT)

Copyright © 2024 - ReeceDeveloper

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
