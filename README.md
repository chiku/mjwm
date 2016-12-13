mjwm
====

[![Build Status](https://travis-ci.org/chiku/mjwm.svg?branch=master)](https://travis-ci.org/chiku/mjwm)
[![Build Status](https://drone.io/github.com/chiku/mjwm/status.png)](https://drone.io/github.com/chiku/mjwm/latest)

Overview
--------

mjwm creates JWM's menu from (freedesktop) desktop files. Include the generated file in the rootmenu section of your ~/.jwmrc

Read more about JWM (Joe's Window Manager) at [http://joewing.net/projects/jwm](http://joewing.net/projects/jwm)

mjwm is based on mjm by insmyic <gminsm@gmail.com> [http://sourceforge.net/projects/mjm](http://sourceforge.net/projects/mjm)

Dependencies
------------

The application runs on a POSIX system with a C++ runtime.

For compiling the aplication you need make, automake, autoconf and a recent C++ compiler. This application has compiled fine with g++ versions 4.6, 4.8 & 4.9 & 5.3 and clang++ 3.3, 3.4, 3.5 & 3.7.

Installation from source
------------------------

* Clone the repository

* From the root of the application run
```script
./autogen.sh
./configure --prefix=/usr
make
sudo make install
```

Options
-------

``` script
Usage: mjwm [options]

Optional arguments:
  -c, --category-file=[FILE]  Use an external category file. Overrides the
                                built in categories. Please look at
                                default.mjwm to write your own category files.
      --help                  Show this help.
      --iconize=[THEME]       Search for icon files by name in $HOME,
                                $XDG_DATA_DIRS/icons, and /usr/share/pixmaps.
                                Icon file names would be absolute paths to
                                icons in the specified directories. Hicolor
                                icon theme is used if no theme name is given.
  -i, --input-directory=[DIRECTORY]
                              Directory to scan for '.desktop' files. Multiple
                                directories, if provided, must be separated by
                                colons. [Default: application directories
                                under $XDG_DATA_HOME & $XDG_DATA_DIRS]
      --language=[NAME]       The language for which the menu would be build.
      --no-backup             Do not create any backup files.
  -o, --output-file=[FILE]    Outfile file [Default: $HOME/.jwmrc-mjwm]
  -v  --verbose               Verbose output.
      --version               Show version information.
```

Usage
-----

* Run the script
``` script
mjwm
```

* Edit your ```$HOME/.jwmrc file```. Add an ```<Include>$HOME/.jwmrc-mjwm</Include>``` line inside ```RootMenu```.
``` xml
<JWM>
  <!-- SNIP SNIP -->

  <RootMenu onroot="12">
      <!-- Other Menu Entries -->

      <Include>$HOME/.jwmrc-mjwm</Include>

      <!-- Other Menu Entries -->
  </RootMenu>

  <!-- SNIP SNIP -->
</JWM>
```

* Reload JWM
``` script
jwm -reload
```

Examples
--------

Generate menu entries for files inside /usr/local/share/applications
``` script
mjwm -i /usr/local/share/applications
```

Generate menu entries for files inside multiple directories /usr/local/share/applications, /usr/share/applications
& ~/.local/share/applications
``` script
mjwm -i /usr/local/share/applications:/usr/share/applications:~/.local/share/applications
```

Create menu entries with absolute path names to icons images from Hicolor theme
``` script
mjwm --iconize
```

Create menu entries with absolute path names to icons images from Faenza theme
``` script
mjwm --iconize=Faenza # this works as well : mjwm --iconize Faenza
```

Use categories from as an external file
Look at data/default.mjwm to create your own category file
``` script
mjwm -c data/default.mjwm
```

Running tests
-------------

* Clone the repository

* From the root of the application run
``` script
./autogen.sh
./configure
VERBOSE=true make check
```

_mjwm uses [Doctest](https://github.com/onqtam/doctest) for unit tests. Doctest is released under the MIT License._

Exit codes
----------

* 0 - All okay
* 1 - Couldn't access file for read or write (e.g. couldn't create output file)
* 2 - Invalid command line arguments

Contributing
------------

* Fork the project.
* Make your feature addition or bug fix.
* Add tests for it. This is important so I don't break it in a future version unintentionally.
* Commit, but do not mess with the VERSION. If you want to have your own version, that is fine but bump the version in a commit by itself in another branch so I can ignore it when I pull.
* Send me a pull request.

License
-------

This tool is released under the GPLv3 license. Please refer to COPYING for license information.
