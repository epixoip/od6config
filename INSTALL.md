## Debian / Ubuntu

To build the .deb archive, run:

```
debuild -i -us -uc -b
```

Once the .deb has been built, *dpkg -i* the archive.


## All Others

```
make
make install
```
