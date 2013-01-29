Rock N' Roll Soul
=================

A mix of platforming and physics based puzzle themed about love and rock and roll.

##Installation

###Linux (Ubuntu)

* Download C++11 compliant compiler. (apt-get install g++ g++-4.7)
* Download scons and SFML. (apt-get install scons libsfml-dev)
  * Note: Must be SFML 1.6. (At the time of writing, libsfml-dev corresponds to 1.6.)
* Run "scons" in root directory of project.
* To play, run "./rocknroll".

###Windows

* An .exe is supplied in the repository, so no need to build it.
* If you want to build it yourself, download Visual Studio Express 2012 and build Project1.sln.

##Controls

* Mouse: Selection in menu
* Left/Right: Walk
* Up/Down: Move aim
* Spacebar (Hold): Charge jump
* Spacebar (Release): Release charge and jump
* R: Restart level
* M/Esc: Quit to main menu

Developed from scratch in 48 hours for Global Game Jam 2013.

##Animation Editing

This game supports simple tiled animations. Animations are defined in two pieces: A sprite sheet (.png) and a file describing it (.anim). Both of these files should reside in the "assets" folder. .anim files are plain text. Open them in a program like notepad or gedit.

The recommended program to create sprite sheets is aseprite: http://www.aseprite.org/

.anim files support the following commands:

* frames numberOfFrames
	* Declares the number of frames in this animation.
* fps framesPerSecond
	* Declares the number of frames per second for the animation.
* sequence sequenceName startIndex sequenceLength
	* Declares an animation within the sprite sheet, which can be referred to in code.
	* startIndex is 0 for the very first frame of animation.
	* sequenceLength declares how long the animation is in number of frames.
* rect rectangleName x y width height
	* Declares a rectangle which can be referred to in code.
* point pointName x y
	* Declares a 2d coordinate with the given name and position.
* string stringName stringValue
	* Declares a string of text which can be referred to in code.
* constant constantName constantNumber
	* Declares a single constant number which can be referred to in code.

All characters in a line after a # symbol are ignored.

Note that some points and rectangles have special meaning in the game for entities or buttons.
I'm not gonna document those just yet because they are subject to change!

##Level Editing

You can add your own levels to the game by putting them in the "level" folder. The .map files are plain text. Open them in a program like notepad or gedit.

Here's a list of commands you can put in the .map files:

* spawnpoint pointName x y
    * Creates a spawn point.
	* If pointName is "start", the player will begin the level at this point.
	* x and y define the position of the spawn point in world space.
* gravity x y
	* Overrides the default gravity used in the level.
	* Use this to make levels underwater or on the moon.
* platform animationName x y
	* Creates a platform which the player can step on.
	* animationName is the name of the animation used. (In "assets" folder.)
	* x and y define the position of the platform in world space.
* goal animationName x y
	* Creates a goal post which is used for the end of a level.
	* animationName is the name of the animation used. (In "assets" folder.)
	* x and y define the position of the goal in world space.
* collectible animationName x y
	* Creates a collectible item, which will be collected by the player on contact.
	* animationName is the name of the animation used. (In "assets" folder.)
	* x and y define the position of the collectible in world space.
* decoration animationName x y
	* Creates a decoration, which serves no purpose other than for aesthetics.
	* animationName is the name of the animation used. (In "assets" folder.)
	* x and y define the position of the decoration in world space.

All characters in a line after a # symbol are ignored.

##Menu Editing

You need to put levels in the level selection menu before being able to access them.
Menus are stored in the "menu" folder. The .menu files are plain text. Open them in a program like notepad or gedit.

Here's a list of commands you can put in the .menu files:

* level levelName levelIcon x y
	* Creates a button which will bring the player to a level.
	* levelName is the name of the .map file in the "level" folder.
	* levelIcon is the name of the animation used for the icon. (In "assets" folder.)
	* x and y define the position of the menu icon.
* decoration animationName x y
	* Creates a decoration, which serves no purpose other than for aesthetics.
	* animationName is the name of the animation used. (In "assets" folder.)
	* x and y define the position of the decoration in world space.

All characters in a line after a # symbol are ignored.


##Credits

Art by Moltanem2000 (Aka Brandon Duncan): [https://github.com/moltanem2000)](https://github.com/moltanem2000)

![Moltanem2000](http://i.imgur.com/fqO73pm.png)

Background music by Gnar Sound. (Aka Lee Gauthier)

![Gnar Sound](http://i.imgur.com/GB9wJUR.jpg)

Programming by Nicolas Guillemot.

![Nicolas Guillemot](http://i.imgur.com/4zTIG44.png)
 
SFML used a cross-platform back-end.

![SFML](http://i.imgur.com/wxjLGs4.png)

Animated sprites made using Aseprite.

![Aseprite](http://i.imgur.com/dmJxYF6.png)
