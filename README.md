# Corewar

This project was completed in July 2019 as part of the 42 school cursus. The goal was to create a programming game very similar to the Core War game created by D. G. Jones and A. K. Dewdney in which two or more battle programs compete for control of a virtual computer ([see wikipedia page here](https://en.wikipedia.org/wiki/Core_War))
Two programs have to be coded: the first is an assembler for an assembly-like language that transforms a set of instructions for the champions (the battle programs) into a binary file. The second program is the corewar program which parses the champions and contains the battle algorithm.

🍌 This project was completed with [Xeska](http://github.com/anaiel/Xeska), anyahyao and abossard.

![path to corewar](https://i.imgur.com/jYQR0kG.png "Inner circle > Algo branch > ft_printf > push_swap > lem-in > corewar")

*Simple virtual machine, simple assembly language, compilation, visualisation*

## Solving the problem

I worked on the corewar program, and the work there was pretty straightforward. It was a matter of attention to detail and patience to make sure the behaviour of the different operations the champions can perform corresponded exactly to that of the reference corewar program (which was provided with the subject). The job was rendered much easier by the fact that there are guides in circulation on how the operations work (although none of them are 100% reliable), therefore there was no need to reverse-engineer the provided reference corewar program (which, in hindsight, might also have taken a bit of the fun out of the project).

The most interesting part of my job was in refactoring the code for the instructions to make sure it was simple, and that all operations, although they work differently, used the same tool functions. I also gave a lot of thought to the fact that each function should only perform one specific action, or, in the case of the battle function, call functions following a specific algorithm. It really helped in keeping function under 25 lines (which is mandated by the norm).

I also added a few options to the corewar executables (all mine but the visualiser) :

```
usage: ./corewar [-visual | [-v verbosity_level] [-dump nbr_cycles]] [-n player_number] champion1.cor ...

*** VERBOSITY LEVEL ***
 1: Live instructions
 2: Display current cycle and cycle to die decrement
 4: Display details of the instrutions
 8: Display carriage deaths
16: Display movement of the PCs (except in case of zjump)
Add the numbers for a combination of verbosity levels
```

### Visualizer (BONUS)

The visualizer program uses the ncurse graphics library. It allows to see the different programs battle each other, follow how many *live* instructions all of them have performed, and so on.

![visualiser](https://i.imgur.com/R3KZAgT.png "Battle between 4 champions")

## Getting Started

Run the command `make` to create the corewar, asm and unassembler executables.

## Examples

```
$> ./asm Anastasia.s
Writing output program to Anastasia.cor
```

```
$> ./corewar Anastasia.cor helltrain.cor
Introducing contestants...
* Player 1, weighing 576 bytes, "Anastasia, The Glorious Banana Maiden" ("Stay away from lazy parasites, who perch on you just to satisfy their needs, they do not come to alleviate your burdens, hence, their mission is to distract, detract and extract, and make you live in abject poverty. ― Michael Bassey Johnson") !
* Player 2, weighing 617 bytes, "helltrain" ("choo-choo, motherf*****s !") !
Contestant 1, "Anastasia, The Glorious Banana Maiden", has won !
```

## Authors

🍌 Team Anas and the bananas:
* **[anaiel](https://github.com/anaiel)** - *Parsing, battle algorithm, refactoring operations, flags*
* **[Xeska](https://github.com/Xeska)** - *Operations, visualizer*
* **anyahyao** - Assembler
* **abossard** - Assembler

<img align="right" src="https://i.imgur.com/FW5Sd6I.png" />
<p align="right">🌟 Outstanding project</p>
