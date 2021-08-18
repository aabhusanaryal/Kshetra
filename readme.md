# Kshetra

#### A Vector field plotter.

## Abstract

Kshetra is a project done as a mini project for Object Oriented Programming [CT501], a course offered by the Institute of Engineering, Tribhuvan University. It helped us apply the concepts of OOP and realise the potential of Object Oriented Design in a full blown application.
Kshetra is a 2D vector field plotter, which means that it basically takes in a vector valued function and plots vectors (arrows) at different coordinates of a graph. Some applications that solve the same problem are GeoGebra and Desmos. Kshetra differs from the mentioned applications in that it is a native app (built with C++) and not a web app (built with JavaScript) which inherently gives it a higher ground in terms of performance.
Vector fields are used to model numerous real life problems, which include fluid flow (like the flow of water in a river) and other fields like Gravitational and Electric fields to name a few. Hence a tool that helps in visualising such fields is certainly very handy.

## Build Instructions

You may simply run the application by downloading the latest release [here](https://github.com/aabhusanaryal/Kshetra/releases). If, for some reason, you want to build the project on your own; read [this](https://www.sfml-dev.org/download/sfml/2.5.1/) guide on setting up SFML for your compiler. For this instructions, we'll be using GCC 7.3.0 and hence will download the [GCC 7.3.0 MinGW (SEH) - 64-bit](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip) zip file from the aforementioned site.

Then, create a folder named `src_SFML` (case matters) on the parent directory of Kshetra. Then, paste the `lib` and `include` folder from the downloaded zip onto this newly created folder.

Now, copy the contents of the bin folder (contains some .dll files) from the downloaded zip to the parent directory of Kshetra.

Finally, create another directory named `build_gcc` on the parent directory of Kshetra.

Now, run the following commands to build the project:

```bash
$ g++ -Isrc/include -Isrc_SFML/include -c -g -O2 ./src/*.cpp
```

```bash
$ g++ *.o -Lsrc_SFML/lib -lsfml-graphics -lsfml-window -lsfml-system ./assets/icon.res -Wl,--subsystem,windows -mwindows -o ./build_gcc/Kshetra.exe
```

This should build the application and place it on the `build_gcc` folder. You can now run the application by running the following command:

```bash
./build_gcc/Kshetra.exe
```

## Screenshots

**1. Main Menu**
![](https://i.imgur.com/QRfB6eS.png)

**2. One of the Common Functions**
![](https://i.imgur.com/FWnRLtc.png)

**3. Simulation of Interaction of Charges [Easter Egg]**
![](https://media.discordapp.net/attachments/862246526021926925/877489405303095296/interaction_of_charges.gif?width=1216&height=675)

**4. Plotting Custom Functions**
![](https://i.imgur.com/GxRYnRm.png)

## Attributions
Icon By [Luc Chaffard](https://iconscout.com/contributors/luc-chaffard) on [Iconscout](https://iconscout.com/)

## External libraries used

[SFML](https://www.sfml-dev.org/) is distributed under the [zlib/png license](https://opensource.org/licenses/Zlib)

## License

[MIT License](https://opensource.org/licenses/MIT)
