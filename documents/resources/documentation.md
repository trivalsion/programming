# Programming Tools Documentation
## Programming Tools
* [LLVM - toolchain](https://llvm.org/)
	* [Clang Compiler Documentation](https://clang.llvm.org/docs/index.html)
		* [Cross-compilation Info](https://clang.llvm.org/docs/CrossCompilation.html)
		* [Toolchain info](https://clang.llvm.org/docs/Toolchain.html)
	* [LLD Linker Documentation](https://lld.llvm.org/)

* [GNU - toolchain](https://www.gnu.org/manual/manual.html)
	* [GNU GCC Compiler](https://gcc.gnu.org/onlinedocs/)
	* [GNU Binutils(e.g. ld)](https://www.gnu.org/software/binutils/)
		* [Linkerscript guide](https://sourceware.org/binutils/docs/ld/Scripts.html)

* [Make - Build system](https://www.gnu.org/software/make/)
	* [Make Documentation](https://www.gnu.org/software/make/manual/)
		* [Make documentation's complex makefile example](https://www.gnu.org/software/make/manual/make.html#Complex-Makefile)
	* [Guide](https://makefiletutorial.com/)
	* [OSdev Makefile guide](https://wiki.osdev.org/Makefile)
	* [Writing complex makefiles guide](http://nuclear.mutantstargoat.com/articles/make/)

* [Bash - Shell](https://www.gnu.org/software/bash/manual/bash.html#Redirecting-Input)

* [Git - Source Control System](https://git-scm.com/doc)
	* [Official git architectue and usage book](https://git-scm.com/book/en/v2)
	* [Official git tutorial](https://git-scm.com/docs/gittutorial)
	* [Bitbucket git guide](https://www.atlassian.com/git)

* [Python - Programming language](https://www.python.org/doc/)


## Documentation Tools
* Markdown - the easiest and the best documentation format that follows WYSIWYM(What You See Is What You Mean) paradigm
	* [Most Common Specification(there are some others)](https://commonmark.org/)
	* [Markdown Guide](https://www.markdownguide.org/)
		* [CheatSheet](https://www.markdownguide.org/cheat-sheet/)
			* [Basic Syntax - Supported by all of the Markdown parsers](https://www.markdownguide.org/basic-syntax/)
			* [Extended Syntax - Supported by some or most, but not all Markdown parsers](https://www.markdownguide.org/extended-syntax/)
	* Markdown to PDF/HTML/... conversion tools
		* [Pandoc - document converter that supports multiple formats to convert to and from(Link to examples of conversion including Markdown)](https://pandoc.org/demos.html)



# Specifications
* C Documentation
	* [GNU C Documentation](https://www.gnu.org/software/gnu-c-manual/)
	* Official C documentation
		* To find a particular document from standards website search google for - \<xx\> c standard draft. Then if the google found it, copy the link to it and get name of the document by reading the link(it should be something like n4747 somewhere in the link) and find it in [documents list](http://www.open-std.org/JTC1/SC22/WG14/www/docs/)
		* [Official open standards website](http://www.open-std.org/)
		* [C standards](http://www.open-std.org/JTC1/SC22/WG14/)
		* [All C standard draft documents list](http://www.open-std.org/JTC1/SC22/WG14/www/docs/)
		* [C11 Standard draft](http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1548.pdf)

* System V ABI
	* [Sys V AMD64 ABI](https://gitlab.com/x86-psABIs/x86-64-ABI)
	* [Links](https://wiki.osdev.org/System_V_ABI#Documents)

* UNIX - there are multiple unix specification documents(and there are a lot of revisions of each so make sure to use the latest)
	* [UNIX specification](https://www.opengroup.org/membership/forums/platform/unix)
	* [Collection of POSIX documents](http://www.open-std.org/JTC1/SC22/WG15/)
	* [Collection of UNIX standards](https://publications.opengroup.org/standards/unix/single-unix-specification)
		* [Single UNIX specification](https://publications.opengroup.org/t101)
		* [UNIX Base Specification](https://publications.opengroup.org/standards/unix/c181)

* Collections
	* [Collection of open group's open standards](https://publications.opengroup.org/)
	* [Collection of various open standards and/or their drafts](http://www.open-std.org/)



# Programming Language Uses
* `C` - extremely low level and/or performance sensative tasks
	* Device Drivers
	* Operating Systems
	* Graphics Programming(e.g. Renderers or Raytracers)
	* Game Engines
	* Electronic Engineering/Firmware

* `Rust` - alternative to C++(and C) for complex applications that require concurrency and memory-safety(rust has no memory errors such as segfaults)
	* Same uses as with C above(except EE/Firmware and Drivers)
	* Blockchain
	* Databases
	* Search Engines

* `Python` - very high level stuff(like automation or ML) and scripts
	* Parsers
	* General purpose GUI desktop applications(e.g. image viewver or mediaplayer)
	* Artificial Intelligence/Machine Learning
	* Proof of Concepts(e.g. CVE/vulneravility, algorithm or new idea testing)

* `C++` - complex low-level applications that require both high execution speed and Object Oriented Programming(Which C does't have)
	* Gamedev and Game Engines
	* Internet Browsers
	* Virtualization
