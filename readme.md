# This is an experiment
with [mruby](https://mruby.org) some test programs are included in the rubies folder.

this program is liable to being buggy and unsound but it aims to demonstrate what is possible with mruby.

## Compilation
For the cmake recipe to work properly you need to download mruby 2.x.x and extract it on a folder called vendor,
inside it extract the mruby and strip the version from the pathname, compile mruby first and then compile this program.

The resulting binary is self contained and takes a single mrb filename as an argument, ie:
`controller rubies/game_demo.rb`