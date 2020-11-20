# Virtual-File-System
● A virtual file system provides a standard interface between the
operating system kernel and the details of actual file systems.
● VFS system will have all of the usual functions, such
as open, close, read, write, rename, delete.
● It will pass them to file system drivers, which are responsible
for implementing the commands in the case of any particular
file system.

● It allows client applications to access different types of concrete
file systems in a uniform way.
● To access local and network storage devices transparently without
the client application noticing the difference.
● To bridge the differences in Windows, classic Mac OS/macOS and
Unix filesystems
● Making it is easy to add support for new file system types to the
kernel simply by fulfilling the contract.
