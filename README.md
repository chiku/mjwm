mjwm
====

[![Build Status](https://travis-ci.org/chiku/mjwm.png?branch=master)](https://travis-ci.org/chiku/mjwm)

Overview
--------

mjwm creates JWM's menu from (freedesktop) desktop files. Include the generated file in the rootmenu section of your ~/.jwmrc

Read more about JWM (Joe's Window Manager) at [http://joewing.net/projects/jwm](http://joewing.net/projects/jwm)

mjwm is based on mjm by insmyic <gminsm@gmail.com> [http://sourceforge.net/projects/mjm](http://sourceforge.net/projects/mjm)

Dependencies
------------

The application runs on a POSIX system with a C++ runtime.

For compiling the aplication you need make, automake, autoconf and a recent C++ compiler. This application has compiled fine with g++ 4.6, g++ 4.8 and clang++ 3.3.

Installation from source
------------------------

* Clone the repository

* From the root of the application run
```script
./autogen.sh
./configure --prefix=/usr # Install mjwm to /usr, when prefix is not mentioned installs to /usr/local
make
sudo make install
```

Options
-------

``` script
Usage: mjwm [options]

Optional arguments:
  -o, --output-file [FILE]    Outfile file [Default: ./automenu]
  -i, --input-directory [DIRECTORY]
                              Directory to scan for '.desktop' files. Multiple
                                directories, if provided, must be separated by
                                colons. [Default: applications directories
                                under $XDG_DATA_DIRS & $XDG_DATA_DIRS]
  -c, --category-file [FILE]  Use an external category file. Overrides the
                                built in categories. Please look at
                                default.mjwm to write your own category files.
      --iconize               Search for icon files by name in $HOME,
                                $XDG_DATA_DIRS/icons, and /usr/share/pixmaps.
                                Icon file names would be absolute paths to
                                icons in the specified directories.
      --help                  Show this help
      --version               Show version information
```

Usage
-----

* Run the script
``` script
mjwm -o $HOME/.mjwm-entries -a
```

* Edit your $HOME/.jwmrc file. Add an Include $HOME/.mjwm-entries line inside RootMenu.
``` xml
<JWM>
  <!-- SNIP SNIP -->

  <RootMenu onroot="12">
      <!-- Other Menu Entries -->

      <Include>$HOME/.mjwm-entries</Include>

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
# mjwm -i /usr/local/share/applications/ # works as well
```

Generate menu entries for files inside multiple directories /usr/local/share/applications, /usr/share/applications
& ~/.local/share/applications
``` script
mjwm -i /usr/local/share/applications:/usr/share/applications:~/.local/share/applications
```

Create menu entries with absolute path names to icons files
``` script
mjwm --iconize
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

_mjwm uses [Catch](https://github.com/philsquared/Catch) for unit tests. Catch is released under Boost Software License._

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
