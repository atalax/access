access
======

Wrapper around the access syscall.

```
Usage: access [OPTIONS].. [FILE]...
Lists whether the current user does have specified permissions to the files.
The exit code is 0 if all the listed files match the mask.
See man 2 access for more details.

  -q, --quiet			No output, just the exit code
  -e, --effective			Use the eacess syscall instead
  -r, --read			Check whether the user can read
  -w, --write			Check whether the user can write
  -x, --execute			Check whether the user can execute
  -h, --help			Display this message
```
