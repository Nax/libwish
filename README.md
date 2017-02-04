# libwish

Libwish is a rich, developer friendly text-mode library.

## How to build

```sh
mkdir -p build/release
cd build/release
cmake ../.. -DCMAKE_BUILD_TYPE=Release
make
sudo make install
```

Use `-lwish` to link against libwish.  
Libwish requires terminfo, which often comes bundled with ncurses.  
In that case, add `-lncurses` or `-lcurses` to the link flags as well.

## Why use libwish instead of ncurses?

I have five major problems with ncurses:

 * No support for Unicode
 * No support for colors outside of pairs
 * A very limited support for 256-colors terminals
 * A terrible API (yx coordinates anyone?)
 * Full of globals and non prefixed, very short names
 * The API is fixed in stone

Libwish solves every one of these issues:

 * Full Unicode support via UTF-8, even outside of the BMP
 * Support for raw 256-colors
 * A nicer, self-contained API under the `wish_` prefix
 * The API is open to changes, while safe thanks to SemVer

Of course, keep in mind that libwish is still a young project.

## I want to contribute

You're welcome.  
Open an issue or a pull request if you already have some code, and we will try to improve the project together.

## License

Libwish is available under the MIT License.

## Author

[Libwish](https://github.com/Nax/libwish) was created by Maxime Bacoux "[Nax](https://github.com/Nax)".
