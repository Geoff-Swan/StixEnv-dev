#!/bin/fish

set value 0

set value (dmenu -p 'Brightness >' < /dev/null);

sudo light -S $value
