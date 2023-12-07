# StixEnv: 
### An ultra-lightweight, beautiful, dwm-based environment.


![alt text](screenshots/typical_usage.png) 
_The Stix Environment uses the pure, built-in dwm bar with some custom hacks. Slstatus provides the statusbar itself and status2d adds a splash of colour_

The ultimate goal of the Stix Environment is to end up a slick new spin on the 'suckless experience' that aims for something just a bit more special than the average DWM 'rice' while preserving that which makes suckless software great: simplicity, clarity, and frugality. _We are not there yet - not even close -_ and if you want a slick-looking DWM without the work, there's [chadwm](https://github.com/siduck/chadwm/). It's better than this may ever get.


### (Basically just Geoff Swan's DWM environment; the suckless suite with a few patches [some custom, some not] for looks and feels)
(& named for my preference to use linux as a persistent live installation on a USB stick for the sake of portability)

__This is very, *very* much a work in progress: use for reference, don't run in production just yet; right now the codebase is dirty and full of stupid little idiosyncrasies and poor naming conventions that only I can interpret.__


![alt text](screenshots/app_launcher.png) 
_The Stix Environment features a fairly typical (albiet patched and customised) build of dmenu, and makes extensive use of dmenu to provide option menus and text prompts to control power, brightness, volume_

#### Colours:

The Stix Environment uses the Catppuccin colourscheme: soft and easy on the eyes, and featuring vast support for just about every application that people in our sphere use, it should be exceptionally easy to theme one's entire workflow to match Stix for a particularly cohesive experience

#### Terminal: 

* At the minute, StixEnv's ST build is very minimally custom: one patch (`anysize`), and the config.h colours provided by Catppuccin themselves. More to come on ST soon. 

#### Window Manager:

The Stix Environment is built around Suckless' DWM, with a few alterations:

* The 'dot tag' tag / 'workspace' indicators are a custom addition found around line 850 in the souce code; they can be substituted for any character and soon users will have the ability to specify the character in `config.h`
* Tag indicators are now coloured with colours specified in config.h - this is a potential source of an out-of-range range as the code doesn't actually check to see if enough colours have been specified. This will change.
* Window titles and status bars display across all monitors; the window title is centred, and its colour can be specified in `config.h`
* Patches `vanitygaps` and `barpadding` space everything out a little, with the help of a couple of custom padding options exclusive to this build
* The `status2d` patch allows for (relatively) user-friendly colouring of both foreground and background in the status text
* I expect StixEnv::DWM to become the focal point for this environment, at least until I expand into other areas and build this out into a more complete DE with fully-custom tools: as a result, the custom DWM build will see lots of work!

#### D-Menu:

StixEnv::dmenu is a fairly standard build of dmenu; `center` confines the dmenu to a region in the centre of the screeen (a custom option in `config.h` allows the user to specify y-position to control the precise vertical position of dialogues), while `fuzzymatch` implements fuzzyfinding for option menus


* The Stix Environment relies heavily on dmenu, and dmenu will only become more intertwined with the environment.
* So far, it's responsible for a couple of proof-of-concept system-control dialogues (power menu, backlight control, and volume control), and as time goes on it will become increasingly responsible for allowing the user to fine-tune StixEnv on-the-fly. 
* These dialogues are defined and launched primarily from shell scripts written for the FISH shell and found in the scripts directory dwm expects to see them in `/usr/share/scripts`.
* StixEnv will soon feature lighter, more elegant, and tighter intergration with dmenu

- MORE TO COME (BOTH DOCS AND ACTUAL CODE) VERY SOON -

I DON'T UNDERSTAND LICENSING: The MIT/X Consortium License (under which Suckless software is licensed) permits sublicensing, and since MIT/X is a subset of GPL (as I understand it; I'm a child and not a lawyer), I did consider sublicensing under GPL because I like it but MIT is really straightforward and I really do not want to wander into actual legal territory regardless of how permissive and libre the metaphorical hornet's nest I'm poking may be. Everything here is under MIT/X Consortium.
