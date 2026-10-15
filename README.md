# Scoundrel

A single-player roguelite card game played with nothing but a deck of cards, based on the solitaire game **Scoundrel**. Fight monsters, grab weapons, drink potions and try to survive until the deck runs out.

Written in **C++** with **SFML 3**. All artwork (cards, backgrounds, character portraits) is **AI-generated**.

<!-- Add a screenshot or GIF here, e.g. ![Gameplay](docs/gameplay.png) -->

## Table of contents

- [Features](#features)
- [How to play](#how-to-play)
- [Game modes](#game-modes)
- [The deck](#the-deck)
- [Controls](#controls)
- [Settings](#settings)
- [Getting started](#getting-started)
- [Project structure](#project-structure)
- [Project status](#project-status)
- [Credits](#credits)

## Features

- A full Scoundrel deck turned into a dungeon: monsters, weapons, healing potions and (optionally) merchants.
- Three game modes: **Classic**, **+Merchant** and **+two Merchants**.
- Fully mouse-driven interface with hover effects.
- Dark-fantasy, AI-generated artwork for the cards, backgrounds and player portraits.
- Random player portrait every run.
- Adjustable resolution (640x360 up to 1920x1080) and windowed or fullscreen mode.
- A randomly chosen, rather silly window title on every launch.

## How to play

You start with **20 HP**. The dungeon is a shuffled deck, and you face it **a room at a time**: each room is four face-up cards.

**Your goal is to get through the entire deck without your HP reaching 0.** When you do, your remaining HP is your score.

### Playing a room

1. Click **three of the four cards** in the room to play them, in any order.
2. The fourth card stays on the table and becomes part of the next room. Three new cards are dealt next to it.
3. Repeat until the deck is empty and every card in the last room has been played.

### What each card does

| Suit | Cards | Type | Effect when played |
|------|-------|------|--------------------|
| Spades and Clubs | 2 to 14 (J = 11, Q = 12, K = 13, A = 14) | **Monster** | You take damage equal to its value, unless your weapon helps (see below). |
| Diamonds | 2 to 10 | **Weapon** | Equip it. It replaces any weapon you already carry. |
| Hearts | 2 to 10 | **Healing potion** | Restores HP equal to its value, up to your maximum of 20. |

### Weapons

A weapon reduces the damage you take from a monster by its value (to a minimum of 0 damage), but it dulls as you use it:

- Right after you equip a weapon, it can fight any monster.
- Each time you beat a monster with it, the weapon can afterwards only be used on **strictly weaker** monsters. The side panel shows this limit as **BUFFER**.
- If a monster is as strong or stronger than the weapon's limit, or you have no weapon, you take the monster's **full value** as damage.

For example, with a Diamond 5 equipped you would take 3 damage from a monster of value 8 (8 - 5), and from then on the weapon only works on monsters 7 or lower.

### Healing

Only **one healing potion per room** has any effect. A second Heart in the same room is used up and gives you nothing, so choose carefully which cards to play.

### Avoiding a room

If the room looks bad, you can **avoid it** with one of the three arrow buttons around the table. The four cards go to the bottom of the deck and four fresh cards are dealt. There are limits:

- You can't avoid two rooms in a row.
- You can't avoid a room once you have already played a card from it.
- You can't avoid the last room, once the deck is empty.

Two of the arrows put the skipped cards back in the same order, while the third reverses their order.

### Merchants

In the merchant modes, one or two **Jack** cards (shown with Jack of Hearts and Jack of Diamonds art) are shuffled into the deck. Playing one **sells your current weapon**: you heal for the lower of the weapon's value and its current BUFFER, and then you are left without a weapon.

### Winning and losing

- **You lose** the moment your HP drops to 0.
- **You win** when the deck is empty and you have played every card in the final room, with HP above 0.

## Game modes

Pick a mode from the main menu:

| Mode | Deck size | Merchants |
|------|-----------|-----------|
| **Play Classic** | 44 cards | None |
| **Play +Merchant** | 45 cards | 1 |
| **Play +two Merchants** | 46 cards | 2 |

## The deck

The classic 44-card Scoundrel deck is made from a standard deck:

- 26 monsters: Spades and Clubs, 2 to Ace
- 9 weapons: Diamonds, 2 to 10
- 9 healing potions: Hearts, 2 to 10

The jokers, the red face cards and the red aces are removed. The merchant modes add the Jacks on top.

## Controls

Everything is played with the mouse.

| Action | Input |
|--------|-------|
| Play a card | Left-click it |
| Avoid the room | Click one of the three arrow buttons |
| Menu selection | Click an entry (it turns green when hovered) |
| Continue from the win or lose screen | Left-click or `Space` |

**Easter egg:** pressing `B` during a run heals you for 1 HP. It is a cheat, and the game's window titles joke about it.

## Settings

Settings are read at startup from `Projektc/settings.txt`:

```
CardMotive:
classic
Resolution:
1920
1080
Fullscreen:
windowed
Username:
Player
TimeLimit:
0
```

| Setting | Values |
|---------|--------|
| `Resolution` | Width then height on separate lines. Supported range is 640x360 to 1920x1080. Keep a 16:9 ratio, because everything is scaled from the width. |
| `Fullscreen` | `windowed` or `fullscreen` |
| `CardMotive` | `classic` (the only card set currently included) |
| `Username` | Your display name |

## Getting started

### Requirements

- Windows (x64)
- Visual Studio 2022 (toolset v143) with the C++ desktop workload
- C++20

SFML 3 headers and libraries are already included in the repository (`include/` and `lib/`), so there is nothing else to install.

### Build and run

1. Clone the repository:
   ```bash
   git clone https://github.com/AmberWillowLuna/Scoundrel_Orginal_Project.git
   ```
2. Open `Projektc.sln` in Visual Studio.
3. Select the **x64** platform and the **Debug** or **Release** configuration.
4. Build and run (`F5`).

> **Important:** the game loads its images and fonts through relative paths (`Cards/`, `Backgrounds/`, `Fonts/`, `Icons/`, `settings.txt`), so it must run with `Projektc/` as the working directory. Visual Studio does this by default. If you launch the `.exe` yourself, start it from inside `Projektc/`, for example:
>
> ```
> cd Projektc
> ..\x64\Debug\Projektc.exe
> ```
>
> The SFML DLLs must sit next to the executable (they are already in `x64/Debug/`).

## Project structure

```
Scoundrel_Orginal_Project/
├── Projektc.sln
├── include/SFML/            # SFML 3 headers
├── lib/                     # SFML 3 and dependency libraries
├── x64/                     # Build output and SFML DLLs
└── Projektc/
    ├── Projektc.cpp         # Entry point: reads settings, creates the window
    ├── Handler.cpp/.h       # Main menu and game start
    ├── Dungeon.cpp/.h       # The run itself: rooms, input, win/lose screens
    ├── Night.cpp/.h         # Room helpers: hover, card clicks, avoiding a room, shuffling
    ├── Card.h               # Card classes: Monster, Weapon, Healing, Merchant
    ├── PrepCard.cpp/.h      # Builds the deck for each game mode
    ├── Player.h             # Player stats and the stats panel text
    ├── settings.txt         # Resolution, window mode and other settings
    ├── Cards/classic/       # Card artwork
    ├── Backgrounds/         # Menu, night and other backgrounds
    ├── Icons/               # Player portraits
    ├── Boosters/            # Booster artwork (not used yet)
    ├── Fonts/               # Main.ttf and Secondary.ttf
    └── Saves/               # Save slot and graveyard data (not used yet)
```

## Project status

The playable game in this repository is the **card-room game** described above: Classic, +Merchant and +two Merchants.

The repository also contains artwork and data for a planned **campaign layer** that the current source code does not use yet:

- Day-phase backgrounds with a trader and a sailor
- Booster cards (Adrenaline, Pure Liquid, Short Sword, The Fool, Wheel of Fortune)
- Elemental card art (air, lava, water, earth) and joker cards
- Save slots, gold and a graveyard of fallen players
- A time-limit setting (parsed from `settings.txt` but not used yet)

## Credits

- **Scoundrel** is a solitaire card game designed by Zach Gage and Kurt Bieg. This project is an unofficial fan implementation.
- All artwork was generated with AI.
- Built with [SFML](https://www.sfml-dev.org/).
