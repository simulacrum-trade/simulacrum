
Debian
====================
This directory contains files used to package simulacrumd/simulacrum-qt
for Debian-based Linux systems. If you compile simulacrumd/simulacrum-qt yourself, there are some useful files here.

## simulacrum: URI support ##


simulacrum-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install simulacrum-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your simulacrum-qt binary to `/usr/bin`
and the `../../share/pixmaps/simulacrum128.png` to `/usr/share/pixmaps`

simulacrum-qt.protocol (KDE)

