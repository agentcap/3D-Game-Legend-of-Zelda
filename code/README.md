## Rollnumber - 20161164
## Name - Pradeep Yarlagadda

## Legend of Zelda

### Introduction

- The goal of this game is to obtain the maximum amount of points in the duration of your game.
- You are Link and you operate one of the finest boats in the Great Sea.
- The game can be seen from multiple views controlled by both mouse and keyboards.

### Statistics

- The following values are displayed in the title of the game.
- SCore : Points scored by the user.
- Health : Amount of health available to the user.
- Boost : Amount of Boost available to the user.

### Running the Game

- create a build directory in the main folder.
- go to build and execute the following commands:

`make ..
 make
./graphics_asgn1`

### Controls

#### Basic controls
key 'W arrow' 		--> move front
key 'A arrow' 	--> turn left
key 'D arrow' 	--> turn right
key 'S arrow' 	--> move back
key 'space'			--> jump
key 'f'				--> fire bullets
key 'b'				--> boost

key 'z'				--> Switch control between Link and boat.
key 'o'				--> Switch b/n **orthographic** and **perspective** projection



#### Views and Controls
key 'c'				--> Switch b/n different camera views

##### order:
0 -     Follow-cam view
1 - 	Boat view
2 - 	Top View
3 -		Tower View
4 - 	Helicopter-cam View

### Description
- On colliding with a rock health points decrease by 0.5
- On colliding with a normal monster health points decrease by 1
- On colliding with a boss monster health points decrease by 2
- Gifts of different colors are present on the barrel which help in earning different points.
- Monsters can be killed by shooting them with bullets using cannon.

### Bonus implemented

#### ISLAND:
- Link can mount on the island by pressing the key 'z' only when he is the mounting zone.
- Treasure Implemented.


#### Added sound for various events

- Background music of ocean noice.
- Music for bullets.
- Added music when gifts, boosts are captured.
- Added music when monster boss spawns in the game.
- Added music for jump event of the boat.

#### Various upgrades for ship

- Whenever a boss monster is killed four types of boost may be dropped which are upgrades for the ship : 
1) Booster: increases the speed of the boat when pressed key 'b'.
2) Health Points: Provides the boat with a health point.
3) Score Points 

#### Implemented Different Shades