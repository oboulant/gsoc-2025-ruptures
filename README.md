# gsoc-2025-ruptures
Test for gsoc 2025 for ruptures

## Run evenrything (easy, medium and hard tests)

```zsh
./run_rscript.zsh 
```

## Files and explanations

`getsumcum.cpp` and `use-getcumsum.R` are just the standalone files for the easy test. 

Then, `getcumsum-cost.cpp` has the cpp code for all three tests. `everything.R` runs all three implementations (native R, non-efficient (with no pre-cumputation) and efficient). It checks that all three implementations yield the same result and it also run a small benchmark to compare performance on a single scenario. 

