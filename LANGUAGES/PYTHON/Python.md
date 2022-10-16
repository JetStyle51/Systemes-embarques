# Python

# Components

- `pip`
- `virtualenv`
- 

> Note: Python exists in a tiny version named `CircuitPython`

## Configuration

Know the version
```bash
~$ python -V
 Python 3.2.1
```

You can use `virtualenv` to choose which python you want to use as temporary
```bash
# Use this to create your temporary python "install"
# (Assuming that is the correct path to the python interpreter you want to use.)
virtualenv -p /usr/bin/python2.7 --distribute temp-python

# Type this command when you want to use your temporary python.
# While you are using your temporary python you will also have access to a temporary pip,
# which will keep all packages installed with it separate from your main python install.



# A shorter version of this command would be ". temp-python/bin/activate"
source temp-python/bin/activate

# When you no longer wish to use you temporary python type
desactivate
```

# Commands

`chmod` has the purpose of changing the permissions of file/folder
```bash
chmod 755 filename
# 777 permission on the directory means that everyone has access to read/write/execute (execute on a directory means that you can do an ls of the directory).
# 755 means read and execute access for everyone and also write access for the owner of the file. When you perform chmod 755 filename command you allow everyone to read and execute the file, the owner is allowed to write to the file as well. So, there should be no permission to everyone else other than the owner to write to the file, 755 permission is required
```