## Details

- Category: MISC
- Author:   yuma

## Description

The challenge is a dungeon crawler RPG. 
The goal is to defeat the boss at the end to receive the flag. The problem is that by using the game mechanics, the boss can't be defeated.


## Solution

There is one room that allows to downgrade the damage of your character. 
As the damage is an unsigned int, if you hit the wall in the one room often enough, your damage underflows and you easily defeat everyone.

Tasks:
1. Go Straight
2. Go Left
3. Go Straight
4. Go Left
5. Hit Wall until your damage underflows
6. Go Right
7. Go Right
8. Go Straight
9. Go Left.
10. Go Straight
11. Go Right
12. Defeat Boss -> Flag