## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Ressources](#Ressources)
* [Saved view of a maze ](#Saved-view-of-a-maze)

## General info
CUB3D is a 42-networking project, inspired by the world-famous eponymous 90’s game, Wolfenstein 3D, which was the first FPS ever. The aim of this project is to create a dynamic view inside a maze, in which the player will have to find his way.
CUB3D is a great opportunity to explore ray-casting technology, and to improve the skills in these areas: windows, colors, events, fill shapes, etc.

## Technologies
Project is created with:
* C language
* MiniLibX library
	
## Setup
* To run this project for macOS:

```
$ cd ../Cub3D
$ make
$ ./cub3D map.cub
```

* To generate a map:

```
$ ./Cub3D_map_generator 'number of rows' 'number of column' 
```

* To save a screenshot

```
$ ./cub3D map.cub --save
```

## Ressources
* [Wolfenstein 3D game](http://users.atw.hu/wolf3d/)
* [Lode's Computer Graphics Tutorial Raycasting](https://lodev.org/cgtutor/raycasting.html)
* [Introduction to Raycasting Theory with JavaScript](https://courses.pikuma.com/courses/raycasting)
* [Ray-Casting Tutorial For Game Development And Other Purposes](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
* [Bits to Bitmaps: A simple walkthrough of BMP Image Format](https://medium.com/sysf/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393)

## Saved view of a maze 
<img src="https://github.com/NAB-khaoula/Cub3D/blob/master/save.bmp" />
