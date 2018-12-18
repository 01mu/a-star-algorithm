# a-star-algorithm
A* algorithm sliding game solver. Includes A* search and depth first branch and bound search with different heuristic options.
## Usage
### Out of place heuristic
```
Start state:
1 3 4
8 6 2
7 0 5

End state:
1 2 3
8 0 4
7 6 5

Finding path using Out of place heuristic...

Moves:
Up:
1 3 4
8 0 2
7 6 5

Up:
1 0 4
8 3 2
7 6 5

Down:
1 3 4
8 0 2
7 6 5

Up:
1 0 4
8 3 2
7 6 5

Up:
1 3 0
8 2 4
7 6 5

Left:
1 0 3
8 2 4
7 6 5

Down:
1 2 3
8 0 4
7 6 5

Move count: 7
```
## Manhattan heuristic
```
Start state:
1 3 4
8 6 2
7 0 5

End state:
1 2 3
8 0 4
7 6 5

Finding path using Manhattan heuristic...

Moves:
Up:
1 3 4
8 0 2
7 6 5

Right:
1 3 4
8 2 0
7 6 5

Up:
1 3 0
8 2 4
7 6 5

Left:
1 0 3
8 2 4
7 6 5

Down:
1 2 3
8 0 4
7 6 5

Move count: 5
```
