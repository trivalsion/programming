# How python files and directories should be laid out and interconnected
## Resources
* [Full "import" system(together with packages) python documentation](https://docs.python.org/3/reference/import.html)
* [Python Documentation Tutorial on Modules](https://docs.python.org/3/tutorial/modules.html)
	* [Packages Section](https://docs.python.org/3/tutorial/modules.html#packages)
* [Python Project Structure Tutorial](https://dev.to/codemouse92/dead-simple-python-project-structure-and-imports-38c6)
* [Real Python Tutorial](https://realpython.com/python-modules-packages/)


## Package Project Structure
* Description - the best project structure for python with having one folder which would be the root package and all other code folders in it would be subpackages. Creating subpackage folders is needed for better code seperation and all the subpackages should be placed into the main package so that each of the subpackges could access modules from the root package or other subpackges without using `..` or modifying the python include search path.
### Definitions
* Module - .py file
* Package - directory with `__init__.py` file and other python files
	* The main package also has `__main__.py` in it and other packages(folders with `__init__.py`) in it are called subpackages
* In python `import` the dots(`.`) between names do not indicate classes... they indicate folders(e.g. `test1.test2.file` would be `./test1/test2/file`) and the final name(after which there is no dot) indicates the python file to be included

## Implementing
1. Place all of the code folders into one directory and make that directory that now contains other directories the root package by creating `__main__.py` and `__init__.py`(could be empty) files in it
	1. Put into `__main__.py`
		* 	```py
			import root_package.folder.py_file as pyfile # import the main executable/script of the package which should be called when the package is called

			if __name__ == '__main__': # name is __main__ when the package itself is called and not the script
				fc.start_client() # call some function in the main script
			```
	2. Create `__init__.py`(could be empty) in all subdirectories in the root package to make them subpackages
	3. For modules in root or subpackages to import anything from other subpackages of the root package or even their own subpackges they need to write all of the folder path starting from the root package - e.g. `import <root_package_folder_name>.<subpackage>.<py_file>`. None of the modules in packages can even import files that are located in their folder(packages are folders) without either writing the full path like in the first example in this point or writing `from .<py_file> import <object>`.
	4. Packages should be called with `python -m <package-folder>`(-m option calls package as if it was a script), which would call the `__main__.py` file in the package folder. If you call a module in a packge using `python module.py` than the include paths that go from root package folder wouldn't work.
		* To pass command line arguments to the script(`__main__.py`, the arguments are stored somewhere in the memory together with the script so they are not required to be passed by `__main__.py` to the script it calls and so they con be interpreted by a called function located in any of the scrips) when calling a package do `python -m <package-folder> --example-argument 1 --example-argument2 1...`
