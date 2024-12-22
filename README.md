# aoc-2024


Case 1: 
C N X ...
* can only get rid of C or N (current or next)
* need to check if (C, X) satisfies invariants
* need to check if (N, X) satisfies invariants
* if successful, pick first one that works

Case 2:
... X C N Y ...
* still can only get rid of C or N (current or next)
* need to check if (X, C) and (C, Y) satisfy invariants
* need to check if (X, N) and (N, Y) satisfy invariants
* if successful, pick first one that works 

 
Case 3: 
... X C N
* can only get rid of C or N (current or next)
* need to check if (X, N) satisfies invariants
* need to check if (X, C) satisfies invariants
* if successful, pick first one that works

Pseudocode
```
if case 1:
    find next+1
    if check_invariants(


```