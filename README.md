# a-star-algorithm
A* algorithm sliding game solver. Includes A* search and depth first branch and bound search with different heuristic options.

Output:
---
```
Start state: 1 3 4 8 6 2 7 0 5 
End state: 1 2 3 8 0 4 7 6 5 

(Move made) (G value + H value) (Open lists) (Closed lists) [Board state]
(RIGHT) (1 + 8) (OPEN LIST 1) (CLOSED LIST 1) [ 1 3 4 8 6 2 7 5 0 ]
(LEFT) (1 + 8) (OPEN LIST 2) (CLOSED LIST 1) [ 1 3 4 8 6 2 0 7 5 ]
(UP) (1 + 4) (OPEN LIST 3) (CLOSED LIST 1) [ 1 3 4 8 0 2 7 6 5 ]
(RIGHT) (2 + 4) (OPEN LIST 3) (CLOSED LIST 2) [ 1 3 4 8 2 0 7 6 5 ]
(DOWN) (2 + 6) (OPEN LIST 4) (CLOSED LIST 2) [ 1 3 4 8 6 2 7 0 5 ]
(LEFT) (2 + 6) (OPEN LIST 5) (CLOSED LIST 2) [ 1 3 4 0 8 2 7 6 5 ]
(UP) (2 + 6) (OPEN LIST 6) (CLOSED LIST 2) [ 1 0 4 8 3 2 7 6 5 ]
(DOWN) (3 + 6) (OPEN LIST 6) (CLOSED LIST 3) [ 1 3 4 8 2 5 7 6 0 ]
(LEFT) (3 + 4) (OPEN LIST 7) (CLOSED LIST 3) [ 1 3 4 8 0 2 7 6 5 ]
(UP) (3 + 4) (OPEN LIST 8) (CLOSED LIST 3) [ 1 3 0 8 2 4 7 6 5 ]
(DOWN) (4 + 4) (OPEN LIST 8) (CLOSED LIST 4) [ 1 3 4 8 2 0 7 6 5 ]
(LEFT) (4 + 2) (OPEN LIST 9) (CLOSED LIST 4) [ 1 0 3 8 2 4 7 6 5 ]
(RIGHT) (5 + 4) (OPEN LIST 9) (CLOSED LIST 5) [ 1 3 0 8 2 4 7 6 5 ]

(DOWN) (5 + 0) (OPEN LIST 10) (CLOSED LIST 5) [ 1 2 3 8 0 4 7 6 5 ]
^ WINNER

(LEFT) (5 + 4) (OPEN LIST 11) (CLOSED LIST 5) [ 0 1 3 8 2 4 7 6 5 ]
(RIGHT) (6 + 2) (OPEN LIST 11) (CLOSED LIST 6) [ 1 2 3 8 4 0 7 6 5 ]
(DOWN) (6 + 2) (OPEN LIST 12) (CLOSED LIST 6) [ 1 2 3 8 6 4 7 0 5 ]
(LEFT) (6 + 2) (OPEN LIST 13) (CLOSED LIST 6) [ 1 2 3 0 8 4 7 6 5 ]
(UP) (6 + 2) (OPEN LIST 14) (CLOSED LIST 6) [ 1 0 3 8 2 4 7 6 5 ]

# Nodes: 6
Time: 0.000539 seconds
```
