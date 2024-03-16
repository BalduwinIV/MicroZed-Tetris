# Tetris

Game remake, adapted for MicroZed Evaluation Kit.

## Getting started

![menu_screen](https://github.com/BalduwinIV/MicroZed-Tetris/assets/42943996/549d1101-773a-40df-96b6-73987d90b9b0)

When you start the program, you'll see a menu that enables you to start a new game,
change game speed, turn the audio or showing next block on/off or exit the program.
Switching between those options is possible by turning the green rotary knob and
choosing the option - by pressing
it. You can change the falling block
speed by choosing this option on
the menu and turning the blue
knob (you’ll see a part of LED line
lighting according to the speed you
chose). When you turn on/off
showing next block, the color of the
left RGB-led is going to change
(turns red when you turn it off and
green when you turn it off). Same
logic with turning the audio on/off
(but with the right RGB-led).

## Game

![game_screen_update](https://github.com/BalduwinIV/MicroZed-Tetris/assets/42943996/4bf70162-bdad-4cf1-8cbe-48ee594a6f2e)

On the screen you will see several areas. In the central area the game itself will be
displayed. The left one will show the amount of blocks you placed sorted by type.
Types are distinguished by the
shape of the block and have
different colors. On the right there
are three changeable areas and
one permanent one at the bottom
with the Tetris logo. Among the
changeable areas the top one
shows your current score and the
best score out of the ones
achieved earlier. The middle one
shows the next block that will fall
down. The bottom area displays
the amount of lines destroyed
throughout the game.

Blocks will be falling with the speed you chose on the starting menu. Every block may
be rotated (by turning the red knob) and moved to the left/right (by turning the blue
knob) if there is enough space for that. It is possible to make a block fall quicker (soft
drop) by pressing and holding the blue knob or make it fall instantly by pressing the
red knob.
Whenever the line is destroyed, you'll see an animation on LED line and a similar
animation on the game field when the line is erased.
You’ll get points every time the line is destroyed according to their amount and your
current speed. The speed of the blocks is changed when the score reaches the trigger
(which is doubled every time it happens.

## Pause

![pause_screen](https://github.com/BalduwinIV/MicroZed-Tetris/assets/42943996/e66b2565-27d6-4e5c-8604-ba047018d2cd)

At any moment of the game, you may
open a menu that’ll show you options
such as continue the game, turn the
audio off/on, change audio volume or go
back to menu. Switching between
options is possible by turning the green
knob and changing volume – by turning
the blue knob. Pressing the green knob
means choosing the corresponding
option.

## Game over

![gameover_screen](https://github.com/BalduwinIV/MicroZed-Tetris/assets/42943996/09a9dc86-105d-40a7-b37a-411e95277f19)

Whenever some block reaches the top of the game field and you can no longer move
it anywhere, the game field will
gradually turn white and animation on
the LED line. After that game statistics
(such as amount of fallen blocks of each
type, lines destroyed and your score)
and option to go back to menu will be
displayed (you have to press the red
knob to do so). If your score exceeded
the previous highest score, best score
will be updated. After that you’ll see the
starting menu and may play the game
again.
