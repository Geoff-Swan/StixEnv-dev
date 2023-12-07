#!/bin/fish

set value 0

set value (dmenu -p '  Volume >  ' < /dev/null);

amixer sset 'Master' $value%
