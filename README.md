# agdb
agdb ("agdb is not gdb") is a system-wide debugger intended for systems composed of multiple boards (of possible different architectures). Agdb rises gdb instances (local o remote instances), coordinates them offering a unified single front-end.
Some notable features are: ability to set conditional breakpoints whose conditions depend on events or simbols of a different board (e.g. stop in the receiver loop only after the sender sent a specific message), and comparative debugging (debugging multiple instances at the same time until the execution path differs).
