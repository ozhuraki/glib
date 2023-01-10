
## To Debug

```
# echo "deb http://ddebs.ubuntu.com $(lsb_release -cs) main restricted universe multiverse
deb http://ddebs.ubuntu.com $(lsb_release -cs)-updates main restricted universe multiverse
deb http://ddebs.ubuntu.com $(lsb_release -cs)-proposed main restricted universe multiverse" > ddebs.list

# sudo mv -v ddebs.list /etc/apt/sources.list.d/
# sudo apt install ubuntu-dbgsym-keyring
```

```
# sudo apt install libglib2.0-0-dbgsym
# mkdir src
# cd src
# apt-get source libglib2.0-0
# ln -s glib2.0-* glib
# cd ..
```

```
# make clean all CC="gcc -O0 -g"
```

```
(gdb) set substitute-path ../../../gio src/glib/gio
```
