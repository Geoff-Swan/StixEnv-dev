#!/bin/fish

switch (echo -e "Power Off\nReboot\nLogout\nLock Screen" | dmenu -i)
	case 'Power Off'
		shutdown now
		echo 'shutting down'
	case 'Reboot'
		echo 'rebooting'
		reboot
	case 'Logout'
		echo 'logging you out'
		killall dwm
	case 'Lock Screen'
		echo 'locking the screen'
		slock
	end
