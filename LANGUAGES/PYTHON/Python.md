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
## Regex
RegEx, or Regular Expression, is a sequence of characters that forms a search pattern.
RegEx can be used to check if a string contains the specified search pattern.

Example: this code aggregate logs into seperate groups and decode them.
```python
def read_manuf_log(expecter: OneWireSerialBytesExpecter, results):
    while True:
        try:
            match = expecter.expect_regex(b"([A-Z]+)? MANUF TEST ?: ([a-z_0-9]+) .*(PASS|FAIL)|Manuf tests global status ?: [^::ascii::]*(FAIL|PASS)|.*[IOCL|IOSOC] MANUF TEST: global results?", timeout=15)
            if match.groups[0]: # MANUF TEST
                results.append((match.groups[0].decode("ascii"), match.groups[1].decode("ascii"), match.groups[2].decode("ascii")))
            elif match.groups[3]: # Global status, end of the tests
                return
        except ExpectTimeout:
            # Check that we found at least a test, otherwise there is an issue
            return
```
