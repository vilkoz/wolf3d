# wolf3d
Game on raycasting engine
## dependencies
for minilibx 
* git
* libx11-dev
* libxext-dev
* build-essential

for openmp on macos
* gcc or clang-omp
## compiling
```
make
```
## execution
```
./wolf3d map_file
```
res/zombies.map - medium difficulty map, res/LClvl2.map - hard map
## screenshots
![zombie](http://imgur.com/5cir8hwl.png)
![dead zombie](http://imgur.com/jqC6WOyl.png)
![pause screen](http://imgur.com/8ES8Ojul.png)
![win screen](http://imgur.com/pVbPUIgl.png)
## map format
map should be rectangular

you can choose texture by simply changing number

example:
```
1111111111111111111
1      12345678   1
1                 1
1   P             1
1                 1
1                 1
1      12345678   1
1111111118111111111
```
![textures example](http://imgur.com/5GCmKWMl.png)

other symbols definition

|'a'| 'b'| 'd'| 'D' | 'z'| 'h' | 's'|
|---|---|---|---|---|---|---|
|block sprite |sprite |door horisontal |door vertical |zombie |potion |ammo |
|<img src="http://imgur.com/0AXuJTcl.png" alt="pillar" width="auto" height="200">|<img src="http://imgur.com/oZqxroMl.png" alt="green light" width="auto" height="200">| <img src="http://imgur.com/g1tJMZZl.png" alt="door horisontal" width="auto" height="200">|<img src="http://imgur.com/g1tJMZZl.png" alt="door vertical" width="auto" height="200">|<img src="http://imgur.com/nRX3mo8l.png" alt="zombie" width="auto" height="200">| (see in game) |(see in game) |
