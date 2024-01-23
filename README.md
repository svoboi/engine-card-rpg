# Engine for card RPG games

This engine allows users to upload cards, setup decks and to play with them!

## About

#### Players
There can be however many players, as long, as they have enough cards to play with.
Player can be either AI or human. There isn't any limit on how many players have to be AI or human, so if your heart desires to just watch the computer play by itself, you can do that too!
Players stats for beginning of the game can be customized, each player can have different stats.
We are keeping track of players health, mana, offense and defense. Mana and offense are both refilled after each round.

#### Configuration
In config files, users define their cards and deck setup - how many of each card there are.

#### Cards
Cards can have however many effects from five categories: attack, HP change, defense change, offense change and mana change.
Attack is a special category of effect that first decreases defense and then HP. Effects of card are in two categories: on me and on enemy.
If the player doesn't choose enemy, effects on enemy are also used on player on turn. Card can't be played, if player doesn't have enough points in any of categories that are named in 'Effects on me' part of card.

## Configuration
There are two types of files you can load with this engine - configuration files and save files. Save files have the same content as config files plus information about current situation - player's stats, their cards etc.

In addition to customizing your own cards, you can set whether the players can see each others cards with "cardsVisibility", which can be either 0 for visible cards or 1 for closed game. If you choose 1, the engine adds screen which only says whose turn it will be, so that that player can take over.

## How to run the program
If you have g++ compiler for C++, running command 'make run' in the project folder should start the program.

## How to play
Firstly you need to choose whether you want to start from config file or from save file. Then you need to specify path to the file, e.g. configFiles/settlements.json.
The file doesn't need to have ".json" suffix to load. You can find a few examples in folders "configFiles" and "saveFiles".  
After the game ends, you can choose to play again by putting in y and enter.

### Controls
#### Help
Write h and enter to show possible commands.

#### Play
Card is player with input 'p 0 1' for example. The first number specifies the played card and the second player onto which the enemy effects will apply. Both indexes start on zero.

#### Skip
To skip turn, write s and enter.

#### Throw away
Card is thrown away with 't 0', where the number specifies index of the card being throw away.

#### Save
For saving the game in its current state, any of the players can use 'save folder/file'. Folder must already exist for the saving to be successful.

#### End
You can end the game by using e and enter.

## Credit
Doxyfile for documentation is by David Bernhauer, from his project for subject PA2 at Czech technical university in Prague.
Makefile is a combination of makefiles by David Bernhauer, Tomas Pecka and David Breiner from their seminars also for PA2 at CTU.