## Copyright and License

std-simd is licensed with the [3-clause BSD license](http://opensource.org/licenses/BSD-3-Clause).
Your contributions to std-simd must be released under the same license. You must add
your copyright information to the files you modified/added.

## Code Formatting & Style

The recommended way is to format the code according to `clang-format` using the
`.clang-format` file in the repository.

## Git History

Git history should be flat, if feasible. Feel free to use merges on your private
branch. However, once you submit a pull request, the history should apply
cleanly on top of master. Use `git rebase [-i]` to straighten the history.

Use different branches for different issues.

## Git Commit Logs

1. Write meaningful summaries and strive to use no more than 50 characters
1. Use imperative mood in the subject line (and possibly in bullet points in the
   summary)
1. Wrap the body at 72 characters
1. Use the body to explain *what* and *why* (normally it is irrelevant *how* you
   did it)

See also [Chris Beams article](http://chris.beams.io/posts/git-commit/).
