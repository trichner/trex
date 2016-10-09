# The T-Rex Regex Group Matcher
`trex` (pronounced t-rex) is a simple command-line utility that works
similar to `grep`. The main difference is that it only shows the matching
groups of a regular expressions.

This allows simple parsing out of values from text while still requiring more context than just the match of the value.
While `sed` and `awk` can also do this, I never manage to remember the syntax.

This utility uses the UNIX/POSIX regex.h implementation of pattern matcher,
therefore POSIX syntax applies for provided patterns.

## Example

```
> echo "t=4.33 x=82 and d=99" | trex 'x=([0-9]*)'
82
```
As shown above, this makes parsing out values from files very simple.


## Wishlist
- allow input of multiple files
- add `-i` flag for case insensitive matches (eflags)
- add `-0` flag for `\0` separated matches instead of ' '

## Authors
- Thomas Richner
