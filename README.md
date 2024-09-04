# large_additions_in_c
* An approach to add numbers of undefined length in C
* Digits above 100k take 30 seconds to process in vscode but in cmd, it runs well.
* But digits above 1M take 10 seconds in cmd as well.
* Apart from the time it takes to allocate the values, the sum is calculated quickly.

# Problem in this approach
* The frequent reallocation is bad, because it requires frequent movement of data, and that's why the allocation of values takes time.
